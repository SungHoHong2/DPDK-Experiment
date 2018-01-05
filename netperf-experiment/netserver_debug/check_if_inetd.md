```c
static void
check_if_inetd() { 

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  if (not_inetd) {
    return;
  }
  else {
#if !defined(WIN32) && !defined(__VMS)
    struct sockaddr_storage name;
    netperf_socklen_t namelen;

    namelen = sizeof(name); // active
    if (getsockname(0, // active
		    (struct sockaddr *)&name, // active
		    &namelen) == SOCKET_ERROR) { // active
      not_inetd = 1; // active
    }
    else {
      not_inetd = 0;
      child = 1;
    }
#endif
  }
}
```
