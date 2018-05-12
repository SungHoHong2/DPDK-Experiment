#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/distributed.hh"
#include "core/sleep.hh"
#include <vector>
#include <iostream>
using namespace seastar;
size_t BUFFER_SIZE = 64;

#include "server_mpi.hh"


namespace bpo = boost::program_options;

int main(int ac, char** av) {
    app_template app;
    app.add_options()
        ("buffer", bpo::value<unsigned>()->default_value(64), "buffer size")
    ;

    return app.run_deprecated(ac, av, [&app] {
        uint16_t port = 1234; // assign the port value from the app_template
        auto server = new distributed<tcp_server>; // run distributed object
        // The distributed template manages a sharded service,
        // by creating a copy of the service on each shard, providing mechanisms
        auto&& config = app.configuration();
        // to communicate with each shard's copy, and a way to stop the service.
        BUFFER_SIZE = config["buffer"].as<unsigned>();
        //Starts Service by constructing an instance on every logical core with a copy of args passed to the constructor.
        server->start().then([server = std::move(server), port] () mutable {
            engine().at_exit([server] {
                return server->stop();
            });
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
            // Invoke a method on all Service instances in parallel.
        }).then([port] {
            std::cout << "Seastar TCP server listening on port " << port << " with buffer " << BUFFER_SIZE  <<"...\n";
        });

        std::cout << "Sleeping... " << std::flush;
        using namespace std::chrono_literals;
        seastar::sleep(1s).then([] {
            std::cout << "Done.\n";
        });

    });


}
