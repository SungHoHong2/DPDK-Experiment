```
1) Use gdb 7.10 or 7.11.  7.7 doesn't work.
2) Ensure that gdb's python libraries are installed
3) When using gdb, link against Seastar's release library, not the debug library.
4) Create a .gdbinit in my project directory with the following lines:
handle SIG34 noprint nostop
handle SIG35 noprint nostop
handle SIGUSR1 noprint nostop
5) Add this to my ~/.gdbinit
add-auto-load-safe-path /path/to/my/project/.gdbinit
```

**memcached.cc**
```c++
apps/memcached/memcache.cc:1412
apps/memcached/memcache.cc:1423
apps/memcached/memcache.cc:1426

app.run_deprecated(ac, av, [&]);
    cache_peers.start();
    tcp_server.start(sharded_cache& cache, distributed<system_stats>& system_stats);
    udp_server.start(sharded_cache& cache, distributed<system_stats>& system_stats);
```

**memcached.hh**

```c++
apps/memcached/memcached.hh

namespace memcache;
    class item;
    class cache;
        using cache_type = bi::unordered_set<item,bi::member_hook<item, item::hook_type, &item::_cache_link>, bi::power_2_buckets<true>, bi::constant_time_size<true>>;
```
