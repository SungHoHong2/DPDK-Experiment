#include "dpdk_memcached.hh"
#include "dpdk_basic.hh"
#include "dpdk_error.hh"
#include "md5.hh"
#include <sys/time.h>
#include "dpdk_hash.hh"
#include "dpdk_string.hh"
#include "aes.hh"
#include "dpdk_io.hh"


#define memcached_is_buffering(__object) ((__object)->flags.buffer_requests)
#define memcached_is_encrypted(__object) ((__object)->hashkit._key)
#define memcached_is_replying(__object) ((__object)->flags.reply)


static inline const char *storage_op_string(memcached_storage_action_t verb)
{
    switch (verb)
    {
        case REPLACE_OP:
            return "replace ";

        case ADD_OP:
            return "add ";

        case PREPEND_OP:
            return "prepend ";

        case APPEND_OP:
            return "append ";

        case CAS_OP:
            return "cas ";

        case SET_OP:
            break;
    }

    return "set ";
}


memcached_instance_st* memcached_instance_fetch(Memcached *ptr, uint32_t server_key)
{
    if (ptr == NULL)
    {
        return NULL;
    }

    return &ptr->servers[server_key];
}

struct libmemcached_io_vector_st
{
    const void *buffer;
    size_t length;
};



hashkit_string_st *hashkit_encrypt(hashkit_st *kit,
                                   const char* source, size_t source_length)
{
    return aes_encrypt(static_cast<aes_key_t*>(kit->_key), source, source_length);
}


bool memcached_io_writev(memcached_instance_st* instance,
                         libmemcached_io_vector_st vector[],
                         const size_t number_of, const bool with_flush)
{
    ssize_t complete_total= 0;
    ssize_t total= 0;

    for (size_t x= 0; x < number_of; x++, vector++)
    {
        complete_total+= vector->length;
        if (vector->length)
        {
            size_t written;
            if ((_io_write(instance, vector->buffer, vector->length, false, written)) == false)
            {
                return false;
            }
            total+= written;
        }
    }
//
//    if (with_flush)
//    {
//        if (memcached_io_write(instance) == false)
//        {
//            return false;
//        }
//    }

    return (complete_total == total);
}





#include <sys/socket.h>
#include <poll.h>

memcached_return_t memcached_vdo(memcached_instance_st* instance,
                                 libmemcached_io_vector_st vector[],
                                 const size_t count,
                                 const bool with_flush)
{
    memcached_return_t rc;


//    if (memcached_is_udp(instance->root))
//    {
//        return _vdo_udp(instance, vector, count);
//    }
//
    bool sent_success= memcached_io_writev(instance, vector, count, with_flush);
//    if (sent_success == false)
//    {
//        assert(memcached_last_error(instance->root) == MEMCACHED_SUCCESS);
//        if (memcached_last_error(instance->root) == MEMCACHED_SUCCESS)
//        {
//            assert(memcached_last_error(instance->root) != MEMCACHED_SUCCESS);
//            return memcached_set_error(*instance, MEMCACHED_WRITE_FAILURE, MEMCACHED_AT);
//        }
//        else
//        {
//            rc= memcached_last_error(instance->root);
//        }
//    }
//    else if (memcached_is_replying(instance->root))
//    {
//        memcached_server_response_increment(instance);
//    }

    return rc;
}


static memcached_return_t memcached_send_ascii(Memcached *ptr,
                                               memcached_instance_st* instance,
                                               const char *key,
                                               const size_t key_length,
                                               const char *value,
                                               const size_t value_length,
                                               const time_t expiration,
                                               const uint32_t flags,
                                               const uint64_t cas,
                                               const bool flush,
                                               const bool reply,
                                               const memcached_storage_action_t verb)
{
    char flags_buffer[MEMCACHED_MAXIMUM_INTEGER_DISPLAY_LENGTH +1];
    int flags_buffer_length= snprintf(flags_buffer, sizeof(flags_buffer), " %u", flags);

    char expiration_buffer[MEMCACHED_MAXIMUM_INTEGER_DISPLAY_LENGTH +1];
    int expiration_buffer_length= snprintf(expiration_buffer, sizeof(expiration_buffer), " %llu", (unsigned long long)expiration);

    char value_buffer[MEMCACHED_MAXIMUM_INTEGER_DISPLAY_LENGTH +1];
    int value_buffer_length= snprintf(value_buffer, sizeof(value_buffer), " %llu", (unsigned long long)value_length);


    char cas_buffer[MEMCACHED_MAXIMUM_INTEGER_DISPLAY_LENGTH +1];
    int cas_buffer_length= 0;
    if (cas)
    {
        cas_buffer_length= snprintf(cas_buffer, sizeof(cas_buffer), " %llu", (unsigned long long)cas);
    }

    libmemcached_io_vector_st vector[]=
            {
                    { NULL, 0 },
                    { storage_op_string(verb), strlen(storage_op_string(verb))},
                    { memcached_array_string(ptr->_namespace), memcached_array_size(ptr->_namespace) },
                    { key, key_length },
                    { flags_buffer, size_t(flags_buffer_length) },
                    { expiration_buffer, size_t(expiration_buffer_length) },
                    { value_buffer, size_t(value_buffer_length) },
                    { cas_buffer, size_t(cas_buffer_length) },
                    { " noreply", reply ? 0 : memcached_literal_param_size(" noreply") },
                    { memcached_literal_param("\r\n") },
                    { value, value_length },
                    { memcached_literal_param("\r\n") }
            };

    /* Send command header */
    memcached_return_t rc=  memcached_vdo(instance, vector, 12, flush);
//
//    // If we should not reply, return with MEMCACHED_SUCCESS, unless error
//    if (reply == false)
//    {
//        return memcached_success(rc) ? MEMCACHED_SUCCESS : rc;
//    }
//
//    if (flush == false)
//    {
//        return memcached_success(rc) ? MEMCACHED_BUFFERED : rc;
//    }
//
//    if (rc == MEMCACHED_SUCCESS)
//    {
//        char buffer[MEMCACHED_DEFAULT_COMMAND_SIZE];
//        rc= memcached_response(instance, buffer, sizeof(buffer), NULL);
//
//        if (rc == MEMCACHED_STORED)
//        {
//            return MEMCACHED_SUCCESS;
//        }
//    }
//
//    if (rc == MEMCACHED_WRITE_FAILURE)
//    {
//        memcached_io_reset(instance);
//    }
//
//    assert(memcached_failed(rc));
//#if 0
//    if (memcached_has_error(ptr) == false)
//  {
//    return memcached_set_error(*ptr, rc, MEMCACHED_AT);
//  }
//#endif

    return rc;
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
    memcached_instance_st* instance= memcached_instance_fetch(ptr, server_key);
    instance->io_wait_count.read= 0;
    instance->io_wait_count.write= 0;


    bool flush= true;
    if (memcached_is_buffering(instance->root) and verb == SET_OP)
    {
        flush= false;
    }

    bool reply= memcached_is_replying(ptr);

    hashkit_string_st* destination= NULL;

    if (memcached_is_encrypted(ptr))
    {

        if ((destination= hashkit_encrypt(&ptr->hashkit, value, value_length)) == NULL)
        {
            return rc;
        }
        value= hashkit_string_c_str(destination);
        value_length= hashkit_string_length(destination);
    }

//    if (memcached_is_binary(ptr))
//    {
//        rc= memcached_send_binary(ptr, instance, server_key,
//                                  key, key_length,
//                                  value, value_length, expiration,
//                                  flags, cas, flush, reply, verb);
//    }
//    else
//    {
        rc= memcached_send_ascii(ptr, instance,
                                 key, key_length,
                                 value, value_length, expiration,
                                 flags, cas, flush, reply, verb);
//    }

    hashkit_string_free(destination);

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

