sudo git pull origin master
wait
sudo make
wait
sudo gcc daemon-interface.c -o daemon-interface

echo ./seastar-daemon --smp 1 --server "10.218.111.252:1234"
echo ./seastar-daemon --smp 1 --server "10.218.104.170:1234"
