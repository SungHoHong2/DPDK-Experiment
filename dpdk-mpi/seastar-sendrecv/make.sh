sudo git pull origin master
wait
sudo make
wait
gcc daemon-interface.c -o daemon-interface

echo ./tcp_test --smp 1 --server "10.218.111.252:1234"
echo ./tcp_test --smp 1 --server "10.218.104.170:1234"
