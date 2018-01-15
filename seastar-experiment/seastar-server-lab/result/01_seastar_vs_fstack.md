

### SEASTAR with 2 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000
Latency   594.50us   10.82us   0.95ms   92.62%                    
Transfer/sec:      2.49MB                          

Latency   581.34us   32.26us 763.00us   82.26%                           
Transfer/sec:      2.53MB                           

Latency   575.05us   31.69us   0.96ms   79.38%                    
Transfer/sec:      2.57MB                          


./wrk -t4 -c4 -d10s http://10.218.111.253:10000

Latency   589.42us    9.43us   0.95ms   91.56%                  
Transfer/sec:      5.00MB                          

Latency   589.40us   10.39us   0.95ms   92.20%
Transfer/sec:      5.02MB                          

Latency   582.98us   16.99us   0.88ms   77.51%                       
Transfer/sec:      5.07MB                            


./wrk -t8 -c8 -d10s http://10.218.111.253:10000

Latency   588.61us   27.03us   0.91ms   95.70%
Transfer/sec:     10.05MB                          

Latency   588.86us   30.12us   0.92ms   94.84%        
Transfer/sec:     10.04MB                           

Latency   588.77us   
Transfer/sec:     10.04MB

./wrk -t16 -c16 -d10s http://10.218.111.253:10000

Latency     1.09ms  129.24us   1.64ms   72.79%              
Transfer/sec:     10.83MB                           

Latency     1.09ms  131.38us   1.46ms   72.79%                          
Transfer/sec:     10.78MB                          

Latency     1.09ms  128.65us   1.49ms   72.89%                              
Transfer/sec:     10.76MB                             

./wrk -t32 -c32 -d10s http://10.218.111.253:10000

Latency     2.18ms  193.71us   2.65ms   97.86%                              
Transfer/sec:     10.80MB                             

Latency     2.18ms  191.11us   2.86ms   92.58%  
Transfer/sec:     10.83MB                           

Latency     2.18ms  178.69us   2.81ms   92.72%  
Transfer/sec:     10.78MB                           


./wrk -t64 -c64 -d10s http://10.218.111.253:10000
Latency     4.35ms  357.06us   4.73ms   98.93%  
Transfer/sec:     10.83MB                           

Latency     4.35ms  355.32us   4.98ms   98.93%                         
Transfer/sec:     10.83MB                          

Latency     4.35ms  346.21us   4.78ms   98.90%                          
Transfer/sec:     10.83MB                           
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
