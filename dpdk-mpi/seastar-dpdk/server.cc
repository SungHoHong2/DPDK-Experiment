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
static shared_use_st *pShardStuff;
#include "server.hh"


int main(int ac, char** av) {

    int running = 1;
    void *pShardMemory = (void*)0;
    int shmId;

    srand((unsigned int)getpid());
    shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if(shmId == -1){
        std::cout << "[shared memory][Error]shmget fail. id:" << shmId << running << pShardStuff << pShardMemory << std::endl;;
        exit(EXIT_FAILURE);
    }

    pShardMemory = shmat(shmId, (void*)0, 0);
    if(pShardMemory == (void*)-1){
        std::cout << "[shared memory][Error]shmat fail."<< std::endl;;
        exit(EXIT_FAILURE);
    }

    // you will have to put this as a argument
    pShardStuff = (struct shared_use_st *) pShardMemory;
    pShardStuff->written_by_you = 0;
    std::cout << "[shared memory]shmat success. flag:" << pShardStuff->written_by_you << std::endl;;


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
