export MPICC=/home/sungho/mpich
export PATH=/home/you/mpich-install/bin:$PATH
sudo git pull origin master
wait
if [ "$1" = "mpi_send_recv" ]
then
mpicc -o mpi-send-recv mpi-send-recv.c
wait
# mpirun -n 2 -hostfile hosts_file ./mpi-send-recv
mpirun -n 2 ./send_recv
fi
