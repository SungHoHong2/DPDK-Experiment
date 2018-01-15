
```
# visasu
sudo ./server --dpdk-pmd --network-stack native --dhcp 0 --host-ipv4-addr 10.107.30.34 --netmask-ipv4-addr 255.255.254.0 --gw-ipv4-addr 10.107.30.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.253:10000 | sed -e 's/<[^>]*>//g'


# TCP seastar
./server --host-ipv4-addr 10.218.111.252 --netmask-ipv4-addr 255.255.248.0 --gw-ipv4-addr 10.218.111.1 --collectd 0 --smp 2
wget -qO- http://10.218.111.252:10000 | sed -e 's/<[^>]*>//g'

sudo ./server -l 0-3 -n 4 -- -q 8 -p 0x2 -T 1 //dpdk is working fine
httpd works so I need something to add in the makefile
```

httpd
linux-vdso.so.1 =>  (0x00007fff0d5dd000)                                     
libboost_program_options.so.1.66.0=>/usr/lib/libboost_program_options.so.1.6.0  


                                                 
libboost_system.so.1.66.0 => /usr/lib/libboost_system.so.1.66.0
libboost_filesystem.so.1.66.0 => /usr/lib/libboost_filesystem.so.1.66.0
libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6
libboost_thread.so.1.66.0 => /usr/lib/libboost_thread.so.1.66.0 (
libcrypto++.so.9 => /usr/lib/libcrypto++.so.9           
librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1           
libgnutls.so.28 => /usr/lib/x86_64-linux-gnu/libgnutls.so.28
libgnutlsxx.so.28 => /usr/lib/x86_64-linux-gnu/libgnutlsxx.so.28
liblz4.so.1 => /usr/lib/x86_64-linux-gnu/liblz4.so.1
libprotobuf.so.8 => /usr/lib/x86_64-linux-gnu/libprotobuf.so.8 (
libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (          
libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1  
libunwind.so.8 => /usr/lib/x86_64-linux-gnu/libunwind.so.8
libyaml-cpp.so.0.5 => /usr/lib/x86_64-linux-gnu/libyaml-cpp.so.0.5
libibverbs.so.1 => /usr/lib/libibverbs.so.1              
libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6          
libhwloc.so.5 => /usr/lib/x86_64-linux-gnu/libhwloc.so.5
libnuma.so.1 => /usr/lib/x86_64-linux-gnu/libnuma.so.1
libpciaccess.so.0 => /usr/lib/x86_64-linux-gnu/libpciaccess.so.0
libxml2.so.2 => /usr/lib/x86_64-linux-gnu/libxml2.so.2 (0x00007f9b021d2000)   
libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007f9b01fb9000)             
libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f9b01d9b000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f9b019d1000)             
/lib64/ld-linux-x86-64.so.2 (0x00007f9b0583e000)                              
libp11-kit.so.0 => /usr/lib/x86_64-linux-gnu/libp11-kit.so.0 (0x00007f9b0178f0
libtasn1.so.6 => /usr/lib/x86_64-linux-gnu/libtasn1.so.6 (0x00007f9b0157a000)
libnettle.so.4 => /usr/lib/x86_64-linux-gnu/libnettle.so.4 (0x00007f9b0134b000
libhogweed.so.2 => /usr/lib/x86_64-linux-gnu/libhogweed.so.2 (0x00007f9b0111d0
libgmp.so.10 => /usr/lib/x86_64-linux-gnu/libgmp.so.10 (0x00007f9b00ea8000)   
liblzma.so.5 => /lib/x86_64-linux-gnu/liblzma.so.5 (0x00007f9b00c86000)       
libnl.so.1 => /usr/lib/x86_64-linux-gnu/libnl.so.1 (0x00007f9b00a34000)       
libltdl.so.7 => /usr/lib/x86_64-linux-gnu/libltdl.so.7 (0x00007f9b0082a000)   
libffi.so.6 => /usr/lib/x86_64-linux-gnu/libffi.so.6 (0x00007f9b00621000)     



libboost_system.so.1.66.0 => /usr/lib/libboost_system.so.1.66.0             
libboost_filesystem.so.1.66.0 => /usr/lib/libboost_filesystem.so.1.66.0       
libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6                     
libboost_thread.so.1.66.0 => /usr/lib/libboost_thread.so.1.66.0               
libcrypto++.so.9 => /usr/lib/libcrypto++.so.9 (0x00007ffc3a075000)            
libgnutls.so.28 => /usr/lib/x86_64-linux-gnu/libgnutls.so.28                   
libgnutlsxx.so.28 => /usr/lib/x86_64-linux-gnu/libgnutlsxx.so.28 (             
liblz4.so.1 => /usr/lib/x86_64-linux-gnu/liblz4.so.1 (0x00007ffc3994e000)     
libprotobuf.so.8 => /usr/lib/x86_64-linux-gnu/libprotobuf.so.8 (               
libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007ffc39435000)     
libunwind.so.8 => /usr/lib/x86_64-linux-gnu/libunwind.so.8 (0x00007ffc3921900$
libyaml-cpp.so.0.5 => /usr/lib/x86_64-linux-gnu/libyaml-cpp.so.0.5             
libibverbs.so.1 => /usr/lib/libibverbs.so.1 (0x00007ffc38d80000)              
librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007ffc38b77000)           
libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007ffc38973000)           
libhwloc.so.5 => /usr/lib/x86_64-linux-gnu/libhwloc.so.5 (0x00007ffc38733000)
libnuma.so.1 => /usr/lib/x86_64-linux-gnu/libnuma.so.1 (0x00007ffc38527000)   
libpciaccess.so.0 => /usr/lib/x86_64-linux-gnu/libpciaccess.so.0               
libxml2.so.2 => /usr/lib/x86_64-linux-gnu/libxml2.so.2 (0x00007ffc37fb8000)   
libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007ffc37d9e000)             
libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007ffc37a98000)             
libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007ffc3787a000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ffc374b0000)             
/lib64/ld-linux-x86-64.so.2 (0x00007ffc3b31d000)                              
libp11-kit.so.0 => /usr/lib/x86_64-linux-gnu/libp11-kit.so.0                         
libtasn1.so.6 => /usr/lib/x86_64-linux-gnu/libtasn1.so.6 (0x00007ffc37059000)
libnettle.so.4 => /usr/lib/x86_64-linux-gnu/libnettle.so.4                           
libhogweed.so.2 => /usr/lib/x86_64-linux-gnu/libhogweed.so.2                        
libgmp.so.10 => /usr/lib/x86_64-linux-gnu/libgmp.so.10 (0x00007ffc36987000)   
liblzma.so.5 => /lib/x86_64-linux-gnu/liblzma.so.5 (0x00007ffc36765000)       
libnl.so.1 => /usr/lib/x86_64-linux-gnu/libnl.so.1 (0x00007ffc36513000)       
libltdl.so.7 => /usr/lib/x86_64-linux-gnu/libltdl.so.7 (0x00007ffc36309000)   
libffi.so.6 => /usr/lib/x86_64-linux-gnu/libffi.so.6 (0x00007ffc36100000)     
