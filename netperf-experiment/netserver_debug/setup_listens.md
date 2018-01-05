```c
void setup_listens(char name[], char port[], int af) {

  int do_inet;
  int no_name = 0;
#ifdef AF_INET6
  int do_inet6;
#endif

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  if (strcmp(name,"") == 0) {
    no_name = 1;
    switch (af) {
    case AF_UNSPEC:
      do_inet = 1;
#ifdef AF_INET6
      do_inet6 = 1;
#endif
      break;
    case AF_INET:
      do_inet = 1;
#ifdef AF_INET6
      do_inet6 = 0;
#endif
      break;
#ifdef AF_INET6
    case AF_INET6:
      do_inet = 0;
      do_inet6 = 1;
      break;
#endif
    default:
      do_inet = 1;
    }
    /* if we have IPv6, try that one first because it may be a superset */
#ifdef AF_INET6
    if (do_inet6)
      create_listens("::0",port,AF_INET6);
#endif
    if (do_inet)
      create_listens("0.0.0.0",port,AF_INET);
  }
  else {
    create_listens(name,port,af);
  }

  if (listen_list) {
    fprintf(stdout,
	    "Starting netserver with host '%s' port '%s' and family %s\n",
	    (no_name) ? "IN(6)ADDR_ANY" : name,
	    port,
	    inet_ftos(af));
    fflush(stdout);
  }
  else {
    fprintf(stderr,
	    "Unable to start netserver with  '%s' port '%s' and family %s\n",
	    (no_name) ? "IN(6)ADDR_ANY" : name,
	    port,
	    inet_ftos(af));
    fflush(stderr);
    exit(1);
  }
}
```
