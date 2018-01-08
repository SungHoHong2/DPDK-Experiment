### LOAD BALANCING

```c
// init eal
ret = rte_eal_init(argc, argv);

/* Parse application arguments (after the EAL ones) */
ret = app_parse_args(argc, argv);

app_init();
```

> [step into app_init()](app_init.md)

```c

/* Launch per-lcore init on every lcore */
rte_eal_mp_remote_launch(app_lcore_main_loop, NULL, CALL_MASTER);
RTE_LCORE_FOREACH_SLAVE(lcore) {
  if (rte_eal_wait_lcore(lcore) < 0) {
    return -1;
  }
}

```

> [app_lcore_main_loop](app_lcore_main_loop.md)
