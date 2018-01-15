

### SEASTAR with 2 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   594.50us   10.82us   0.95ms   92.62%
  Req/Sec     1.68k     4.57     1.72k    96.53%
33837 requests in 10.10s, 25.11MB read           
Requests/sec:   3350.31                            
Transfer/sec:      2.49MB                          


./wrk -t4 -c4 -d10s http://10.218.111.253:10000




./wrk -t8 -c8 -d10s http://10.218.111.253:10000
./wrk -t16 -c16 -d10s http://10.218.111.253:10000
./wrk -t32 -c32 -d10s http://10.218.111.253:10000
./wrk -t64 -c64 -d10s http://10.218.111.253:10000
```

### F-STACK with 2 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.252:10000
./wrk -t4 -c4 -d10s http://10.218.111.252:10000
./wrk -t8 -c8 -d10s http://10.218.111.252:10000
./wrk -t16 -c16 -d10s http://10.218.111.252:10000
./wrk -t32 -c32 -d10s http://10.218.111.252:10000
./wrk -t64 -c64 -d10s http://10.218.111.252:10000
```


### SEASTAR with 4 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   594.50us   10.82us   0.95ms   92.62%
  Req/Sec     1.68k     4.57     1.72k    96.53%
33837 requests in 10.10s, 25.11MB read           
Requests/sec:   3350.31                            
Transfer/sec:      2.49MB                          


./wrk -t4 -c4 -d10s http://10.218.111.253:10000




./wrk -t8 -c8 -d10s http://10.218.111.253:10000
./wrk -t16 -c16 -d10s http://10.218.111.253:10000
./wrk -t32 -c32 -d10s http://10.218.111.253:10000
./wrk -t64 -c64 -d10s http://10.218.111.253:10000
```

### F-STACK with 4 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.252:10000
./wrk -t4 -c4 -d10s http://10.218.111.252:10000
./wrk -t8 -c8 -d10s http://10.218.111.252:10000
./wrk -t16 -c16 -d10s http://10.218.111.252:10000
./wrk -t32 -c32 -d10s http://10.218.111.252:10000
./wrk -t64 -c64 -d10s http://10.218.111.252:10000
```



### SEASTAR with 8 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   594.50us   10.82us   0.95ms   92.62%
  Req/Sec     1.68k     4.57     1.72k    96.53%
33837 requests in 10.10s, 25.11MB read           
Requests/sec:   3350.31                            
Transfer/sec:      2.49MB                          


./wrk -t4 -c4 -d10s http://10.218.111.253:10000




./wrk -t8 -c8 -d10s http://10.218.111.253:10000
./wrk -t16 -c16 -d10s http://10.218.111.253:10000
./wrk -t32 -c32 -d10s http://10.218.111.253:10000
./wrk -t64 -c64 -d10s http://10.218.111.253:10000
```

### F-STACK with 8 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.252:10000
./wrk -t4 -c4 -d10s http://10.218.111.252:10000
./wrk -t8 -c8 -d10s http://10.218.111.252:10000
./wrk -t16 -c16 -d10s http://10.218.111.252:10000
./wrk -t32 -c32 -d10s http://10.218.111.252:10000
./wrk -t64 -c64 -d10s http://10.218.111.252:10000
```
