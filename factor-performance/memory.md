### MEMORY

- **commands**
```
cat /proc/meminfo
```


- **result**
```
//fiu                             //visasu
MemTotal:       65859688 kB       MemTotal:       65934712 kB    
MemFree:        59748352 kB       MemFree:        61044168 kB    
MemAvailable:   63383336 kB       MemAvailable:   62481708 kB    
Buffers:          511452 kB       Buffers:          353196 kB    
Cached:          2825412 kB       Cached:          1173328 kB    
SwapCached:            0 kB       SwapCached:            0 kB    
Active:          3360212 kB       Active:          1013288 kB    
Inactive:        1068408 kB       Inactive:         523908 kB    
Active(anon):    1125916 kB       Active(anon):      19436 kB    
Inactive(anon):    51648 kB       Inactive(anon):      964 kB    
Active(file):    2234296 kB       Active(file):     993852 kB    
Inactive(file):  1016760 kB       Inactive(file):   522944 kB    
Unevictable:        3660 kB       Unevictable:           0 kB    
Mlocked:            3660 kB       Mlocked:               0 kB    
SwapTotal:             0 kB       SwapTotal:       1952764 kB    
SwapFree:              0 kB       SwapFree:        1952764 kB    
Dirty:                 0 kB       Dirty:                 0 kB    
Writeback:             0 kB       Writeback:             0 kB    
AnonPages:       1095568 kB       AnonPages:         14916 kB    
Mapped:           104964 kB       Mapped:            12688 kB    
Shmem:             83400 kB       Shmem:              5584 kB    
Slab:            1009720 kB       Slab:             323824 kB    
SReclaimable:     881032 kB       SReclaimable:     258628 kB    
SUnreclaim:       128688 kB       SUnreclaim:        65196 kB    
KernelStack:        9136 kB       KernelStack:        6896 kB    
PageTables:         5900 kB       PageTables:         2076 kB    
NFS_Unstable:          0 kB       NFS_Unstable:          0 kB    
Bounce:                0 kB       Bounce:                0 kB    
WritebackTmp:          0 kB       WritebackTmp:          0 kB    
CommitLimit:    32929844 kB       CommitLimit:    33871544 kB    
Committed_AS:    2303780 kB       Committed_AS:      83916 kB    
VmallocTotal:   34359738367 kB    VmallocTotal:   34359738367 kB
VmallocUsed:           0 kB       VmallocUsed:      394456 kB    
VmallocChunk:          0 kB       VmallocChunk:   34325254144 kB
HardwareCorrupted:     0 kB       HardwareCorrupted:     0 kB    
AnonHugePages:   1060864 kB       AnonHugePages:         0 kB    
CmaTotal:              0 kB       HugePages_Total:    1024       
CmaFree:               0 kB       HugePages_Free:        0       
HugePages_Total:       0          HugePages_Rsvd:        0       
HugePages_Free:        0          HugePages_Surp:        0       
HugePages_Rsvd:        0          Hugepagesize:       2048 kB    
HugePages_Surp:        0          DirectMap4k:      136440 kB    
Hugepagesize:       2048 kB       DirectMap2M:     7096320 kB    
DirectMap4k:      256524 kB       DirectMap1G:    61865984 kB    
DirectMap2M:     8017920 kB             
DirectMap1G:    60817408 kB             

```
