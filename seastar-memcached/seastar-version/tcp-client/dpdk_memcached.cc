#include "dpdk_memcached.hh"
#include "dpdk_basic.hh"
#include "dpdk_error.hh"
#include <sys/time.h>

#define memcached_is_auto_eject_hosts(__object) ((__object)->flags.auto_eject_hosts)


/* string value */
struct memcached_continuum_item_st
{
    uint32_t index;
    uint32_t value;
};

struct memcached_virtual_bucket_t {
    bool has_forward;
    uint32_t size;
    uint32_t replicas;
    struct bucket_t buckets[];
};


static void sort_hosts(Memcached *ptr)
{
    if (memcached_server_count(ptr))
    {
        qsort(memcached_instance_list(ptr), memcached_server_count(ptr), sizeof(memcached_instance_st), compare_servers);
    }
}

memcached_return_t run_distribution(Memcached *ptr)
{
    if (ptr->flags.use_sort_hosts)
    {
        sort_hosts(ptr);
    }

    switch (ptr->distribution)
    {
        case MEMCACHED_DISTRIBUTION_CONSISTENT:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA_SPY:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_WEIGHTED:
            return update_continuum(ptr);

        case MEMCACHED_DISTRIBUTION_VIRTUAL_BUCKET:
        case MEMCACHED_DISTRIBUTION_MODULA:
            break;

        case MEMCACHED_DISTRIBUTION_RANDOM:
            srandom((uint32_t) time(NULL));
            break;

        case MEMCACHED_DISTRIBUTION_CONSISTENT_MAX:
        default:
            assert_msg(0, "Invalid distribution type passed to run_distribution()");
    }

    return MEMCACHED_SUCCESS;
}


uint32_t memcached_virtual_bucket_get(const memcached_st *self, uint32_t digest)
{
    if (self)
    {
        if (self->virtual_bucket)
        {
            uint32_t result= (uint32_t) (digest & (self->virtual_bucket->size -1));
            return self->virtual_bucket->buckets[result].master;
        }

        return (uint32_t) (digest & (self->number_of_hosts -1));
    }

    return 0;
}

memcached_return_t initialize_query(Memcached *self, bool increment_query_id)
{
    if (self == NULL)
    {
        return MEMCACHED_INVALID_ARGUMENTS;
    }

    if (increment_query_id)
    {
        self->query_id++;
    }

    if (self->state.is_time_for_rebuild)
    {
        memcached_reset(self);
    }

    memcached_error_free(*self);
    memcached_result_reset(&self->result);

    return MEMCACHED_SUCCESS;
}

struct memcached_array_st
{
    Memcached *root;
    size_t size;
    char c_str[];
};

size_t memcached_array_size(memcached_array_st *array)
{
    if (array)
    {
        return array->size;
    }

    return 0;
}

const char *memcached_array_string(memcached_array_st *array)
{
    if (array)
    {
        return array->c_str;
    }

    return NULL;
}

static inline void _regen_for_auto_eject(Memcached *ptr)
{
    if (_is_auto_eject_host(ptr) && ptr->ketama.next_distribution_rebuild)
    {
        struct timeval now;

        if (gettimeofday(&now, NULL) == 0 and
            now.tv_sec > ptr->ketama.next_distribution_rebuild)
        {
            run_distribution(ptr);
        }
    }
}


static uint32_t dispatch_host(const Memcached *ptr, uint32_t hash)
{
    switch (ptr->distribution)
    {
        case MEMCACHED_DISTRIBUTION_CONSISTENT:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_WEIGHTED:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_KETAMA_SPY:
        {
            uint32_t num= ptr->ketama.continuum_points_counter;
            WATCHPOINT_ASSERT(ptr->ketama.continuum);

            memcached_continuum_item_st *begin, *end, *left, *right, *middle;
            begin= left= ptr->ketama.continuum;
            end= right= ptr->ketama.continuum + num;

            while (left < right)
            {
                middle= left + (right - left) / 2;
                if (middle->value < hash)
                    left= middle + 1;
                else
                    right= middle;
            }
            if (right == end)
                right= begin;
            return right->index;
        }
        case MEMCACHED_DISTRIBUTION_MODULA:
            return hash % memcached_server_count(ptr);
        case MEMCACHED_DISTRIBUTION_RANDOM:
            return (uint32_t) random() % memcached_server_count(ptr);
        case MEMCACHED_DISTRIBUTION_VIRTUAL_BUCKET:
        {
            return memcached_virtual_bucket_get(ptr, hash);
        }
        default:
        case MEMCACHED_DISTRIBUTION_CONSISTENT_MAX:
            WATCHPOINT_ASSERT(0); /* We have added a distribution without extending the logic */
            return hash % memcached_server_count(ptr);
    }
    /* NOTREACHED */
}


uint32_t hashkit_digest(const hashkit_st *self, const char *key, size_t key_length)
{
    return self->base_hash.function(key, key_length, self->base_hash.context);
}


static inline uint32_t generate_hash(const Memcached *ptr, const char *key, size_t key_length)
{
    return hashkit_digest(&ptr->hashkit, key, key_length);
}



static inline uint32_t _generate_hash_wrapper(const Memcached *ptr, const char *key, size_t key_length)
{
    if (memcached_server_count(ptr) == 1)
        return 0;

    if (ptr->flags.hash_with_namespace)
    {
        size_t temp_length= memcached_array_size(ptr->_namespace) + key_length;
        char temp[MEMCACHED_MAX_KEY];

        if (temp_length > MEMCACHED_MAX_KEY -1)
            return 0;

        strncpy(temp, memcached_array_string(ptr->_namespace), memcached_array_size(ptr->_namespace));
        strncpy(temp + memcached_array_size(ptr->_namespace), key, key_length);

        return generate_hash(ptr, temp, temp_length);
    }
    else
    {
        return generate_hash(ptr, key, key_length);
    }
}

uint32_t memcached_generate_hash_with_redistribution(memcached_st *ptr, const char *key, size_t key_length)
{
    uint32_t hash= _generate_hash_wrapper(ptr, key, key_length);

    _regen_for_auto_eject(ptr);

    return dispatch_host(ptr, hash);
}



static inline memcached_return_t memcached_send(memcached_st *shell,
                                                const char *group_key, size_t group_key_length,
                                                const char *key, size_t key_length,
                                                const char *value, size_t value_length,
                                                const time_t expiration,
                                                const uint32_t flags,
                                                const uint64_t cas,
                                                memcached_storage_action_t verb)
{
    Memcached* ptr= memcached2Memcached(shell);
    memcached_return_t rc;
    if (memcached_failed(rc= initialize_query(ptr, true)))
    {
        return rc;
    }

    uint32_t server_key= memcached_generate_hash_with_redistribution(ptr, group_key, group_key_length);
//    memcached_instance_st* instance= memcached_instance_fetch(ptr, server_key);
//
//    WATCHPOINT_SET(instance->io_wait_count.read= 0);
//    WATCHPOINT_SET(instance->io_wait_count.write= 0);
//
//    bool flush= true;
//    if (memcached_is_buffering(instance->root) and verb == SET_OP)
//    {
//        flush= false;
//    }
//
//    bool reply= memcached_is_replying(ptr);
//
//    hashkit_string_st* destination= NULL;
//
//    if (memcached_is_encrypted(ptr))
//    {
//        if (can_by_encrypted(verb) == false)
//        {
//            return memcached_set_error(*ptr, MEMCACHED_NOT_SUPPORTED, MEMCACHED_AT,
//                                       memcached_literal_param("Operation not allowed while encyrption is enabled"));
//        }
//
//        if ((destination= hashkit_encrypt(&ptr->hashkit, value, value_length)) == NULL)
//        {
//            return rc;
//        }
//        value= hashkit_string_c_str(destination);
//        value_length= hashkit_string_length(destination);
//    }
//
//    if (memcached_is_binary(ptr))
//    {
//        rc= memcached_send_binary(ptr, instance, server_key,
//                                  key, key_length,
//                                  value, value_length, expiration,
//                                  flags, cas, flush, reply, verb);
//    }
//    else
//    {
//        rc= memcached_send_ascii(ptr, instance,
//                                 key, key_length,
//                                 value, value_length, expiration,
//                                 flags, cas, flush, reply, verb);
//    }
//
//    hashkit_string_free(destination);

    return rc;
}



memcached_return_t dpdk_memcached_set(memcached_st *ptr, const char *key, size_t key_length,
                                 const char *value, size_t value_length,
                                 time_t expiration,
                                 uint32_t flags)
{
    std::cout << "dpdk_memcached_set BEGIN" << std::endl;
    memcached_return_t rc;
    LIBMEMCACHED_MEMCACHED_SET_START();
    rc= memcached_send(ptr, key, key_length,
                       key, key_length, value, value_length,
                       expiration, flags, 0, SET_OP);
    LIBMEMCACHED_MEMCACHED_SET_END();

    std::cout << "dpdk_memcached_set END" << std::endl;
    return rc;
}

