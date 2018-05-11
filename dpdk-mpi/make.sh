export MPICC=/home/sungho/mpich
export PATH=/home/sungho/mpich/bin:$PATH
sudo git pull origin master
wait
if [ "$1" = "hellow" ]
then
sudo mpicc -o hellow hellow.c
echo mpirun -n 4 -hostfile hosts_file ./hellow

elif [ "$1" = "mpi-send-recv" ]
then
sudo mpicc -o mpi-send-recv mpi-send-recv.c
echo mpirun -n 2 -hostfile hosts_file ./mpi-send-recv

fi
