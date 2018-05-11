export MPICC=/home/sungho/mpich
export PATH=/home/sungho/mpich/bin:$PATH
sudo git pull origin master

sudo mpicc -o $1 $1.c
mpirun -n 2 -hostfile hosts_file ./$1
