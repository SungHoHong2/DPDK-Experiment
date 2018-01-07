### TCP in FIU
```
./wrk -t2 -c2 -d10s http://10.107.30.102



./wrk -t4 -c4 -d10s http://10.107.30.102
./wrk -t8-c8 -d10s http://10.107.30.102
./wrk -t16 -c16 -d10s http://10.107.30.102
./wrk -t32 -c32 -d10s http://10.107.30.102
./wrk -t64 -c64 -d10s http://10.107.30.102

```

<br>

### RDMA in FIU
```
./wrk -t2 -c2 -d10s http://10.107.30.102
./wrk -t4 -c4 -d10s http://10.107.30.102
./wrk -t8-c8 -d10s http://10.107.30.102
./wrk -t16 -c16 -d10s http://10.107.30.102
./wrk -t32 -c32 -d10s http://10.107.30.102
./wrk -t64 -c64 -d10s http://10.107.30.102

```
