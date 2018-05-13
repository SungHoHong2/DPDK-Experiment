sudo git pull origin master
wait
sudo g++ -g parent.cc  -O2  -lrt  -lboost_system  -lpthread -o parent
sudo g++ -g child.cc  -O2  -lrt  -lboost_system  -lpthread -o child

wait
echo ./parent
echo ./child
