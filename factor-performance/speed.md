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
default pipe size: 65536  
new pipe size: 1048576    
```


<br>


### NIC
```
lspci | egrep -i --color 'network|ethernet'
/sbin/ifconfig -a
```

```
//visasu
eth3      Link encap:Ethernet  HWaddr e4:1d:2d:d9:b6:41                    
          inet addr:10.107.30.32  Bcast:10.107.31.255  Mask:255.255.254.0  
          inet6 addr: fe80::e61d:2dff:fed9:b641/64 Scope:Link              
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1               
          RX packets:112026203 errors:0 dropped:0 overruns:0 frame:0       
          TX packets:57654380 errors:0 dropped:0 overruns:0 carrier:0      
          collisions:0 txqueuelen:1000                                     
          RX bytes:45048490641 (45.0 GB)  TX bytes:6105769414 (6.1 GB)   


//fiu test
enp1s0f0  Link encap:Ethernet  HWaddr 0c:c4:7a:3a:35:70                     
          inet addr:172.23.10.14  Bcast:172.23.255.255  Mask:255.255.0.0    
          inet6 addr: fe80::ec4:7aff:fe3a:3570/64 Scope:Link                
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1                
          RX packets:123186745 errors:0 dropped:4701891 overruns:0 frame:0  
          TX packets:119059518 errors:0 dropped:0 overruns:0 carrier:0      
          collisions:0 txqueuelen:1000                                      
          RX bytes:117299854836 (117.2 GB)  TX bytes:107106776457 (107.1 GB)

ib0       Link encap:UNSPEC  HWaddr A0-00-02-20-FE-80-00-00-00-00-00-00-00-00-00-00
          inet addr:172.24.30.31  Bcast:172.24.255.255  Mask:255.255.0.0           
          inet6 addr: fe80::7efe:9003:9a:7c31/64 Scope:Link                        
          UP BROADCAST RUNNING MULTICAST  MTU:2044  Metric:1                       
          RX packets:433544198 errors:0 dropped:0 overruns:0 frame:0               
          TX packets:143519518 errors:0 dropped:0 overruns:0 carrier:0             
          collisions:0 txqueuelen:256                                              
          RX bytes:690295877922 (690.2 GB)  TX bytes:660085999769 (660.0 GB)       
```
