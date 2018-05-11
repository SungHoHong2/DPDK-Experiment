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
mpiexec -f hosts_file -n 2 ./hellow
```

**MPI_SEND expeiment**
```c++
gdb --args mpirun -n 2 ./mpi-send-recv
ui/mpich/mpiexec.c:152
ui/mpich/mpiexec.c:335  /* Launch the processes */
pm/pmiserv/pmiserv_pmci.c:95
tools/bootstrap/src/bsci_launch.c:12
tools/bootstrap/external/external_common_launch.c:102


```
