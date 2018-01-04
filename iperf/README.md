### IPerf

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
# server
iperf -s / iperf3 -s

# client
iperf/iperf3 -c remotehost -i 1 -t 30	 // Run a 30 second tests, giving results every 1 second
```


<br>
