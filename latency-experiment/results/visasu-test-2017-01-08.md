
```
82:00.0 Network controller: Mellanox Technologies MT27500 Family [ConnectX-3]


// 10.107.30.33
./tcp-server

// 10.107.30.102
sudo ./fstack-server --conf config_server.ini --proc-type=primary --proc-id=0


./wrk -t2 -c2 -d10s http://10.107.30.33:8888

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    22.46us    3.08us 155.00us   69.14%
  Req/Sec    42.35k     3.81k   49.36k    59.41%
  850948 requests in 10.10s, 527.49MB read         
Requests/sec:  84253.37                            
Transfer/sec:     52.23MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    24.62us    3.09us 113.00us   74.08%  
  Req/Sec    38.73k     3.52k   45.15k    63.86%  
778205 requests in 10.10s, 482.40MB read          
Requests/sec:  77053.55                             
Transfer/sec:     47.76MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    22.13us    3.17us 277.00us   72.68%
  Req/Sec    42.91k     3.94k   49.36k    56.44%
862195 requests in 10.10s, 534.46MB read         
Requests/sec:  85365.23                            
Transfer/sec:     52.92MB                          


./wrk -t4 -c4 -d10s http://10.107.30.33:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    24.21us    3.83us 172.00us   73.34%  
  Req/Sec    39.41k     4.18k   51.24k    69.55%  
1583570 requests in 10.10s, 0.96GB read           
Requests/sec: 156795.61                             
Transfer/sec:     97.20MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    26.31us    3.52us 184.00us   73.56%  
  Req/Sec    36.36k     3.13k   43.28k    68.56%  
1460873 requests in 10.10s, 0.88GB read           
Requests/sec: 144647.58                             
Transfer/sec:     89.67MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev   
  Latency    25.02us    3.79us 189.00us   64.60%    
  Req/Sec    38.20k     3.98k   47.32k    65.35%    
1534740 requests in 10.10s, 0.93GB read             
Requests/sec: 151962.60                               
Transfer/sec:     94.20MB                             


./wrk -t8 -c8 -d10s http://10.107.30.33:8888
8 threads and 8 connections                        
Thread Stats   Avg      Stdev     Max   +/- Stdev  
  Latency    24.18us    4.21us 164.00us   75.41%   
  Req/Sec    39.47k     3.86k   50.44k    72.52%   
3172098 requests in 10.10s, 1.92GB read            
Requests/sec: 314077.75                              
Transfer/sec:    194.69MB                            

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    24.72us    3.55us 194.00us   70.43%
  Req/Sec    38.64k     2.86k   45.42k    64.48%
3105712 requests in 10.10s, 1.88GB read          
Requests/sec: 307507.84                            
Transfer/sec:    190.62MB                          

8 threads and 8 connections                       
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    25.17us    3.64us 236.00us   72.67%  
  Req/Sec    37.96k     2.80k   43.44k    66.58%  
3051279 requests in 10.10s, 1.85GB read           
Requests/sec: 302109.67                             
Transfer/sec:    187.27MB                           


./wrk -t16 -c16 -d10s http://10.107.30.33:8888
16 threads and 16 connections                    
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    45.12us    6.96us 702.00us   83.47%
  Req/Sec    21.56k     1.86k   32.69k    86.26%
3465826 requests in 10.10s, 2.10GB read          
Requests/sec: 343188.06                            
Transfer/sec:    212.74MB                          

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    41.29us    4.13us 658.00us   80.94%  
  Req/Sec    23.58k   788.43    26.08k    77.54%  
3791851 requests in 10.10s, 2.30GB read           
Requests/sec: 375478.45                             
Transfer/sec:    232.75MB                           

Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    45.39us    8.65us   0.87ms   80.17%  
  Req/Sec    21.46k     2.40k   35.73k    79.95%  
3449983 requests in 10.10s, 2.09GB read           
Requests/sec: 341593.57                             
Transfer/sec:    211.75MB                           


./wrk -t32 -c32 -d10s http://10.107.30.33:8888
32 threads and 32 connections                      
Thread Stats   Avg      Stdev     Max   +/- Stdev  
  Latency    87.41us   31.10us   0.86ms   62.70%   
  Req/Sec    11.29k     2.66k   18.95k    56.90%   
3631276 requests in 10.10s, 2.20GB read            
Requests/sec: 359540.79                              
Transfer/sec:    222.88MB                            

32 threads and 32 connections                     
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency    88.19us   31.71us   1.48ms   65.40%  
  Req/Sec    11.20k     2.86k   20.50k    49.69%  
3601028 requests in 10.10s, 2.18GB read           
Requests/sec: 356553.52                             
Transfer/sec:    221.02MB                           

32 threads and 32 connections                        
Thread Stats   Avg      Stdev     Max   +/- Stdev    
  Latency    88.46us   32.83us   4.30ms   67.37%     
  Req/Sec    11.15k     2.91k   16.76k    49.13%     
3586227 requests in 10.10s, 2.17GB read              
Requests/sec: 355075.32                                
Transfer/sec:    220.11MB                              


./wrk -t64 -c64 -d10s http://10.107.30.33:8888
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   177.20us   52.43us   1.40ms   87.39%
  Req/Sec     5.62k     1.09k    9.29k    79.72%
3614620 requests in 10.10s, 2.19GB read          
Requests/sec: 357907.62                            
Transfer/sec:    221.86MB                          

64 threads and 64 connections                     
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   168.23us   49.20us   3.67ms   89.20%  
  Req/Sec     5.93k     1.08k   10.59k    81.64%  
3811774 requests in 10.10s, 2.31GB read           
Requests/sec: 377414.24                             
Transfer/sec:    233.95MB                           

64 threads and 64 connections                     
Thread Stats   Avg      Stdev     Max   +/- Stdev
  Latency   166.43us   49.34us   2.71ms   87.59%  
  Req/Sec     5.98k     1.19k    9.24k    80.69%  
3847917 requests in 10.10s, 2.33GB read           
Requests/sec: 380987.46                             
Transfer/sec:    236.17MB                           
```
