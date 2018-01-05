```c
void setup_listens(char name[], char port[], int af) {

  int do_inet; // active
  int no_name = 0;  //active
#ifdef AF_INET6
  int do_inet6;
#endif

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  if (strcmp(name,"") == 0) { //active
    no_name = 1; // active
    switch (af) {   // active
    case AF_UNSPEC:  // active
      do_inet = 1;  // active
#ifdef AF_INET6
      do_inet6 = 1;  // active
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
    /* if we have IPv6, try that one first because it may be a superset * /
#ifdef AF_INET6
    if (do_inet6)  // active
      create_listens("::0",port,AF_INET6);  // active
#endif
    if (do_inet)  // active
      create_listens("0.0.0.0",port,AF_INET);  // active
  }
  else {
    create_listens(name,port,af);
  }

  if (listen_list) {  // active
    fprintf(stdout,
	    "Starting netserver with host '%s' port '%s' and family %s\n",
	    (no_name) ? "IN(6)ADDR_ANY" : name,
	    port,
	    inet_ftos(af));  // active
    fflush(stdout);  // active
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
