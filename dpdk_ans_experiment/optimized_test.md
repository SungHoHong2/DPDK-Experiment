### KNI Optimization Test

- reinstall the dpdk to change the KNI driver
```

CONFIG_RTE_LIBRTE_KNI=y
CONFIG_RTE_KNI_PREEMPT_DEFAULT=n  
  // This patch introduces CONFIG_RTE_KNI_PREEMPT_DEFAULT flag. When set to 'no',
  // KNI kernel thread(s) do not call schedule_timeout_interruptible(), which
  // improves overall KNI performance at the expense of CPU cycles (polling).


CONFIG_RTE_LIBRTE_PMD_PCAP=y
CONFIG_RTE_LIBRTE_MLX4_PMD=y

```

- change the kni driver to multiple threads
```
insmod /home/sungho/dpdk-stable-17.05.2/build/kmod/rte_kni.ko
insmod /home/sungho/dpdk-stable-17.05.2/build/kmod/rte_kni.ko kthread_mode=multiple

```


- assign multiple threads running dpdk-ans








- the reason why I am getting the confusion is that according to the IX: A Protected Dataplane Operating System for
High Throughput and Low Latency, the latency created by using the kernel space stack can be alleviated by higher packet rates
However this assumptions can be different based on how we design the usage of data plane.
