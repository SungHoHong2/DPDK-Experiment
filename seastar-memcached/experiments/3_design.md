
```c++
int main();
    ms_global_struct_init();
        ms_sync_lock_init();
        ms_global.finish_warmup= false;
        ms_global.time_out= false;

    ms_setting_init_pre();
        memset(&ms_setting, 0, sizeof(ms_setting));
        // global character block size
        // array of servers
        // array of keys
        // array of values
        // fixed value size
        // expected throughput
        ms_setting.ncpu= ms_get_cpu_count();
        // the total number of running threads
        ms_setting.nthreads= DEFAULT_THREADS_NUM;
        ms_setting.nconns= DEFAULT_CONNS_NUM;
        ms_setting.run_time= DEFAULT_RUN_TIME;
        ms_setting.total_srv_cnt= MCD_SRVS_NUM_INIT;
        ms_setting.servers= (ms_mcd_server_t *)malloc((size_t)ms_setting.total_srv_cnt * sizeof(ms_mcd_server_t));
        ms_setting_slapmode_init_pre();
              ms_setting.exec_num= DEFAULT_EXE_NUM;
              // the percentage of data verification
              ms_setting.verify_percent= DEFAULT_VERIFY_RATE;
              // the percentage of expired data
              ms_setting.exp_ver_per= DEFAULT_VERIFY_RATE;
              // the percentage of overwritten data
              ms_setting.overwrite_percent= DEFAULT_OVERWRITE_RATE;
              ms_setting.mult_key_num= DEFAULT_DIV;
              ms_setting.fixed_value_size= 0;
              ms_setting.win_size= DEFAULT_WINDOW_SIZE;

    ms_options_parse(argc, argv);

    ms_setting_init_post();
        ms_get_serverlist(ms_setting.srv_str);
              memcached_server_st *server_pool;
              server_pool = memcached_servers_parse(str);
              for (uint32_t loop= 0; loop < memcached_server_list_count(server_pool); loop++)
                  strcpy(ms_setting.servers[ms_setting.srv_cnt].srv_host_name, server_pool[loop].hostname);
                  ms_setting.servers[ms_setting.srv_cnt].srv_port= server_pool[loop].port;
                  ms_setting.servers[ms_setting.srv_cnt].disconn_cnt= 0;
                  ms_setting.servers[ms_setting.srv_cnt].reconn_cnt= 0;
                  ms_setting.srv_cnt++;

                  srvs= (ms_mcd_server_t *)realloc( ms_setting.servers,
                                            (size_t)ms_setting.total_srv_cnt * sizeof(ms_mcd_server_t) * 2);

        ms_setting_slapmode_init_post();
              ms_setting.total_key_rng_cnt= KEY_RANGE_COUNT_INIT;
              ms_setting.key_distr=(ms_key_distr_t *)malloc((size_t)ms_setting.total_key_rng_cnt * sizeof(ms_key_distr_t));
              ms_setting.total_val_rng_cnt= VALUE_RANGE_COUNT_INIT;
              ms_setting.value_distr=(ms_value_distr_t *)malloc((size_t)ms_setting.total_val_rng_cnt * sizeof( ms_value_distr_t));

              // configuration of test mode such as FACEBOOK

              ms_build_distr();
                  /* calculate average value size and key size */
                  ms_calc_avg_size();

                  ms_setting.char_blk_size= RAND_CHAR_SIZE;
                  int key_scope_size=(int)((ms_setting.char_blk_size - RESERVED_RAND_CHAR_SIZE) / UNIT_ITEMS_COUNT)
                  ms_setting.distr= (ms_distr_t *)malloc(
                    sizeof(ms_distr_t) * ms_setting.win_size);

                    /**
                      *  character block is divided by how many different key
                      *  size, each different key size has the same size character
                      *  range.
                      */
                      for (int m= 0; m < units; m++)
                        for (int i= 0; i < UNIT_ITEMS_COUNT; i++)
                              ms_setting.distr[m * UNIT_ITEMS_COUNT + i].key_offset=
                              ADDR_ALIGN(key_scope_size * i);

                    /* initialize key size distribution */
                    /* initialize value distribution */
                    /* shuffle distribution */

                    /*
                     * according to the key and value distribution, to build the
                     * (key, value) pair distribution. the (key, value) pair
                     * distribution array is global
                     */
              ms_init_random_block();
              ms_print_setting();

        ms_stats_init();
              memset(&ms_stats, 0, sizeof(ms_stats_t));

        ms_thread_init();
              ms_thread_ctx=(ms_thread_ctx_t *)malloc(sizeof(ms_thread_ctx_t) * (size_t)ms_setting.nthreads);

              pthread_key_create(&ms_thread_key, NULL);

              /* Create threads after we've done all the epoll setup. */
              ms_create_worker(ms_worker_libevent, (void *)&ms_thread_ctx[i]);
                  static void ms_create_worker(void *(*func)(void *), void *arg)
                        pthread_create(&thread, &attr, func, arg)

                  static void *ms_worker_libevent(void *arg);
                        ms_set_thread_cpu_affinity(thread_ctx->thd_idx %  ms_setting.ncpu);
                        ms_clock_handler(0, 0, 0);
                        ms_thread= pthread_getspecific(ms_thread_key);
                        event_base_loop(ms_thread->base, 0); // is this from posix

                        static int ms_setup_thread(ms_thread_ctx_t *thread_ctx)
                              int ms_setup_conn(ms_conn_t *c)
                              static int ms_conn_init(ms_conn_t *c,
                                                      const int init_state,
                                                      const int read_buffer_size,
                                                      const bool is_udp)
                              c->msglist= (struct msghdr *)malloc(
                                sizeof(struct msghdr) * (size_t)c->msgsize);
                              if (ms_setting.mult_key_num > 1){
                                c->mlget_task.mlget_item= (ms_mlget_task_item_t *)
                                                          malloc(
                                  sizeof(ms_mlget_task_item_t) * (size_t)ms_setting.mult_key_num);
                              }

                              ms_thread->base= event_init(); // this is also in posix
                              static int ms_conn_event_init(ms_conn_t *c)
                                    void ms_event_handler(const int fd, const short which, void *arg) // it is using lib event
                                          static void ms_drive_machine(ms_conn_t *c)
                                                static int ms_transmit(ms_conn_t *c)
                                                        res= sendmsg(c->sfd, m, 0);

        ms_monitor_slap_mode(); // wait until the threads are complete
        ms_thread_cleanup();
        ms_global_struct_destroy();
        ms_setting_cleanup();
```
