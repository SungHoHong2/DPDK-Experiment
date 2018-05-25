**memcached**
```c++
int main()
  while (-1 != (c = getopt(argc, argv, shortopts)))
    do_daemonize = true;
    settings.maxbytes = ((size_t)atoi(optarg)) * 1024 * 1024
    settings.port = atoi(optarg);
    tcp_specified = true;
    use_slab_sizes = false;
    settings.num_threads_per_udp = settings.num_threads;


/* daemonize if requested */
memcached.c:7557
if (do_daemonize) {
    daemonize(maxcore, settings.verbose);
}

int daemonize(int nochdir, int noclose)
    fork()

```

**memcached_client**
```
static void *ms_worker_libevent(void *arg)
ms_set_thread_cpu_affinity(thread_ctx->thd_idx %  ms_setting.ncpu);
```
