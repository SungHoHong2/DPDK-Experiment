### vd_arg_set


```c
void vd_arg_set(config_t *cfg, char *var_name,
                   char *var_symbol, const char *dst)
{
    int ret;

    ret = config_lookup_string(cfg, var_name, &dst);
    CHECK_RETURN(ret, var_name);
    vd_gconf.vd_eal_args[vd_gconf.args_count++] = var_symbol;
    ret = vd_set_eal_args(&vd_gconf.vd_eal_args[vd_gconf.args_count++],
                          dst);
}
```


```c
int vd_set_eal_args(char **dst, const char *src)
{
    *dst = (char*)malloc(strlen(src));
    if (!*dst) {
        printf("No Memory to allocate for args or src 0!\n");
        return 0;
    }
    strcpy(*dst, src);
    return strlen(src);
}
```
