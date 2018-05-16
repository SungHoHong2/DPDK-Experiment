### Seastar-Daemon

**current issue**
- the problem seems to be like the Seastar version because the latest version Seastar v18 is having a crash whenever it is using DPDK with socket connection.
- I'am hoping that the errors will be resolved by downgrading the version.
- I am having issues with installing dpdk with the downgrade version, and I am suspecting that the dpdk version is not properly provided by the Seastar


**seastar-daemon**
- creates a tx and rx shared memory for the host
- the listen and accept interface which reads data from other host.
- listen interface writes the received data to the shared memory.
- connection interface writes data to the other host
- connection interface reads shared memory and sends the data to the other node.

**daemon-interface**
- links to the shared memory with IPC library
- the memory is shared between C execution file and C++ execution file.


```c++
// seastar daemon
#define TEXT_SIZE 2048
#define KEY_ID 2016

struct shared_use_st {
    int written_by_you;
    char data[TEXT_SIZE];
};

void *pShardMemory = (void*)0;
shared_use_st *pShardStuff;

int main(int ac, char ** av)

    // create shared memory
    srand((unsigned int)getpid());
    shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    pShardMemory = shmat(shmId, (void*)0, 0);
    pShardStuff = (struct shared_use_st *) pShardMemory;
    pShardStuff->written_by_you = 0;

    // use seastar framework
    app_template app;
    // run the server application
    return app.run_deprecated(ac, av, [&app] {
        server->start().then([server = std::move(server))
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});

        // run the client application
        sleep(10s).then([con_server, test, ncon])
              clients.start().then([con_server, test, ncon])
                    clients.invoke_on_all(&client::start, ipv4_addr{con_server}, test, ncon);


// daemon interface

// locate the shared memory
void *pShardMemory = (void*)0;
struct shared_use_st *pShardStuff;
int shmId;
char buffer[TEXT_SIZE];
srand((unsigned int)getpid());
shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
pShardMemory = shmat(shmId, (void*)0, 0);
pShardStuff = (struct shared_use_st *) pShardMemory;

// write in the shared memory
strncpy(pShardStuff->data, buffer, TEXT_SIZE);
pShardStuff->written_by_you = 1;

```
