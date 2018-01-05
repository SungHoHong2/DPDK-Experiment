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

    namelen = sizeof(name);
    if (getsockname(0,
		    (struct sockaddr *)&name,
		    &namelen) == SOCKET_ERROR) {
      not_inetd = 1;
    }
    else {
      not_inetd = 0;
      child = 1;
    }
#endif
  }
}
```
