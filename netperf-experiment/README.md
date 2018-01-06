### Netperf Experiments

- **install**

```
git clone https://github.com/HewlettPackard/netperf.git
./autogen.sh
apt install texinfo
./configure
make
```

<br>


- **running**

```
// server wenji-wrk
// Starting netserver with host 'IN(6)ADDR_ANY' port '12865' and family AF_UNSPEC
cd src
./netserver

// client dkasu
cd src

./netperf -P 12865 -t TCP_RR -H 10.218.111.252 -- -r 1,1 -o P50_LATENCY,P90_LATENCY,P99_LATENCY
```

<br>

| commands | description |
| -- | -- |
| -H | server ip address |
| -m | size of the packet |
| -l | elapsed time |
| -o | used for creating latency features [optional]|


<br>


- **building netserver**
```
./netperf -H 10.218.111.252 -l 5 -- -m 2048 -o P99_LATENCY

./netserver --conf config_server.ini --proc-type=primary --proc-id=0
```
