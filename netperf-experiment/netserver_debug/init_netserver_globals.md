```c
static void
init_netserver_globals() {

#if defined(__VMS) || defined(VMWARE_UW)
  spawn_on_accept = 0;
  want_daemonize = 0;
#else
  spawn_on_accept = 1;
#if defined(WIN32)
  /* we only know how to spawn in WIN32, not daemonize */
  want_daemonize = 0;
#else
  want_daemonize = 1;
#endif /* WIN32 */
#endif /* __VMS || VMWARE_UW */

  child = 0;
  not_inetd = 0;
  netperf_daemon = 0;
}
```
