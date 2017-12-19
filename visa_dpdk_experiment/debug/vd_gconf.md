### vd_gconf

```c
typedef const char* arg_type;

struct vd_config {
    uint8_t port_id;
    arg_type core_mask;
    arg_type mem_channel;
    arg_type socket_mem;
    arg_type pmd_type;
    arg_type app_name;
    arg_type ip_addr;

    char* vd_eal_args[MAX_ARG_NUM];
    unsigned args_count;
} vd_gconf;

```
