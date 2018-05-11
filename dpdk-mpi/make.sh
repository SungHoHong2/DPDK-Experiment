export MPICC=/home/sungho/mpich
export PATH=/home/you/mpich-install/bin:$PATH
sudo git pull origin master

if [ "$1" = "mpi_send_recv" ]
then
mpicc -o mpi-send-recv mpi-send-recv.c
wait
mpirun -n 1 -hostfile hosts_file ./mpi-send-recv
fi
