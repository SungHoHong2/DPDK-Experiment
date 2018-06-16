#ifndef DPDK_MEMCACHED_HH
#define DPDK_MEMCACHED_HH
#include <libmemcached/memcached.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

memcached_return_t dpdk_memcached_set(memcached_st *ptr, const char *key, size_t key_length,
                                 const char *value, size_t value_length,
                                 time_t expiration,
                                 uint32_t flags);
#endif
