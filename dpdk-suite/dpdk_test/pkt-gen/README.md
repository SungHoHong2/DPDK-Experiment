https://www.intel.com/content/dam/www/public/us/en/documents/guides/dpdk-testpmd-application-user-guide.pdf

### Running file
```
# 00:1B:21:A6:D4:D5
./app/x86_64-native-linuxapp-gcc/pktgen -l 0-4 -n 3 -- -P -m "[2:4].1" -f throughput.lua
```

### PKTGEN sending packet
```c++
/home/sungho/pktgen-3.4.2/app/pktgen-main.c:471            void pktgen_cli_start();
/home/sungho/pktgen-3.4.2/app/cli-functions.c:1430
/home/sungho/pktgen-3.4.2/lib/cli/cli.c:729
/home/sungho/pktgen-3.4.2/lib/cli/cli.c:707
/home/sungho/pktgen-3.4.2/lib/cli/cli.c:617                /* Process the input for the CLI from the user */
/home/sungho/pktgen-3.4.2/lib/cli/cli.c:644                /* Found a vt100 key sequence, execute function */
/home/sungho/pktgen-3.4.2/lib/cli/cli_vt100_keys.c:111
/home/sungho/pktgen-3.4.2/lib/cli/cli.c:503                // activiates when set 0 dst mac 00:1B:21:A6:D4:D5
/home/sungho/pktgen-3.4.2/app/cli-functions.c:426          int set_cmd(int argc, char **argv);
      argv[0] set
      argv[1] 0
      argv[2] mac
      argv[3] dst
      m->index  23
      void single_set_dst_mac(port_info_t *info, struct ether_addr *mac);

/home/sungho/pktgen-3.4.2/lib/cli/cli_string_fns.c:246
/home/sungho/pktgen-3.4.2/app/pktgen-cmds.c:1002
```

### LUI Script

```

```
