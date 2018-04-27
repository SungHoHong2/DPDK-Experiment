### location
```
/data/sungho/DPDK-Experiment/pktcapture-experiment/infiniband_pktcapture
```

### installing gcc-7
```
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 100
sudo update-alternatives --config gcc
```


### add configuration file
```
modes = {                                                                             
    'debug': {                                                                        
        'sanitize': '-fsanitize=address -fsanitize=leak -fsanitize=undefined -fuse-ld=gold',                                                                                
        'sanitize_libs': '-lasan -lubsan',                                            
```

### capturing packets
```

sudo tshark -n -i ib0 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 172.24.30.30 || ip.src == 172.24.30.31" -e data.data >> receiver_ib0

sudo tshark -n -i ib0 -T fields -e frame.time_relative -e ip.src -Y "ip.src == 172.24.30.30 || ip.src == 172.24.30.31" -e data.data >> sender_ib0


```
