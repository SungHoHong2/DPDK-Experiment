#include "dpdk_memcached.hh"
#include "dpdk_basic.hh"
#include "dpdk_error.hh"
#include "md5.hh"
#include <sys/time.h>
#include "dpdk_hash.hh"


#define memcached_is_buffering(__object) ((__object)->flags.buffer_requests)
#define memcached_is_encrypted(__object) ((__object)->hashkit._key)
#define memcached_is_replying(__object) ((__object)->flags.reply)


memcached_instance_st* memcached_instance_fetch(Memcached *ptr, uint32_t server_key)
{
    if (ptr == NULL)
    {
        return NULL;
    }

    return &ptr->servers[server_key];
}


hashkit_string_st* aes_encrypt(aes_key_t *_aes_key,
                               const char* source, size_t source_length)
{
    if (_aes_key == NULL)
    {
        return NULL;
    }

    size_t num_blocks= source_length/AES_BLOCK_SIZE;

    hashkit_string_st* destination= hashkit_string_create(source_length);
    if (destination)
    {
        char *dest= hashkit_string_c_str_mutable(destination);

        for (size_t x= num_blocks; x > 0; x--)   /* Encode complete blocks */
        {
            rijndaelEncrypt(_aes_key->encode_key.rk, _aes_key->encode_key.nr, (const uint8_t*)(source),
                            (uint8_t*) (dest));
            source+= AES_BLOCK_SIZE;
            dest+= AES_BLOCK_SIZE;
        }

        uint8_t block[AES_BLOCK_SIZE];
        char pad_len= AES_BLOCK_SIZE - (source_length - AES_BLOCK_SIZE*num_blocks);
        memcpy(block, source, 16 -pad_len);
        memset(block + AES_BLOCK_SIZE -pad_len, pad_len, pad_len);
        rijndaelEncrypt(_aes_key->encode_key.rk, _aes_key->encode_key.nr, block, (uint8_t*) (dest));
        hashkit_string_set_length(destination, AES_BLOCK_SIZE*(num_blocks + 1));
    }

    return destination;
}


hashkit_string_st *hashkit_encrypt(hashkit_st *kit,
                                   const char* source, size_t source_length)
{
    return aes_encrypt(static_cast<aes_key_t*>(kit->_key), source, source_length);
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

