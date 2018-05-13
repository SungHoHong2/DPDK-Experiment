sudo git pull origin master
wait
all:
sudo g++ -g parent.cc  -O2  -lrt  -lboost_system  -lpthread -o parent

wait
echo ./tcp_test --smp 1 --server "10.218.111.252:1234"
echo ./tcp_test --smp 1 --server "10.218.104.170:1234"
