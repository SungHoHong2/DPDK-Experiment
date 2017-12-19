### LOAD BALANCING

```c
// init eal
ret = rte_eal_init(argc, argv);

/* Parse application arguments (after the EAL ones) */
ret = app_parse_args(argc, argv);

app_init();
```

- [step into app_init()](app_init.md)
