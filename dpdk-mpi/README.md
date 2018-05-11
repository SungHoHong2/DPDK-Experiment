### DPDK-MPI

```
export MPICC=/home/sungho/mpich
export PATH=/home/you/mpich-install/bin:$PATH

mpicc -o hellow hellow.c
mpirun -n 4 -hostfile hosts_file ./hellow
mpiexec -f hosts_file -n 2 ./hellow
```
