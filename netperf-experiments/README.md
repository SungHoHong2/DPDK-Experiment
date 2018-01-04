### Netperf Experiments

- **install**

```
git clone https://github.com/HewlettPackard/netperf.git
./autogen
./configure
make
```

<br>


- **running**

```
// server wenji-wrk
cd src
./netserver

// client dkasu
cd src
./netperf -P 0 -t TCP_RR -H 10.218.111.252 -- -r 1,1 -o P50_LATENCY,P90_LATENCY,P99_LATENCY
```

<br>
