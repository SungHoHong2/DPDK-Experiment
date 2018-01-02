### Baseline
  - it is definitely faster

```
// DPDK
PING 10.218.111.254 (10.218.111.254) 56(84) bytes of data.   
64 bytes from 10.218.111.254: icmp_seq=1 ttl=64 time=0.630 ms
64 bytes from 10.218.111.254: icmp_seq=2 ttl=64 time=0.348 ms
64 bytes from 10.218.111.254: icmp_seq=3 ttl=64 time=0.346 ms
64 bytes from 10.218.111.254: icmp_seq=4 ttl=64 time=0.446 ms
64 bytes from 10.218.111.254: icmp_seq=5 ttl=64 time=0.432 ms
64 bytes from 10.218.111.254: icmp_seq=6 ttl=64 time=0.469 ms

// TCP
PING 10.218.111.252 (10.218.111.252) 56(84) bytes of data.   
64 bytes from 10.218.111.252: icmp_seq=1 ttl=64 time=0.627 ms
64 bytes from 10.218.111.252: icmp_seq=2 ttl=64 time=0.488 ms
64 bytes from 10.218.111.252: icmp_seq=3 ttl=64 time=0.512 ms
64 bytes from 10.218.111.252: icmp_seq=4 ttl=64 time=0.626 ms
64 bytes from 10.218.111.252: icmp_seq=5 ttl=64 time=0.614 ms
64 bytes from 10.218.111.252: icmp_seq=6 ttl=64 time=0.716 ms
```

<br>

### DPDK

```

// 64
// DPDK  TCP
90105    18509
89550    18365
90326    18583

// 128
89525  
89572
89795

// 256
79785
79437
79570

// 512
86528
90099
90480

// 1024
200212
201816
200616

// 1518
156752
284556
284871

// 2048
405462
404243
404050

// 3000
594670
596209
596539

```

### TCP

```



```
