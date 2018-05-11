export MPICC=/home/sungho/mpich
export PATH=/home/sungho/mpich/bin:$PATH
sudo git pull origin master


if [ "$1" = "" ]
then
echo "I will just update"

else
sudo mpicc -o $1 $1.c
wait
echo ./mpirun -n 2 -hostfile hosts_file ./$1
fi
