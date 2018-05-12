#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "core/sleep.hh"
#include <vector>
#include <sys/time.h>
#include <iostream>

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;
size_t BUFFER_SIZE = 64;
#include "server_mpi.hh"
#include "client_mpi.hh"
namespace bpo = boost::program_options;

int main(int ac, char ** av) {
    app_template app;
    app.add_options()
        ("server", bpo::value<std::string>()->default_value("10.218.111.252:1234"), "Server address")
        ("test", bpo::value<std::string>()->default_value("ping"), "test type(ping | rxrx | txtx)")
        ("conn", bpo::value<unsigned>()->default_value(2), "nr connections per cpu")
        ("proto", bpo::value<std::string>()->default_value("tcp"), "transport protocol tcp|sctp")
        ("buffer", bpo::value<unsigned>()->default_value(64), "buffer size")
        ;


    return app.run_deprecated(ac, av, [&app] {

        uint16_t port = 1234; // assign the port value from the app_template
        auto server = new distributed<tcp_server>; // run distributed object
        auto&& config = app.configuration();
        BUFFER_SIZE = config["buffer"].as<unsigned>();

        server->start().then([server = std::move(server), port] () mutable {
            engine().at_exit([server] {
                return server->stop();
            });
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
            // Invoke a method on all Service instances in parallel.
        }).then([port] {
            std::cout << "Seastar TCP server listening on port " << port << " with buffer " << BUFFER_SIZE  <<"...\n";
        });

        auto server = config["server"].as<std::string>();
        auto test = config["test"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();
        auto proto = config["proto"].as<std::string>();
        protocol = transport::TCP;

        std::cout << "finding connection" << std::endl;
        sleep(10s).then([server, test, ncon] {
          clients.start().then([server, test, ncon] () {
              clients.invoke_on_all(&client::start, ipv4_addr{server}, test, ncon);
          });
        });

    });
}
