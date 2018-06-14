### Seastar Client and Server


**First, checking whether Seastar Memcached does not communicate with each servers**
  - unfortunately, seatar is just using the tcp_server class and extends it in order to use memcached
  - so eventually it only have to run the server class
  - servers do not have to synchronize with each other at all
  - I will simplify it and only leave the essentials


**Second, find how Seastar sends data from client to server that can increase the number of smps**
  - check how that works in Wenji's project


**Third, convert libmemcached into Seatar available**
  -


**Fourth, Final objective will be comparing Wenji's shared library version with the Memcached version**
  - this will convince the Professor about the tradeoff of using shared memory


```



```
