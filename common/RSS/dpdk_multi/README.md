### DPDK MULTI-PROCESS
- demonstrate how two DPDK processes can work together
- using queues and memory pools to share information

```
export RTE_SDK=/home/sungho/f-stack/dpdk
./build/simple_mp -c 3 -n 4 --proc-type=primary
./build/simple_mp -c C -n 4 --proc-type=secondary

./build/symmetric_mp -c 1 -n 4 --proc-type=auto -- -p 0 --num-procs=1 --proc-id=0
```

 is a network driver technology that
i
