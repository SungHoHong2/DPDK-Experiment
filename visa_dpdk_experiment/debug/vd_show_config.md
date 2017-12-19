### vd_show_config

```c
void vd_show_config(uint8_t port_id)
{
    int i = 0;
    for (i = 0; i < vd_gconf.args_count; i++)
        printf("%s ", vd_gconf.vd_eal_args[i]);
    printf("\n");
}
```
