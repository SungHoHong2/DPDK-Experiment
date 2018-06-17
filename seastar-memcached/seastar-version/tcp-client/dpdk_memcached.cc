#include "dpdk_memcached.hh"
#define	LIBMEMCACHED_MEMCACHED_SET_START()
#define	LIBMEMCACHED_MEMCACHED_SET_END()
#define memcached2Memcached(__obj) (__obj)

typedef struct memcached_st Memcached;

enum memcached_storage_action_t {
    SET_OP,
    REPLACE_OP,
    ADD_OP,
    PREPEND_OP,
    APPEND_OP,
    CAS_OP
};


#define MAX_ERROR_LENGTH 2048
struct memcached_error_t
{
    Memcached *root;
    uint64_t query_id;
    struct memcached_error_t *next;
    memcached_return_t rc;
    int local_errno;
    size_t size;
    char message[MAX_ERROR_LENGTH];
};



static inline void libmemcached_free(const memcached_st *self, void *mem)
{
    if (self)
    {
        self->allocators.free(self, mem, self->allocators.context);
    }
    else if (mem)
    {
#ifdef __cplusplus
        std::free(mem);
#else
        free(mem);
#endif
    }
}


static void _error_free(memcached_error_t *error)
{
    if (error)
    {
        _error_free(error->next);

        libmemcached_free(error->root, error);
    }
}


void memcached_error_free(Memcached& self)
{
    _error_free(self.error_messages);
    self.error_messages= NULL;
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

    if (memcached_server_count(self) == 0)
    {
        return memcached_set_error(*self, MEMCACHED_NO_SERVERS, MEMCACHED_AT);
    }

    memcached_error_free(*self);
    memcached_result_reset(&self->result);

    return MEMCACHED_SUCCESS;
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
//
//    if (memcached_failed(memcached_key_test(*ptr, (const char **)&key, &key_length, 1)))
//    {
//        return memcached_last_error(ptr);
//    }
//
//    uint32_t server_key= memcached_generate_hash_with_redistribution(ptr, group_key, group_key_length);
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

