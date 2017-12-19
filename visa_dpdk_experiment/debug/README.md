### VISA-DPDK

```c
int main()
{
    int ret;
    ret = vd_dpdk_init(0, "helloworld");


```

> [vd_dpdk_init](vd_dpdk_init.md)

```c
    if (ret < 0) {
        printf("DPDK initialize fail\n");
    }
    show_conn();
    show_rsmgr();
    return 1;
}

```
