#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/distributed.hh"
#include <vector>
#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "testIpcShardMemory.h"

using namespace seastar;
namespace bpo = boost::program_options;
static shared_use_st *TxShardInstance;
static shared_use_st *RxShardInstance;

#include "server.hh"


int main(int ac, char** av) {

    int running = 1;
    void *TxShardMemory = (void*)0;
    void *RxShardMemory = (void*)0;

    int shmdTX, shmdRX;

    srand((unsigned int)getpid());
    shmdTX = shmget((key_t)2016, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    shmdRX = shmget((key_t)2017, sizeof(struct shared_use_st), 0667 | IPC_CREAT);

    if(shmdTX == -1){
        std::cout << "[shared memory][Error]shmget fail. id:" << shmdTX << running << TxShardInstance << TxShardMemory << std::endl;;
        exit(EXIT_FAILURE);
    }

    TxShardMemory = shmat(shmdTX, (void*)0, 0);
    if(TxShardMemory == (void*)-1){
        std::cout << "[shared memory][Error]shmat fail."<< std::endl;;
        exit(EXIT_FAILURE);
    }

    RxShardMemory = shmat(shmdRX, (void*)0, 0);
    if(RxShardMemory == (void*)-1){
        std::cout << "[shared memory][Error]shmat fail."<< std::endl;;
        exit(EXIT_FAILURE);
    }


    TxShardInstance = (struct shared_use_st *) TxShardMemory;
    TxShardInstance->written_by_you = 0;
    std::cout << "[shared memory]shmat success. flag:" << TxShardInstance->written_by_you << std::endl;;


    RxShardInstance = (struct shared_use_st *) RxShardMemory;
    RxShardInstance->written_by_you = 0;
    std::cout << "[shared memory]shmat success. flag:" << RxShardInstance->written_by_you << std::endl;;



    app_template app;
    app.add_options()
        ("port", bpo::value<uint16_t>()->default_value(1234), "TCP server port");


    return app.run_deprecated(ac, av, [&] {
        auto&& config = app.configuration();
        uint16_t port = config["port"].as<uint16_t>(); // assign the port value from the app_template
        auto server = new distributed<tcp_server>; // run distributed object

        server->start().then([server = std::move(server), port] () mutable {
            engine().at_exit([server] {
                return server->stop();
            });
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
            // Invoke a method on all Service instances in parallel.
        }).then([port] {
            std::cout << "Seastar TCP server listening on port " << port << " ...\n";
        });
    });
}
