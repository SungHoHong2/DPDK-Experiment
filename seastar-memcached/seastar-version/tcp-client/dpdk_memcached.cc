#include "dpdk_memcached.hh"


memcached_return_t memcached_set(memcached_st *ptr, const char *key, size_t key_length,
                                 const char *value, size_t value_length,
                                 time_t expiration,
                                 uint32_t flags)
{
    std::cout << "dpdk_memcached_set BEGIN" << std::endl;
//    memcached_return_t rc;
//    LIBMEMCACHED_MEMCACHED_SET_START();
//    rc= memcached_send(ptr, key, key_length,
//                       key, key_length, value, value_length,
//                       expiration, flags, 0, SET_OP);
//    LIBMEMCACHED_MEMCACHED_SET_END();

    std::cout << "dpdk_memcached_set END" << std::endl;
    return rc;
}

