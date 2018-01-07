### NIC configuration

```
eth2      Link encap:Ethernet  HWaddr e4:1d:2d:d9:b6:40                     
          inet6 addr: fe80::e61d:2dff:fed9:b640/64 Scope:Link               
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1                
          RX packets:1195 errors:0 dropped:0 overruns:0 frame:0             
          TX packets:8 errors:0 dropped:0 overruns:0 carrier:0              
          collisions:0 txqueuelen:1000                                      
          RX bytes:88032 (88.0 KB)  TX bytes:648 (648.0 B)                  

eth3      Link encap:Ethernet  HWaddr e4:1d:2d:d9:b6:41                     
          inet addr:10.107.30.32  Bcast:10.107.31.255  Mask:255.255.254.0   
          inet6 addr: fe80::e61d:2dff:fed9:b641/64 Scope:Link               
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1                
          RX packets:112009661 errors:0 dropped:0 overruns:0 frame:0        
          TX packets:57641833 errors:0 dropped:0 overruns:0 carrier:0       
          collisions:0 txqueuelen:1000                                      
          RX bytes:45040625775 (45.0 GB)  TX bytes:6104511406 (6.1 GB)      
```

<br>

### TCP
```
// thread 2
./wrk -t2 -c2 -d10s http://10.107.30.33:8888

Running 10s test @ http://10.107.30.33:8888         
  2 threads and 2 connections                       

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   243.18us    8.50us 293.00us   80.54%  
  Req/Sec     4.12k    11.89     4.12k    82.67%  
  82449 requests in 10.10s, 51.11MB read            
Requests/sec:   8163.35                             
Transfer/sec:      5.06MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   243.47us    1.32us 296.00us   75.24%
  Req/Sec     4.12k    12.02     4.12k    82.18%
82447 requests in 10.10s, 51.11MB read           
Requests/sec:   8163.01                            
Transfer/sec:      5.06MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   243.17us    8.48us 291.00us   80.54%
  Req/Sec     4.12k    11.63     4.12k    83.17%
82448 requests in 10.10s, 51.11MB read           
Requests/sec:   8163.33                            
Transfer/sec:      5.06MB                          


// thread 4
./wrk -t4 -c4 -d10s http://10.107.30.33:8888

Running 10s test @ http://10.107.30.33:8888         
  4 threads and 4 connections                       
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   243.44us    1.14us 304.00us   83.73%  
    Req/Sec     4.12k    11.96     4.12k    82.18%  
  164891 requests in 10.10s, 102.21MB read          
Requests/sec:  16325.76                             
Transfer/sec:     10.12MB                           


Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   243.26us    6.84us 488.00us   87.96%  
  Req/Sec     4.12k    12.02     4.12k    81.93%  
164891 requests in 10.10s, 102.21MB read          
Requests/sec:  16325.75                             
Transfer/sec:     10.12MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   243.25us    7.40us 332.00us   87.50%  
  Req/Sec     4.12k    11.91     4.12k    81.93%  
164890 requests in 10.10s, 102.21MB read          
Requests/sec:  16326.92                             
Transfer/sec:     10.12MB                           


// thread 8
./wrk -t8 -c8 -d10s http://10.107.30.33:8888
Running 10s test @ http://10.107.30.33:8888         
  8 threads and 8 connections                       
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   471.73us   54.21us 651.00us   61.55%  
  Req/Sec     2.13k   186.87     2.68k    87.50%  
  170621 requests in 10.10s, 105.77MB read          
Requests/sec:  16893.77                             
Transfer/sec:     10.47MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev   
  Latency   471.65us   49.28us 651.00us   61.70%    
  Req/Sec     2.13k   185.37     2.67k    87.50%    
170623 requests in 10.10s, 105.77MB read            
Requests/sec:  16893.40                               
Transfer/sec:     10.47MB                             

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   471.63us   54.89us 706.00us   67.64%  
  Req/Sec     2.12k    73.95     2.64k    91.58%  
170638 requests in 10.10s, 105.78MB read          
Requests/sec:  16895.53                             
Transfer/sec:     10.47MB                           


// thread 16
./wrk -t16 -c16 -d10s http://10.107.30.33:8888

Running 10s test @ http://10.107.30.33:8888        
  16 threads and 16 connections                    
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     0.94ms   68.71us   1.22ms   81.98%
    Req/Sec     1.06k    49.89     1.50k    78.85%
  170656 requests in 10.10s, 105.79MB read         
Requests/sec:  16897.63                            
Transfer/sec:     10.47MB                          

16 threads and 16 connections                      
Thread Stats   Avg      Stdev     Max   +/- Stdev  
  Latency     0.94ms   67.63us   1.22ms   80.84%   
  Req/Sec     1.06k    37.51     1.19k    79.52%   
170658 requests in 10.10s, 105.79MB read           
Requests/sec:  16897.49                              
Transfer/sec:     10.47MB                            

Running 10s test @ http://10.107.30.33:8888         
  16 threads and 16 connections                     
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     0.94ms   71.11us   1.24ms   79.43%  
    Req/Sec     1.06k    37.68     1.58k    93.36%  
  170649 requests in 10.10s, 105.78MB read          
Requests/sec:  16896.60                             
Transfer/sec:     10.47MB                           


// thread 32
./wrk -t32 -c32 -d10s http://10.107.30.33:8888
Running 10s test @ http://10.107.30.33:8888         
  32 threads and 32 connections                     

  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     1.88ms   95.48us   2.15ms   92.21%  
    Req/Sec   532.60     28.42     0.99k    99.13%  
  170737 requests in 10.10s, 105.84MB read          
Requests/sec:  16905.38                             
Transfer/sec:     10.48MB                           

Running 10s test @ http://10.107.30.33:8888           
  32 threads and 32 connections                       
  Thread Stats   Avg      Stdev     Max   +/- Stdev   
    Latency     1.88ms  108.27us   2.19ms   87.13%    
    Req/Sec   532.89     31.21     1.04k    99.19%    
  170733 requests in 10.10s, 105.84MB read            
Requests/sec:  16905.36                               
Transfer/sec:     10.48MB                             

32 threads and 32 connections                     
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency     1.88ms   97.63us   2.19ms   88.08%  
  Req/Sec   532.50     26.40     0.97k    99.04%  
170729 requests in 10.10s, 105.83MB read          
Requests/sec:  16903.93                             
Transfer/sec:     10.48MB                           


// thread 64
./wrk -t64 -c64 -d10s http://10.107.30.33:8888
Running 10s test @ http://10.107.30.33:8888         
  64 threads and 64 connections                     

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency     3.77ms    0.94ms   5.78ms   74.44%  
  Req/Sec   266.19     61.72   490.00     43.65%  
  170868 requests in 10.10s, 105.92MB read          
Requests/sec:  16918.54                             
Transfer/sec:     10.49MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev  
  Latency     3.77ms  823.16us   5.84ms   85.41%   
  Req/Sec   266.10     53.27   464.00     54.23%   
170869 requests in 10.10s, 105.92MB read           
Requests/sec:  16919.28                              
Transfer/sec:     10.49MB                            

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency     3.77ms    0.91ms   5.75ms   71.81%  
  Req/Sec   266.10     61.21   484.00     26.64%  
170874 requests in 10.10s, 105.92MB read          
Requests/sec:  16919.16                             
Transfer/sec:     10.49MB                           

```

### DPDK
```
// thread 2
./wrk -t2 -c2 -d10s http://10.107.30.102
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    98.43us    3.69us 361.00us   94.00%  
  Req/Sec    10.06k    43.68    10.09k    62.87%  
201844 requests in 10.10s, 125.12MB read          
Requests/sec:  19985.40                             
Transfer/sec:     12.39MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev  
  Latency    98.44us    3.56us 325.00us   93.49%   
  Req/Sec    10.06k    43.47    10.09k    62.87%   
  201845 requests in 10.10s, 125.12MB read           
Requests/sec:  19984.91                              
Transfer/sec:     12.39MB                            

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    98.41us    3.41us 283.00us   93.66%
  Req/Sec    10.06k    43.91    10.09k    62.38%
201842 requests in 10.10s, 125.12MB read         
Requests/sec:  19985.81                            
Transfer/sec:     12.39MB                          

// thread 4
./wrk -t4 -c4 -d10s http://10.107.30.102
Running 10s test @ http://10.107.30.102            
  4 threads and 4 connections                      
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    98.40us    2.84us 374.00us   94.67%
    Req/Sec    10.06k    42.86    10.09k    64.36%
  403699 requests in 10.10s, 250.25MB read         
Requests/sec:  39970.72                            
Transfer/sec:     24.78MB                          

Running 10s test @ http://10.107.30.102                  
  4 threads and 4 connections                            
  Thread Stats   Avg      Stdev     Max   +/- Stdev      
    Latency    98.30us    3.85us 232.00us   90.82%       
    Req/Sec    10.06k    43.48    10.09k    62.87%       
  403710 requests in 10.10s, 250.26MB read               
Requests/sec:  39972.14                                  
Transfer/sec:     24.78MB                                

Running 10s test @ http://10.107.30.102                                 
  4 threads and 4 connections                                           
  Thread Stats   Avg      Stdev     Max   +/- Stdev                     
    Latency    98.36us    3.43us 368.00us   94.07%                      
    Req/Sec    10.06k    43.43    10.09k    63.86%                      
  403698 requests in 10.10s, 250.25MB read                              
Requests/sec:  39969.77                                                 
Transfer/sec:     24.78MB                                               


// thread 8
./wrk -t8 -c8 -d10s http://10.107.30.102
Running 10s test @ http://10.107.30.102               
  8 threads and 8 connections                         
  Thread Stats   Avg      Stdev     Max   +/- Stdev   
    Latency    98.16us    3.91us 392.00us   84.55%    
    Req/Sec    10.06k    43.04    10.09k    63.24%    
  807384 requests in 10.10s, 500.49MB read            
Requests/sec:  79940.24                               
Transfer/sec:     49.55MB                             

Running 10s test @ http://10.107.30.102            
  8 threads and 8 connections                      
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    98.17us    4.75us 388.00us   71.71%
    Req/Sec    10.06k    43.57    10.09k    63.12%
  807378 requests in 10.10s, 500.48MB read         
Requests/sec:  79939.54                            
Transfer/sec:     49.55MB                          

Running 10s test @ http://10.107.30.102             
  8 threads and 8 connections                       
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    98.21us    5.07us 285.00us   58.66%  
    Req/Sec    10.06k    43.08    10.09k    63.74%  
  807405 requests in 10.10s, 500.50MB read          
Requests/sec:  79945.62                             
Transfer/sec:     49.56MB                           


// thread 16
./wrk -t16 -c16 -d10s http://10.107.30.102
sungho@c3n23:/data1/sungho/wrk$ ./wrk -t16 -c16 -d10s http://10.107.30.102
Running 10s test @ http://10.107.30.102                                   
  16 threads and 16 connections                                           
  Thread Stats   Avg      Stdev     Max   +/- Stdev                       
    Latency    46.02us    8.75us 360.00us   79.39%                        
    Req/Sec    21.15k     2.02k   28.85k    74.32%                        
  3400370 requests in 10.10s, 2.06GB read                                 
Requests/sec: 336690.20                                                   
Transfer/sec:    208.71MB                                                 


// thread 32
./wrk -t32 -c32 -d10s http://10.107.30.102
32 threads and 32 connections                    
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    51.43us   17.48us   2.91ms   92.47%
  Req/Sec    19.08k     1.35k   21.55k    63.49%
6135612 requests in 10.10s, 3.71GB read          
Requests/sec: 607488.14                            
Transfer/sec:    376.57MB                          

Running 10s test @ http://10.107.30.102            
  32 threads and 32 connections                    
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    51.34us   16.20us   4.45ms   90.94%
    Req/Sec    19.05k     0.96k   21.48k    80.41%
  6126004 requests in 10.10s, 3.71GB read          
Requests/sec: 606587.06                            
Transfer/sec:    376.02MB                          

Running 10s test @ http://10.107.30.102             
  32 threads and 32 connections                     
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    51.08us   16.55us   4.81ms   92.94%  
    Req/Sec    19.16k     1.42k   21.16k    72.80%  
  6162003 requests in 10.10s, 3.73GB read           
Requests/sec: 610122.81                             
Transfer/sec:    378.21MB                           

// thread 64
./wrk -t64 -c64 -d10s http://10.107.30.102

Running 10s test @ http://10.107.30.102            
  64 threads and 64 connections                    
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   106.28us  156.59us  21.75ms   99.82%
    Req/Sec     9.56k   445.25    13.89k    89.08%
  6148071 requests in 10.10s, 3.72GB read          
Requests/sec: 608714.96                            
Transfer/sec:    377.34MB                          

64 threads and 64 connections                      
Thread Stats   Avg      Stdev     Max   +/- Stdev  
  Latency   105.29us  119.27us  19.60ms   99.88%   
  Req/Sec     9.53k   484.39    13.25k    87.79%   
6132278 requests in 10.10s, 3.71GB read            
Requests/sec: 607195.92                              
Transfer/sec:    376.39MB                            

Running 10s test @ http://10.107.30.102               
  64 threads and 64 connections                       
  Thread Stats   Avg      Stdev     Max   +/- Stdev   
    Latency   115.52us  679.01us  69.83ms   99.94%    
    Req/Sec     9.53k   345.13    11.70k    93.60%    
  6127108 requests in 10.10s, 3.71GB read             
Requests/sec: 606689.71                               
Transfer/sec:    376.08MB                             
```
