```c
int _cdecl
main(int argc, char *argv[]) {

  program = (char * )malloc(strlen(argv[0]) + 1); // active
  if (program == NULL) {
    printf("malloc for program name failed!\n");
    return -1 ;
  }
  strcpy(program, argv[0]); // active

  init_netserver_globals();
```
> [init_netserver_globals](init_netserver_globals.md)

```c
  netlib_init();
```

> [netlib_init](netlib_init.md)

```c
  strncpy(local_host_name,"",sizeof(local_host_name)); // active
  local_address_family = AF_UNSPEC;  // active
  strncpy(listen_port,TEST_PORT,sizeof(listen_port)); // active

  scan_netserver_args(argc, argv);

```

> [scan_netserver_args](scan_netserver_args.md)

```c
  check_if_inetd(); //active

```

> [check_if_inetd](check_if_inetd.md)

```c
  if (daemon_parent) { // active
    setup_listens(local_host_name,listen_port,local_address_family); // active
    if (want_daemonize) { // active
      daemonize(); // active
    }
  }
}
```
> [setup_listens](setup_listens.md) <br>
> [daemonize](daemonize.md)
