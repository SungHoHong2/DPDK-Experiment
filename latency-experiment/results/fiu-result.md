### NIC configuration
```
enp1s0f0  Link encap:Ethernet  HWaddr 0c:c4:7a:3a:35:70                             
          inet addr:172.23.10.14  Bcast:172.23.255.255  Mask:255.255.0.0            
          inet6 addr: fe80::ec4:7aff:fe3a:3570/64 Scope:Link                        
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1                        
          RX packets:123139781 errors:0 dropped:4663880 overruns:0 frame:0          
          TX packets:119051016 errors:0 dropped:0 overruns:0 carrier:0              
          collisions:0 txqueuelen:1000                                              
          RX bytes:117292271669 (117.2 GB)  TX bytes:107105982365 (107.1 GB)        


ib0       Link encap:UNSPEC  HWaddr A0-00-02-20-FE-80-00-00-00-00-00-00-00-00-00-00
          inet addr:172.24.30.31  Bcast:172.24.255.255  Mask:255.255.0.0           
          inet6 addr: fe80::7efe:9003:9a:7c31/64 Scope:Link                        
          UP BROADCAST RUNNING MULTICAST  MTU:2044  Metric:1                       
          RX packets:433544198 errors:0 dropped:0 overruns:0 frame:0               
          TX packets:143519518 errors:0 dropped:0 overruns:0 carrier:0             
          collisions:0 txqueuelen:256                                              
          RX bytes:690295877922 (690.2 GB)  TX bytes:660085999769 (660.0 GB)       
```



### TCP in FIU
```
./wrk -t2 -c2 -d10s http://172.23.10.15:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   114.57us   12.22us 261.00us   53.88%  
Req/Sec     8.64k   204.93     9.49k    86.63%  
173666 requests in 10.10s, 107.65MB read          
Requests/sec:  17195.01                             
Transfer/sec:     10.66MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev           
Latency   118.66us   10.91us 206.00us   70.23%            
Req/Sec     8.34k   112.67     8.98k    82.18%            
167719 requests in 10.10s, 103.97MB read                    
Requests/sec:  16605.80                                       
Transfer/sec:     10.29MB                                     


Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   117.13us   16.86us 276.00us   70.83%
Req/Sec     8.46k   750.44     9.98k    82.18%
169849 requests in 10.10s, 105.29MB read         
Requests/sec:  16816.16                            
Transfer/sec:     10.42MB                          


./wrk -t4 -c4 -d10s http://172.23.10.15:8888
4 threads and 4 connections                        
Thread Stats   Avg      Stdev     Max   +/- Stdev  
Latency   138.92us    5.60us 268.00us   75.09%   
Req/Sec     7.14k    60.04     7.31k    66.83%   
287026 requests in 10.10s, 177.92MB read           
Requests/sec:  28419.15                              
Transfer/sec:     17.62MB                            

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   138.28us    5.64us 366.00us   72.30%
Req/Sec     7.18k    61.60     7.45k    87.38%
288470 requests in 10.10s, 178.82MB read         
Requests/sec:  28561.56                            
Transfer/sec:     17.70MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   138.34us    5.62us 227.00us   73.09%
Req/Sec     7.17k    40.55     7.38k    59.90%
288313 requests in 10.10s, 178.72MB read         
Requests/sec:  28547.80                            
Transfer/sec:     17.70MB                          

./wrk -t8 -c8 -d10s http://172.23.10.15:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   157.04us    7.91us 508.00us   77.59%  
Req/Sec     6.32k   204.32     7.03k    80.45%  
508488 requests in 10.10s, 315.21MB read          
Requests/sec:  50347.02                             
Transfer/sec:     31.21MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   157.47us    7.78us   1.06ms   80.50%  
Req/Sec     6.30k   171.15     7.10k    69.93%  
506727 requests in 10.10s, 314.11MB read          
Requests/sec:  50170.50                             
Transfer/sec:     31.10MB                           

8 threads and 8 connections                         
Thread Stats   Avg      Stdev     Max   +/- Stdev   
Latency   158.65us    7.86us   1.10ms   80.76%    
Req/Sec     6.26k   171.18     6.83k    77.10%    
503036 requests in 10.10s, 311.83MB read            
Requests/sec:  49805.64                               
Transfer/sec:     30.87MB                             


./wrk -t16 -c16 -d10s http://172.23.10.15:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev  
Latency   168.37us   17.79us 757.00us   74.87%   
Req/Sec     5.91k   122.84     6.27k    72.15%   
949622 requests in 10.10s, 588.66MB read           
Requests/sec:  94026.77                              
Transfer/sec:     58.29MB                            

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   169.84us   19.26us   1.25ms   73.28%
Req/Sec     5.86k   126.18     6.23k    79.64%
941523 requests in 10.10s, 583.64MB read         
Requests/sec:  93219.97                            
Transfer/sec:     57.79MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev  
Latency   170.38us   19.94us   1.11ms   72.14%   
Req/Sec     5.84k   104.43     6.22k    81.31%   
938454 requests in 10.10s, 581.74MB read           
Requests/sec:  92922.60                              
Transfer/sec:     57.60MB                            

./wrk -t32 -c32 -d10s http://172.23.10.15:8888
Running 10s test @ http://172.23.10.15:8888         
32 threads and 32 connections                     

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   202.98us   20.46us 586.00us   69.89%  
Req/Sec     4.91k    62.25     5.35k    78.37%  
1578731 requests in 10.10s, 0.96GB read           
Requests/sec: 156322.38                             
Transfer/sec:     96.90MB                           

32 threads and 32 connections                        
Thread Stats   Avg      Stdev     Max   +/- Stdev    
Latency   202.88us   20.40us 801.00us   69.97%     
Req/Sec     4.91k    61.13     5.35k    75.77%     
1579681 requests in 10.10s, 0.96GB read              
Requests/sec: 156408.18                                
Transfer/sec:     96.96MB                              

32 threads and 32 connections                     
Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   203.07us   20.53us 505.00us   69.79%  
Req/Sec     4.91k    63.03     5.30k    75.77%  
1578019 requests in 10.10s, 0.96GB read           
Requests/sec: 156246.73                             
Transfer/sec:     96.86MB                           


./wrk -t64 -c64 -d10s http://172.23.10.15:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   376.61us   22.12us 581.00us   71.50%
Req/Sec     2.66k    43.64     3.28k    91.06%
1708378 requests in 10.10s, 1.03GB read          
Requests/sec: 169145.48                            
Transfer/sec:    104.85MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev  
Latency   376.56us   22.50us   3.18ms   72.72%   
Req/Sec     2.66k    46.18     3.33k    91.41%   
1708514 requests in 10.10s, 1.03GB read            
Requests/sec: 169167.22                              
Transfer/sec:    104.86MB                            

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   376.58us   22.23us   1.18ms   71.48%  
Req/Sec     2.66k    46.03     3.26k    92.06%  
1708502 requests in 10.10s, 1.03GB read           
Requests/sec: 169169.70                             
Transfer/sec:    104.87MB                           
```

<br>

### RDMA in FIU
```
./wrk -t2 -c2 -d10s http://172.24.30.30:8888
2 threads and 2 connections                      
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    25.22us    2.60us 152.00us   64.14%
  Req/Sec    38.03k     2.70k   44.01k    64.36%
764213 requests in 10.10s, 473.73MB read         
Requests/sec:  75665.19                            
Transfer/sec:     46.90MB                          

2 threads and 2 connections                       
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    25.38us    2.74us 194.00us   72.13%  
  Req/Sec    37.76k     2.87k   43.64k    66.34%  
758562 requests in 10.10s, 470.22MB read          
Requests/sec:  75106.99                             
Transfer/sec:     46.56MB                           

2 threads and 2 connections                       
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    24.42us    2.99us 241.00us   74.37%  
  Req/Sec    39.28k     3.34k   45.41k    58.42%  
789111 requests in 10.10s, 489.16MB read          
Requests/sec:  78132.97                             
Transfer/sec:     48.43MB                           


./wrk -t4 -c4 -d10s http://172.24.30.30:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    27.65us    3.10us 186.00us   73.20%
  Req/Sec    34.80k     2.73k   42.72k    72.03%
1398888 requests in 10.10s, 867.15MB read        
Requests/sec: 138503.75                            
Transfer/sec:     85.86MB                          

4 threads and 4 connections                      
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    27.62us    3.19us 260.00us   69.18%
  Req/Sec    34.77k     2.44k   41.03k    66.09%
1397532 requests in 10.10s, 866.31MB read        
Requests/sec: 138371.71                            
Transfer/sec:     85.78MB                          

Running 10s test @ http://172.24.30.30:8888         
  4 threads and 4 connections                       
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    27.48us    2.84us 238.00us   73.71%  
    Req/Sec    34.98k     2.10k   41.47k    65.84%  
  1405442 requests in 10.10s, 0.85GB read           
Requests/sec: 139160.09                             
Transfer/sec:     86.26MB                           


./wrk -t8 -c8 -d10s http://172.24.30.30:8888

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency    35.05us    3.07us 819.00us   86.65%
Req/Sec    27.64k     1.04k   31.82k    85.52%
2221998 requests in 10.10s, 1.35GB read          
Requests/sec: 220002.85                            
Transfer/sec:    136.38MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    34.65us    2.55us 380.00us   81.27%
  Req/Sec    27.93k   798.70    32.00k    80.94%
2245229 requests in 10.10s, 1.36GB read          
Requests/sec: 222317.73                            
Transfer/sec:    137.81MB                          

  Thread Stats   Avg      Stdev     Max   +/- Stdev    
    Latency    34.87us    2.87us 547.00us   78.56%     
    Req/Sec    27.70k   778.53    31.09k    74.88%     
  2226862 requests in 10.10s, 1.35GB read              
Requests/sec: 220480.27                                
Transfer/sec:    136.67MB                              


./wrk -t16 -c16 -d10s http://172.24.30.30:8888

  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    69.19us   20.05us 479.00us   59.50%  
    Req/Sec    14.21k     2.61k   25.27k    81.00%  
  2284550 requests in 10.10s, 1.38GB read           
Requests/sec: 226199.97                             
Transfer/sec:    140.22MB                           

  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    68.30us   19.85us   0.99ms   59.89%  
    Req/Sec    14.39k     2.41k   23.30k    76.30%  
  2314542 requests in 10.10s, 1.40GB read           
Requests/sec: 229170.43                             
Transfer/sec:    142.06MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev   
  Latency    68.36us   19.43us   1.73ms   64.73%    
  Req/Sec    14.37k     2.60k   23.77k    81.68%    
2310268 requests in 10.10s, 1.40GB read             
Requests/sec: 228739.86                               
Transfer/sec:    141.79MB                             


./wrk -t32 -c32 -d10s http://172.24.30.30:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   135.68us   46.93us   1.67ms   76.98%
  Req/Sec     7.32k     1.73k   10.40k    64.05%
2354693 requests in 10.10s, 1.43GB read          
Requests/sec: 233150.94                            
Transfer/sec:    144.53MB                          

  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   136.15us   47.08us   1.23ms   76.56%  
    Req/Sec     7.30k     1.72k   10.39k    58.54%  
  2346301 requests in 10.10s, 1.42GB read           
Requests/sec: 232312.48                             
Transfer/sec:    144.01MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   135.12us   46.93us   1.74ms   76.25%  
  Req/Sec     7.35k     1.72k   10.90k    56.56%  
2363744 requests in 10.10s, 1.43GB read           
Requests/sec: 234047.24                             
Transfer/sec:    145.08MB                           

./wrk -t64 -c64 -d10s http://172.24.30.30:8888

Thread Stats   Avg      Stdev     Max   +/- Stdev
Latency   272.39us   66.95us 800.00us   92.55%
Req/Sec     3.67k   577.38     6.29k    84.37%
2358638 requests in 10.10s, 1.43GB read          
Requests/sec: 233554.32                            
Transfer/sec:    144.78MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   274.36us   65.69us 626.00us   93.01%
  Req/Sec     3.64k   563.59     6.20k    85.01%
2342173 requests in 10.10s, 1.42GB read          
Requests/sec: 231907.43                            
Transfer/sec:    143.76MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   275.10us   65.59us   1.83ms   93.10%
  Req/Sec     3.63k   556.35     6.18k    85.21%
2335946 requests in 10.10s, 1.41GB read          
Requests/sec: 231287.07                            
Transfer/sec:    143.37MB                          
```
