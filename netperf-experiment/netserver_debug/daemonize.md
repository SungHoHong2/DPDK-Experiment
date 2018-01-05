```c
void
daemonize() {
#if defined(HAVE_FORK)

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  /* flush the usual suspects */
  fflush(stdin);
  fflush(stdout);
  fflush(stderr);

  switch (fork()) {
  case -1:
    fprintf(stderr,
	    "%s: fork() error %s (errno %d)\n",
	    __FUNCTION__,
	    strerror(errno),
	    errno);
    fflush(stderr);
    exit(1);
  case 0:

    /* perhaps belt and suspenders, but if we dump core, perhaps
       better to do so here. we won't worry about the call being
       successful though. raj 2011-07-08 */
    chdir(DEBUG_LOG_FILE_DIR);

    /* we are the child. we should get a new "where" to match our new
       pid */

    open_debug_file();

#ifdef HAVE_SETSID
      setsid();
#else
      setpgrp();
#endif /* HAVE_SETSID */

      signal(SIGCLD, SIG_IGN);

      /* ok, we can start accepting control connections now */
      accept_connections();

  default:
    /* we are the parent, nothing to do but exit? */
    exit(0);
  }

#else
  fprintf(where,
	  "%s called on platform which cannot daemonize\n",
	  __FUNCTION__);
  fflush(where);
  exit(1);
#endif /* HAVE_FORK */
}
```
