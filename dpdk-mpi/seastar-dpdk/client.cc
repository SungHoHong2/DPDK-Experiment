#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "testIpcShardMemory.h"

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;
namespace bpo = boost::program_options;
#include "client.hh"
static shared_use_st *pShardStuff;


distributed<client> clients;


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
        ("server", bpo::value<std::string>()->default_value("192.168.56.101:1234"), "Server address")
        ("test", bpo::value<std::string>()->default_value("ping"), "test type(ping | rxrx | txtx)")
        ("conn", bpo::value<unsigned>()->default_value(1), "nr connections per cpu");

    return app.run_deprecated(ac, av, [&app] {
        auto&& config = app.configuration();
        auto server = config["server"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();

        clients.start().then([server, ncon] () {
            clients.invoke_on_all(&client::start, ipv4_addr{server}, ncon);
        });
    });
}
