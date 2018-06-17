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
#define SOCKET_ERROR -1
#define get_socket_errno() errno
#include <sys/socket.h>
#include <poll.h>

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




static bool repack_input_buffer(memcached_instance_st* instance)
{
//    if (instance->read_ptr != instance->read_buffer)
//    {
//        /* Move all of the data to the beginning of the buffer so
//         ** that we can fit more data into the buffer...
//       */
//        memmove(instance->read_buffer, instance->read_ptr, instance->read_buffer_length);
//        instance->read_ptr= instance->read_buffer;
//        instance->read_data_length= instance->read_buffer_length;
//    }
//
//    /* There is room in the buffer, try to fill it! */
//    if (instance->read_buffer_length != MEMCACHED_MAX_BUFFER)
//    {
//        do {
//            /* Just try a single read to grab what's available */
//            ssize_t nr;
//            if ((nr= ::recv(instance->fd,
//                            instance->read_ptr + instance->read_data_length,
//                            MEMCACHED_MAX_BUFFER - instance->read_data_length,
//                            MSG_NOSIGNAL)) <= 0)
//            {
//                if (nr == 0)
//                {
//                    memcached_set_error(*instance, MEMCACHED_CONNECTION_FAILURE, MEMCACHED_AT);
//                }
//                else
//                {
//                    switch (get_socket_errno())
//                    {
//                        case EINTR:
//                            continue;
//
//#if EWOULDBLOCK != EAGAIN
//                            case EWOULDBLOCK:
//#endif
//                        case EAGAIN:
//#ifdef __linux
//                            case ERESTART:
//#endif
//                            break; // No IO is fine, we can just move on
//
//                        default:
//                            memcached_set_errno(*instance, get_socket_errno(), MEMCACHED_AT);
//                    }
//                }
//
//                break;
//            }
//            else // We read data, append to our read buffer
//            {
//                instance->read_data_length+= size_t(nr);
//                instance->read_buffer_length+= size_t(nr);
//
//                return true;
//            }
//        } while (false);
//    }

    return false;
}


static bool process_input_buffer(memcached_instance_st* instance)
{
    /*
     ** We might be able to process some of the response messages if we
     ** have a callback set up
   */
//    if (instance->root->callbacks != NULL)
//    {
//        /*
//         * We might have responses... try to read them out and fire
//         * callbacks
//       */
//        memcached_callback_st cb= *instance->root->callbacks;
//
//        memcached_set_processing_input((Memcached *)instance->root, true);
//
//        char buffer[MEMCACHED_DEFAULT_COMMAND_SIZE];
//        Memcached *root= (Memcached *)instance->root;
//        memcached_return_t error= memcached_response(instance, buffer, sizeof(buffer), &root->result);
//
//        memcached_set_processing_input(root, false);
//
//        if (error == MEMCACHED_SUCCESS)
//        {
//            for (unsigned int x= 0; x < cb.number_of_callback; x++)
//            {
//                error= (*cb.callback[x])(instance->root, &root->result, cb.context);
//                if (error != MEMCACHED_SUCCESS)
//                {
//                    break;
//                }
//            }
//
//            /* @todo what should I do with the error message??? */
//        }
//        /* @todo what should I do with other error messages?? */
//        return true;
//    }

    return false;
}


void memcached_quit_server(memcached_instance_st* instance, bool io_death)
{
//    if (instance->valid())
//    {
//        if (io_death == false and memcached_is_udp(instance->root) == false and instance->is_shutting_down() == false)
//        {
//            send_quit_message(instance);
//
//            instance->start_close_socket();
//            drain_instance(instance);
//        }
//    }
//
//    instance->close_socket();
//
//    if (io_death and memcached_is_udp(instance->root))
//    {
//        /*
//           If using UDP, we should stop using the server briefly on every IO
//           failure. If using TCP, it may be that the connection went down a
//           short while ago (e.g. the server failed) and we've only just
//           noticed, so we should only set the retry timeout on a connect
//           failure (which doesn't call this method).
//           */
//        memcached_mark_server_for_timeout(instance);
//    }
}



static bool io_flush(memcached_instance_st* instance,
                     const bool with_flush,
                     memcached_return_t& error)
{
    /*
     ** We might want to purge the input buffer if we haven't consumed
     ** any output yet... The test for the limits is the purge is inline
     ** in the purge function to avoid duplicating the logic..
   */
//    {
//        if (memcached_purge(instance) == false)
//        {
//            return false;
//        }
//    }
    char *local_write_ptr= instance->write_buffer;
    size_t write_length= instance->write_buffer_offset;

    error= MEMCACHED_SUCCESS;

    while (write_length)
    {

        int flags;
        if (with_flush)
        {
            flags= MSG_NOSIGNAL;
        }
        else
        {
            flags= MSG_NOSIGNAL|MSG_MORE;
        }

        ssize_t sent_length= ::send(instance->fd, local_write_ptr, write_length, flags);
         int local_errno= get_socket_errno(); // We cache in case memcached_quit_server() modifies errno

        if (sent_length == SOCKET_ERROR)
        {
            switch (get_socket_errno())
            {
                case ENOBUFS:
                    continue;

                case EAGAIN:
                {
                    /*
                     * We may be blocked on write because the input buffer
                     * is full. Let's check if we have room in our input
                     * buffer for more data and retry the write before
                     * waiting..
                   */
                    if (repack_input_buffer(instance) or process_input_buffer(instance))
                    {
                        continue;
                    }

                    memcached_return_t rc= io_wait(instance, POLLOUT);
                    if (memcached_success(rc))
                    {
                        continue;
                    }
                    else if (rc == MEMCACHED_TIMEOUT)
                    {
                        return false;
                    }

                    memcached_quit_server(instance, true);
                    return false;
                }
                case ENOTCONN:
                case EPIPE:
                default:
                    memcached_quit_server(instance, true);
                    return false;
            }
        }

        instance->io_bytes_sent+= uint32_t(sent_length);

        local_write_ptr+= sent_length;
        write_length-= uint32_t(sent_length);
    }

    instance->write_buffer_offset= 0;
    return true;
}


static bool _io_write(memcached_instance_st* instance,
                      const void *buffer, size_t length, bool with_flush,
                      size_t& written)
{

    const char *buffer_ptr= static_cast<const char *>(buffer);

    const size_t original_length= length;

    while (length)
    {
        char *write_ptr;
        size_t buffer_end= MEMCACHED_MAX_BUFFER;
        size_t should_write= buffer_end -instance->write_buffer_offset;
        should_write= (should_write < length) ? should_write : length;

        write_ptr= instance->write_buffer + instance->write_buffer_offset;
        memcpy(write_ptr, buffer_ptr, should_write);
        instance->write_buffer_offset+= should_write;
        buffer_ptr+= should_write;
        length-= should_write;

        if (instance->write_buffer_offset == buffer_end)
        {
            memcached_return_t rc;
            if (io_flush(instance, with_flush, rc) == false)
            {
                written= original_length -length;
                return false;
            }
        }
    }

    if (with_flush)
    {
        memcached_return_t rc;
        if (io_flush(instance, with_flush, rc) == false)
        {
            written= original_length -length;
            return false;
        }
    }

    written= original_length -length;

    return true;
}


bool memcached_io_write(memcached_instance_st* instance)
{
    size_t written;
    return _io_write(instance, NULL, 0, true, written);
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

    if (with_flush)
    {
        if (memcached_io_write(instance) == false)
        {
            return false;
        }
    }
    return (complete_total == total);
}





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

