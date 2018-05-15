### SHMD Experiments

**client persepctive**
```c++
struct shared_use_st {
    int written_by_you;
    char data[TEXT_SIZE];
};

#define KEY_ID 2016
void *pShardMemory = (void*)0;
struct shared_use_st *pShardStuff;
int shmId;
srand((unsigned int)getpid());

shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
pShardMemory = shmat(shmId, (void*)0, 0);
pShardStuff = (struct shared_use_st *) pShardMemory;

printf("[Client]Enter text :\n");
fgets(buffer, TEXT_SIZE, stdin); // add the input to the buffer
strncpy(pShardStuff->data, buffer, TEXT_SIZE); // copy the buffer to the shared memory
```

**server**
```c++
#define KEY_ID 2016
void *pShardMemory = (void*)0;
struct shared_use_st *pShardStuff;
int shmId;
srand((unsigned int)getpid());

pShardMemory = shmat(shmId, (void*)0, 0);
pShardStuff = (struct shared_use_st *) pShardMemory;
cout << "[Servier]echo data:" << pShardStuff->data << endl;

```
