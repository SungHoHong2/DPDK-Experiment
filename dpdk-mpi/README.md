### DPDK-MPI

**in case your MPI library is not working properly**
```
sudo apt-get purge mpi openmpi-common
```

```
export MPICC=/home/sungho/mpich
export PATH=/home/sungho/mpich/bin:$PATH

mpicc -o hellow hellow.c
mpirun -n 4 -hostfile hosts_file ./hellow
mpirun -n 4 ./hellow

mpiexec -f hosts_file -n 2 ./hellow
```

**HYD experiment**
```c++
gdb --args mpirun -n 2 ./mpi-send-recv
ui/mpich/mpiexec.c:152
ui/mpich/mpiexec.c:335  /* Launch the processes */
pm/pmiserv/pmiserv_pmci.c:95
tools/bootstrap/src/bsci_launch.c:12
tools/bootstrap/external/external_common_launch.c:102
// ssh connection is made for the number of processes
tools/bootstrap/external/external_common_launch.c:181
tools/bootstrap/external/external_common_launch.c:324  // POLLING
tools/demux/demux.c:80
      HYD_status HYDT_dmx_register_fd(int num_fds, int *fd, HYD_event_t events, void *userp,
      HYD_status(*callback) (int fd, HYD_event_t events, void *userp))
ui/mpich/mpiexec.c:343  /* Wait for their completion */
      status = HYD_pmci_wait_for_completion(timeout);
      communication from process 1 of 2
      communication from process 0 of 2
      Number received is: 77
```

**socket send and recv**
- tested with `communication.c`

```c++
utils/sock/sock.c
utils/sock/sock.c:233 // when it reads from other node



```
