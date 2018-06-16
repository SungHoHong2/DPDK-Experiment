#include <libmemcached/memcached.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



int main(){
    std::cout << "memcached BEGIN" << std::endl;


    memcached_server_st *servers = NULL;
    memcached_st *memc;
    memcached_return rc;
    char *key = "keystring";
    char *value = "keyvalue";

    char *retrieved_value;
    size_t value_length;
    uint32_t flags;

    memc = memcached_create(NULL);
    servers = memcached_server_list_append(servers, "10.107.30.40", 11211, &rc);
    rc = memcached_server_push(memc, servers);

    if (rc == MEMCACHED_SUCCESS)
      fprintf(stderr, "Added server successfully\n");
    else
      fprintf(stderr, "Couldn't add server: %s\n", memcached_strerror(memc, rc));


    std::cout << "memcached END" << std::endl;
    return 0;
}
