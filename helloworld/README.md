### HELLOWORLD

```c
int main(int argc, char **argv) {
	ret = rte_eal_init(argc, argv);
	if (ret < 0)
		rte_panic("Cannot init EAL\n");
```

- get the data for logical cores and memory
- initialize the Environment Abstraction Layer (EAL)

<br>

```c
	RTE_LCORE_FOREACH_SLAVE(lcore_id) {
		rte_eal_remote_launch(lcore_hello, NULL, lcore_id);
	}
```
- function for slave cores
- arg1: function to be called
- arg2: argument for the function
- arg3: lcores


<br>

```c
	/* call it on master lcore too */
	lcore_hello(NULL);

	rte_eal_mp_wait_lcore();
	return 0;
}
```

- function for master cores

<br>

```c
static int
lcore_hello(__attribute__((unused)) void *arg)
{
	unsigned lcore_id;
	lcore_id = rte_lcore_id();
	printf("hello from core %u\n", lcore_id);
	return 0;
}
```

- thread function of each cores
