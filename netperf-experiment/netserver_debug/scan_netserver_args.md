```c
void
scan_netserver_args(int argc, char *argv[]) {

  int c;
  char arg1[BUFSIZ], arg2[BUFSIZ];

  if (debug) {
    fprintf(where,
	    "%s: enter\n",
	    __FUNCTION__);
    fflush(where);
  }

  while ((c = getopt(argc, argv, SERVER_ARGS)) != EOF){
    switch (c) {
    case '?':
    case 'h':
      print_netserver_usage();
      exit(1);
    case 'd':
      debug++;
      suppress_debug = 0;
      break;
    case 'D':
      /* perhaps one of these days we'll take an argument */
      want_daemonize = 0;
      not_inetd = 1;
      break;
    case 'f':
      spawn_on_accept = 0;
      not_inetd = 1;
      break;
#ifdef WIN32
    case 'I':
      child = TRUE;
      break;
    case 'i':
      break;
#endif
    case 'L':
      not_inetd = 1;
      break_args_explicit(optarg,arg1,arg2);
      if (arg1[0]) {
	strncpy(local_host_name,arg1,sizeof(local_host_name));
      }
      if (arg2[0]) {
	local_address_family = parse_address_family(arg2);
      }
      break;
    case 'n':
      shell_num_cpus = atoi(optarg);
      if (shell_num_cpus > MAXCPUS) {
	fprintf(stderr,
		"netserver: This version can only support %d CPUs. Please"
		"increase MAXCPUS in netlib.h and recompile.\n",
		MAXCPUS);
	fflush(stderr);
	exit(1);
      }
      break;
    case 'N':
      suppress_debug = 1;
      debug = 0;
      break;
    case 'p':
      /* we want to open a listen socket at a specified port number */
      strncpy(listen_port,optarg,sizeof(listen_port));
      not_inetd = 1;
      break;
    case 'Z':
      /* only copy as much of the passphrase as could fit in the
	 test-specific portion of a control message. Windows does not
	 seem to have a strndup() so just malloc and strncpy it.  we
	 weren't checking the strndup() return so won't bother with
	 checking malloc(). we will though make certain we only
	 allocated it once in the event that someone puts -Z on the
	 command line more than once */
      if (passphrase == NULL)
	passphrase = malloc(sizeof(netperf_request.content.test_specific_data));
      strncpy(passphrase,
	      optarg,
	      sizeof(netperf_request.content.test_specific_data));
      passphrase[sizeof(netperf_request.content.test_specific_data) - 1] = '\0';
      break;
    case '4':
      local_address_family = AF_INET;
      break;
    case '6':
#if defined(AF_INET6)
      local_address_family = AF_INET6;
#else
      local_address_family = AF_UNSPEC;
#endif
      break;
    case 'v':
      /* say how much to say */
      verbosity = atoi(optarg);
      break;
    case 'V':
      printf("Netperf version %s\n",NETPERF_VERSION);
      exit(0);
      break;

    }
  }
}
```
