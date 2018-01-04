### IPerf Experiments

- **install**

```
git clone https://github.com/esnet/iperf.git
./configure
make
make install
```

<br>


- **running**

```
// server 10.218.111.252
cd src
./iperf3 -s

// client
cd src
iperf/iperf3 -c remotehost -i 1 -t 30	 // Run a 30 second tests, giving results every 1 second
```

<br>
