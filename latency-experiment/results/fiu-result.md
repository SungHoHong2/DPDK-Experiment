### TCP in FIU
```
./wrk -t2 -c2 -d1s 172.23.10.15:8888

./wrk -t4 -c4 -d10s http://10.107.30.102:8888
./wrk -t8-c8 -d10s http://10.107.30.102
./wrk -t16 -c16 -d10s http://10.107.30.102
./wrk -t32 -c32 -d10s http://10.107.30.102
./wrk -t64 -c64 -d10s http://10.107.30.102

```

<br>

### RDMA in FIU
```
./wrk -t2 -c2 -d10s http://172.24.30.30:8888
./wrk -t4 -c4 -d10s http://10.107.30.102
./wrk -t8-c8 -d10s http://10.107.30.102
./wrk -t16 -c16 -d10s http://10.107.30.102
./wrk -t32 -c32 -d10s http://10.107.30.102
./wrk -t64 -c64 -d10s http://10.107.30.102

```
