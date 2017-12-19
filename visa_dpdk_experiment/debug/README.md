### VISA-DPDK

```c
int main()
{
    int ret;
    ret = vd_dpdk_init(0, "helloworld");
    if (ret < 0) {
        printf("DPDK initialize fail\n");
    }
    show_conn();
    show_rsmgr();
    return 1;
}

```

> vd_dpdk_init

```c
int vd_dpdk_init(uint8_t portid, char *name)
{
    int ret, nb_ports;

    ret = vd_init_parsed(0, name);
    printf("Try to init eal!\n");

```

> [vd_init_parsed](vd_init_parsed.md)

```c
    ret = rte_eal_init(vd_gconf.args_count, vd_gconf.vd_eal_args);
    if (ret < 0)
        printf("Cannot initial eal!\n");

    nb_ports = rte_eth_dev_count();
    if (nb_ports == 0)
        rte_exit(EXIT_FAILURE, "No Ethernet ports\n");

    return ret;
}
```
