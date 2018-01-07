### speed
Pipes and FIFOs (also known as named pipes) provide a unidirectional
interprocess communication channel.  A pipe has a read end and a
write end.  Data written to the write end of a pipe can be read from
the read end of the pipe. <br> 
[pipe-size.c](pipesize.c)

```
// pipesize
cat /proc/sys/fs/pipe-max-size
echo "testdata" | ./pipe-size
```

```
// visasu
default pipe size: 65536
new pipe size: 1048576  


//fiu

```


<br>


### NIC
```
lspci | egrep -i --color 'network|ethernet'
/sbin/ifconfig -a
```

```
eth3      Link encap:Ethernet  HWaddr e4:1d:2d:d9:b6:41                    
          inet addr:10.107.30.32  Bcast:10.107.31.255  Mask:255.255.254.0  
          inet6 addr: fe80::e61d:2dff:fed9:b641/64 Scope:Link              
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1               
          RX packets:112026203 errors:0 dropped:0 overruns:0 frame:0       
          TX packets:57654380 errors:0 dropped:0 overruns:0 carrier:0      
          collisions:0 txqueuelen:1000                                     
          RX bytes:45048490641 (45.0 GB)  TX bytes:6105769414 (6.1 GB)     
```
