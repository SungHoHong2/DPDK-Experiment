```c
void
netlib_init()
{
  int i;

  where = stdout;

  request_array = (int *)(&netperf_request);
  response_array = (int *)(&netperf_response);

  for (i = 0; i < MAXCPUS; i++) {
    lib_local_per_cpu_util[i] = -1.0;
  }

  lib_local_cpu_stats.peak_cpu_id = -1;
  lib_local_cpu_stats.peak_cpu_util = -1.0;
  lib_remote_cpu_stats.peak_cpu_id = -1;
  lib_remote_cpu_stats.peak_cpu_util = -1.0;

  netperf_version = strdup(NETPERF_VERSION);

  /* on those systems where we know that CPU numbers may not start at
     zero and be contiguous, we provide a way to map from a
     contiguous, starting from 0 CPU id space to the actual CPU ids.
     at present this is only used for the netcpu_looper stuff because
     we ass-u-me that someone setting processor affinity from the
     netperf commandline will provide a "proper" CPU identifier. raj
     2006-04-03 */

  netlib_init_cpu_map();

  if (debug) {
    fprintf(where,
            "netlib_init: request_array at %p\n"
            "netlib_init: response_array at %p\n",
            request_array,
            response_array);
    fflush(where);
  }

  /* some functionality might want to use random numbers, so we should
     initialize the random number generator */
  srand(getpid());

}
```
