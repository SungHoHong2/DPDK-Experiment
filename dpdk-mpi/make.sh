export MPICC=/home/sungho/mpich
export PATH=/home/you/mpich-install/bin:$PATH

if [ "$1" = "mpi_send_recv" ]
then
mpicc -o mpi-send-recv mpi-send-recv.c
wait
mpirun -n 4 -hostfile hosts_file ./mpi-send-recv


fi
