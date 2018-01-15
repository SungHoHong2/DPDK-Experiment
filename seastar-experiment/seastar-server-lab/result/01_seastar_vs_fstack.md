### SEASTAR with 1 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000
Latency   594.62us    7.77us   0.96ms   94.90%      
Transfer/sec:      2.47MB

Latency   595.16us    8.33us   0.91ms   95.37%
Transfer/sec:      2.49MB

Latency   594.70us    8.31us   0.95ms   94.76%
Transfer/sec:      2.49MB


./wrk -t4 -c4 -d10s http://10.218.111.253:10000
Latency   587.96us   10.75us   0.96ms   88.91%
Transfer/sec:      5.03MB

Latency   588.11us   10.59us   0.93ms   93.83%
Transfer/sec:      5.00MB    

Latency   588.95us    9.56us   0.90ms   93.34%
Transfer/sec:      5.02MB


./wrk -t8 -c8 -d10s http://10.218.111.253:10000

Latency   589.16us   29.90us   1.17ms   94.85%
Transfer/sec:     10.03MB

Latency   589.42us   31.13us   1.17ms   94.95%
Transfer/sec:     10.02MB

Latency   589.07us   30.99us   1.17ms   94.43%
Transfer/sec:     10.04MB


./wrk -t16 -c16 -d10s http://10.218.111.253:10000
Latency     1.09ms  131.25us   1.47ms   72.70%
Transfer/sec:     10.76MB

Latency     1.09ms  130.72us   1.49ms   72.59%
Transfer/sec:     10.76MB

Latency     1.09ms  127.70us   1.47ms   72.93%   
Transfer/sec:     10.74MB  


./wrk -t32 -c32 -d10s http://10.218.111.253:10000
Latency     2.19ms  170.35us   2.77ms   85.77%
Transfer/sec:     10.76MB  

Latency     2.18ms  189.75us   2.76ms   97.05%
Transfer/sec:     10.84MB

Latency     2.19ms  153.55us   2.67ms   67.25%
Transfer/sec:     10.75MB


./wrk -t64 -c64 -d10s http://10.218.111.253:10000
Latency     4.35ms  369.22us   4.98ms   98.91%
Transfer/sec:     10.83MB

Latency     4.35ms  333.22us   5.03ms   98.82%
Transfer/sec:     10.83MB  

Latency     4.35ms  373.27us   5.00ms   98.91%
Transfer/sec:     10.83MB
```


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

### SEASTAR with 4 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000
Latency   590.72us   24.41us   0.92ms   88.25%
Transfer/sec:      2.50MB  

Latency   594.74us    9.94us   0.90ms   94.79%  
Transfer/sec:      2.49MB

Latency   594.88us   12.41us   0.94ms   90.39%
Transfer/sec:      2.49MB

./wrk -t4 -c4 -d10s http://10.218.111.253:10000
Latency   585.73us   19.32us   0.92ms   92.24%
Transfer/sec:      5.05MB  

Latency   587.70us   11.67us   0.96ms   93.40%
Transfer/sec:      5.03MB

Latency   588.61us   11.34us   1.07ms   92.76%   
Transfer/sec:      5.02MB


./wrk -t8 -c8 -d10s http://10.218.111.253:10000

Latency   589.05us   32.85us   1.18ms   94.82%
Transfer/sec:     10.02MB  

Latency   589.06us   30.38us   1.17ms   94.79%
Transfer/sec:     10.04MB

Latency   588.95us   30.55us   0.93ms   94.39%
Transfer/sec:     10.03MB


./wrk -t16 -c16 -d10s http://10.218.111.253:10000

Latency     1.09ms  130.23us   1.47ms   72.64%
Transfer/sec:     10.75MB

Latency     1.09ms  130.82us   1.46ms   72.78%
Transfer/sec:     10.77MB

Latency     1.09ms  130.70us   1.50ms   72.72%
Transfer/sec:     10.79MB    



./wrk -t32 -c32 -d10s http://10.218.111.253:10000

Latency     2.18ms  177.90us   2.71ms   92.60%
Transfer/sec:     10.78MB

Latency     2.18ms  463.56us   3.26ms   65.22%
Transfer/sec:     10.84MB

Latency     2.18ms  270.09us   2.83ms   78.09%
Transfer/sec:     10.80MB


./wrk -t64 -c64 -d10s http://10.218.111.253:10000

Latency     4.37ms  288.26us   5.01ms   76.76%
Transfer/sec:     10.84MB

Latency     4.35ms  373.04us   5.00ms   98.91%
Transfer/sec:     10.83MB   

Latency     4.36ms  300.37us   5.30ms   78.29%
Transfer/sec:     10.84MB
```


### SEASTAR with 8 threads
```
./wrk -t2 -c2 -d10s http://10.218.111.253:10000
Latency   589.40us   15.01us   1.81ms   86.75%    
Transfer/sec:      2.51MB   

Latency   591.94us   12.53us   0.92ms   85.93%
Transfer/sec:      2.50MB                                                             

Latency   595.04us   13.85us   1.29ms   89.82%                                    
Transfer/sec:      2.49MB     


./wrk -t4 -c4 -d10s http://10.218.111.253:10000
Latency   587.55us   12.43us   0.90ms   78.86%
Transfer/sec:      5.02MB

Latency   589.12us   10.14us   0.94ms   92.36%  
Transfer/sec:      5.02MB

Latency   589.11us   11.73us   1.32ms   90.12%
Transfer/sec:      5.02MB  

./wrk -t8 -c8 -d10s http://10.218.111.253:10000
Latency   589.80us   31.52us   1.07ms   94.55%
Transfer/sec:     10.03MB

Latency   589.71us   31.55us   1.17ms   95.13%
Transfer/sec:     10.03MB

Latency   590.13us   32.50us   0.91ms   94.50%
Transfer/sec:     10.02MB


./wrk -t16 -c16 -d10s http://10.218.111.253:10000

Latency     1.09ms  130.13us   1.47ms   72.64%
Transfer/sec:     10.77MB   

Latency     1.09ms  127.55us   2.59ms   72.84%
Transfer/sec:     10.74MB

Latency     1.09ms  128.14us   1.48ms   72.63%
Transfer/sec:     10.74MB


./wrk -t32 -c32 -d10s http://10.218.111.253:10000
Latency     2.18ms  302.74us   4.42ms   71.65%
Transfer/sec:     10.83MB

Latency     2.18ms  177.30us   4.71ms   93.00%
Transfer/sec:     10.78MB

Latency     2.18ms  264.54us   2.99ms   82.11%
Transfer/sec:     10.83MB


./wrk -t64 -c64 -d10s http://10.218.111.253:10000
Latency     4.36ms    0.89ms   6.12ms   53.64%   
Transfer/sec:     10.84MB  

Latency     4.37ms  581.70us   6.19ms   73.83%
Transfer/sec:     10.84MB

Latency     4.37ms  648.72us   5.88ms   71.98%  
Transfer/sec:     10.84MB
```



### F-STACK with 1 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.253
Latency   594.09us    9.90us   1.00ms   95.98%
Transfer/sec:      2.08MB

Latency   593.93us    8.86us   0.90ms   95.84%
Transfer/sec:      2.07MB

Latency   593.95us    8.86us   0.97ms   95.57%
Transfer/sec:      2.08MB


./wrk -t4 -c4 -d10s http://10.218.111.253
Latency   589.25us   31.01us   1.00ms   97.24%
Transfer/sec:      4.18MB

Latency   588.54us   32.65us   0.94ms   95.12%
Transfer/sec:      4.20MB

Latency   588.40us   32.97us   1.03ms   94.65%
Transfer/sec:      4.20MB  


./wrk -t8 -c8 -d10s http://10.218.111.253
Latency   625.44us   98.11us   1.22ms   85.42%
Transfer/sec:      7.90MB

Latency   624.10us   96.56us   1.12ms   85.87%
Transfer/sec:      7.91MB

Latency   624.10us   96.56us   1.12ms   85.87%
Transfer/sec:      7.91M


./wrk -t16 -c16 -d10s http://10.218.111.253

Latency     1.06ms  142.88us   1.53ms   61.69%
Transfer/sec:      9.31MB

Latency     1.06ms  142.71us   1.58ms   61.83%
Transfer/sec:      9.31MB

Latency     1.06ms  140.27us   1.51ms   62.06%
Transfer/sec:      9.29MB



./wrk -t32 -c32 -d10s http://10.218.111.253

Latency     2.12ms  148.35us   2.64ms   76.86%
Transfer/sec:      9.28MB

Latency     2.11ms  155.35us   2.63ms   76.42%
Transfer/sec:      9.34MB

Latency     2.11ms  181.99us   2.64ms   78.07%
Transfer/sec:      9.33MB


./wrk -t64 -c64 -d10s http://10.218.111.253
Latency     4.23ms  306.02us   5.00ms   99.28%
Transfer/sec:      9.29MB

Latency     4.22ms  361.38us   4.96ms   98.93%
Transfer/sec:      9.33MB

Latency     4.23ms  227.75us   6.11ms   98.30%
Transfer/sec:      9.34MB

```



### F-STACK with 2 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.253

Latency   591.48us   19.11us   0.97ms   94.20%    
Transfer/sec:      2.08MB   

Latency   594.01us    8.48us   0.93ms   96.06%
Transfer/sec:      2.08MB   

Latency   594.21us   10.14us   0.91ms   93.92%
Transfer/sec:      2.08MB


./wrk -t4 -c4 -d10s http://10.218.111.253
Latency   588.86us   25.79us   1.02ms   94.36%
Transfer/sec:      4.19MB

Latency   589.16us   21.42us   0.92ms   94.61%   
Transfer/sec:      4.18MB  

Latency   588.80us   25.64us   0.99ms   94.80%
Transfer/sec:      4.20MB


./wrk -t8 -c8 -d10s http://10.218.111.253
Latency   616.51us   90.71us   1.17ms   88.20%
Transfer/sec:      8.00MB

Latency   614.57us   88.33us   1.17ms   88.79%  
Transfer/sec:      8.04MB  

Latency   617.38us   91.91us   1.18ms   87.81%
Transfer/sec:      7.98MB  


./wrk -t16 -c16 -d10s http://10.218.111.253
Latency     1.06ms  141.53us   1.50ms   62.12%
Transfer/sec:      9.28MB

Latency     1.06ms  141.70us   1.46ms   62.45%
Transfer/sec:      9.29MB

Latency     1.06ms  142.49us   1.46ms   62.59%
Transfer/sec:      9.30MB


./wrk -t32 -c32 -d10s http://10.218.111.253
Latency     2.12ms  164.43us   2.60ms   77.47%
Transfer/sec:      9.29MB

Latency     2.11ms  164.41us   2.59ms   77.11%
Transfer/sec:      9.34MB

Latency     2.12ms  164.39us   2.60ms   77.70%
Transfer/sec:      9.29MB


./wrk -t64 -c64 -d10s http://10.218.111.253
Latency     4.22ms  348.85us   4.93ms   98.84%
Transfer/sec:      9.33MB

Latency     4.23ms  250.92us   4.72ms   94.24%  
Transfer/sec:      9.34MB  

Latency     4.22ms  342.67us   5.00ms   99.11%
Transfer/sec:      9.31MB
```



### F-STACK with 4 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.253

Latency   593.83us    9.48us   1.05ms   95.66%
Transfer/sec:      2.07MB  

Latency   594.03us   10.51us   0.94ms   93.29%
Transfer/sec:      2.08MB

Latency   594.42us    9.52us   0.85ms   94.71%
Transfer/sec:      2.08MB


./wrk -t4 -c4 -d10s http://10.218.111.253
Latency   585.67us   23.40us   0.91ms   88.51%
Transfer/sec:      4.22MB

Latency   585.29us   26.21us   1.06ms   90.49%
Transfer/sec:      4.22MB

Latency   588.56us   19.76us   0.92ms   93.14%
Transfer/sec:      4.20MB



./wrk -t8 -c8 -d10s http://10.218.111.253
Latency   608.37us   80.12us   1.06ms   90.76%   
Transfer/sec:      8.11MB    

Latency   608.20us   80.74us   0.92ms   90.89%
Transfer/sec:      8.12MB   

Latency   606.56us   78.51us   0.93ms   91.22%
Transfer/sec:      8.15MB



./wrk -t16 -c16 -d10s http://10.218.111.253
Latency     1.06ms  140.69us   1.48ms   62.15%
Transfer/sec:      9.27MB

Latency     1.06ms  142.61us   1.48ms   62.85%
Transfer/sec:      9.30MB  

Latency     1.06ms  140.93us   1.48ms   62.14%
Transfer/sec:      9.27MB


./wrk -t32 -c32 -d10s http://10.218.111.253

Latency     2.11ms  182.24us   2.66ms   78.08%
Transfer/sec:      9.32MB

Latency     2.11ms  484.07us   3.24ms   61.59%
Transfer/sec:      9.33MB

Latency     2.11ms  185.64us   2.79ms   78.56%
Transfer/sec:      9.33MB


./wrk -t64 -c64 -d10s http://10.218.111.253
Latency     4.22ms  415.00us   5.27ms   90.45%
Transfer/sec:      9.33MB

Latency     4.23ms  823.93us   5.78ms   74.91%
Transfer/sec:      9.34MB  

Latency     4.22ms  376.35us   5.02ms   83.39%
Transfer/sec:      9.33MB  
```


### F-STACK with 8 threads

```
./wrk -t2 -c2 -d10s http://10.218.111.253
Latency   593.59us   11.62us   0.88ms   93.62%  
Transfer/sec:      2.08MB  

Latency   594.03us    7.51us 801.00us   95.58%                                    
Transfer/sec:      2.08MB      

Latency   594.09us   12.58us   1.47ms   93.24%
Transfer/sec:      2.07MB


./wrk -t4 -c4 -d10s http://10.218.111.253
Latency   586.87us   13.19us   1.13ms   85.37%
Transfer/sec:      4.21MB

Latency   588.81us   21.81us   1.03ms   94.76%
Transfer/sec:      4.18MB  

Latency   581.53us   29.04us   0.97ms   86.72%
Transfer/sec:      4.24MB


./wrk -t8 -c8 -d10s http://10.218.111.253
Latency   603.59us   72.51us   0.93ms   92.46%
Transfer/sec:      8.18MB

Latency   605.20us   75.09us   0.95ms   91.95%
Transfer/sec:      8.17MB

Latency   615.49us   90.05us   1.16ms   88.10%
Transfer/sec:      8.03MB  



./wrk -t16 -c16 -d10s http://10.218.111.253
Latency     1.06ms  139.18us   1.49ms   61.59%
Transfer/sec:      9.25MB

Latency     1.06ms  141.37us   1.46ms   61.92%
Transfer/sec:      9.28MB

Latency     1.06ms  141.57us   1.67ms   61.96%
Transfer/sec:      9.28MB




./wrk -t32 -c32 -d10s http://10.218.111.253
Latency     2.11ms  423.52us   3.26ms   68.71%
Transfer/sec:      9.33MB  

Latency     2.11ms  156.68us   3.32ms   76.61%
Transfer/sec:      9.34MB

Latency     2.12ms  237.47us   2.96ms   78.02%
Transfer/sec:      9.34MB


./wrk -t64 -c64 -d10s http://10.218.111.253
Latency     4.23ms  822.75us   5.90ms   49.88%
Transfer/sec:      9.34MB

Latency     4.22ms  447.53us   5.31ms   81.89%
Transfer/sec:      9.32MB

Latency     4.23ms  517.51us   6.13ms   77.79%
Transfer/sec:      9.34MB
```
