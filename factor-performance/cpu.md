### CPU
```
cat /proc/cpuinfo
```

```
// fiu                                                             //visasu  
processor       : 31                                               processor       : 31
vendor_id       : GenuineIntel                                     vendor_id       : GenuineIntel             
cpu family      : 6                                                cpu family      : 6  
model           : 63                                               model           : 63
model name      : Intel(R) Xeon(R) CPU E5-2630 v3 @ 2.40GHz        model name      : Intel(R) Xeon(R) CPU E5-2630 v3 @ 2.40GHz            
stepping        : 2                                                stepping        : 2  
microcode       : 0x36                                             microcode       : 0x2b                     
cpu MHz         : 1201.218                                         cpu MHz         : 1200.656                 
cache size      : 20480 KB                                         cache size      : 20480 KB                 
physical id     : 1                                                physical id     : 1  
siblings        : 16                                               siblings        : 16
core id         : 7                                                core id         : 7  
cpu cores       : 8                                                cpu cores       : 8  
apicid          : 31                                               apicid          : 31
initial apicid  : 31                                               initial apicid  : 31
fpu             : yes                                              fpu             : yes
fpu_exception   : yes                                              fpu_exception   : yes
cpuid level     : 15                                               cpuid level     : 15
wp              : yes                                              wp              : yes
bogomips        : 4801.06                                          bogomips        : 4800.92                  
clflush size    : 64                                               clflush size    : 64
cache_alignment : 64                                               cache_alignment : 64
address sizes   : 46 bits physical, 48 bits virtual                address sizes   : 46 bits physical, 48 bits virtual   
power management:                                                  power management:    
```
