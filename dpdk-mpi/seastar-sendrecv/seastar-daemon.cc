// #include <boost/interprocess/managed_shared_memory.hpp>
// #include <cstdlib> //std::system
// #include <sstream>
#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "core/sleep.hh"
#include <vector>
#include <sys/time.h>
#include <iostream>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;

size_t BUFFER_SIZE = 64;
#include "testIpcShardMemory.h"
static shared_use_st *pShardStuff;
#include "server_mpi.hh"
#include "client_mpi.hh"
namespace bpo = boost::program_options;

int main(int ac, char ** av) {

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
        ("server", bpo::value<std::string>()->default_value("10.218.111.252:1234"), "Server address")
        ("conn", bpo::value<unsigned>()->default_value(2), "nr connections per cpu")
        ("test", bpo::value<std::string>()->default_value("ping"), "test type(ping | rxrx | txtx)")
        ("buffer", bpo::value<unsigned>()->default_value(64), "buffer size");


    return app.run_deprecated(ac, av, [&app] {
        uint16_t port = 1234; // assign the port value from the app_template
        auto server = new distributed<tcp_server>; // run distributed object
        auto&& config = app.configuration();
        BUFFER_SIZE = config["buffer"].as<unsigned>();

        auto con_server = config["server"].as<std::string>();

        if(con_server.compare("10.218.111.252:1234")!=0){
              std::cout << "this will act as a server" << std::endl;

              server->start().then([server = std::move(server), port] () mutable {
                  engine().at_exit([server] {
                      return server->stop();
                  });
                  server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
                  // Invoke a method on all Service instances in parallel.
              }).then([port] {
                  std::cout << "Seastar TCP server listening on port " << port << " with buffer " << BUFFER_SIZE  <<"...\n";
              });

       }else {
              std::cout << "this will act as a client" << std::endl;
              auto test = config["test"].as<std::string>();
              auto ncon = config["conn"].as<unsigned>();
              protocol = transport::TCP;

              // in MPI, this runs on a while loop
              std::cout << "finding connection :: " << port << server << std::endl;
              sleep(10s).then([con_server, test, ncon] {
                clients.start().then([con_server, test, ncon] () {
                    clients.invoke_on_all(&client::start, ipv4_addr{con_server}, test, ncon);
                });
              });

             }

    });
}
