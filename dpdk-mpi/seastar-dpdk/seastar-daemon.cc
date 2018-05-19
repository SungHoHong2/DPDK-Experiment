#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/distributed.hh"
#include "core/sleep.hh"
#include <vector>
#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "testIpcShardMemory.h"

using namespace seastar;
namespace bpo = boost::program_options;
using namespace net;
using namespace std::chrono_literals;
static shared_use_st *pShardStuff;
#include "server.hh"
#include "client.hh"
distributed<client> clients;

int main(int ac, char** av) {

    app_template app;
    app.add_options()
        ("port", bpo::value<uint16_t>()->default_value(1234), "TCP server port")
        ("server", bpo::value<std::string>()->default_value("10.107.30.41:1234"), "Server address")
        ("conn", bpo::value<unsigned>()->default_value(1), "nr connections per cpu");

    return app.run_deprecated(ac, av, [&] {
        auto&& config = app.configuration();
        uint16_t port = config["port"].as<uint16_t>(); // assign the port value from the app_template
        auto server = new distributed<tcp_server>; // run distributed object
        auto con_server = config["server"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();

        server->start().then([server = std::move(server), port] () mutable {
            engine().at_exit([server] {
                return server->stop();
            });
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
            std::cout << "server activated\n";
        });

        sleep(10s).then([con_server, ncon] {
          clients.start().then([con_server, ncon] () {
              clients.invoke_on_all(&client::start, ipv4_addr{con_server}, ncon);
              std::cout << "client activated\n";
          });
        });

    });
}
