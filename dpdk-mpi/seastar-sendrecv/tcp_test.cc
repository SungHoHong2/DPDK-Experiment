#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "core/sleep.hh"
#include <sys/time.h>

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;

std::string packetz(BUFFER_SIZE,'*');
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
        auto&& config = app.configuration();
        auto server = config["server"].as<std::string>();
        auto test = config["test"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();
        auto proto = config["proto"].as<std::string>();
        BUFFER_SIZE = config["buffer"].as<unsigned>();
        protocol = transport::TCP;


        std::cout << "finding connection" << std::endl;
        using namespace std::chrono_literals;
        sleep(10s).then([server, test, ncon] {
          clients.start().then([server, test, ncon] () {
              clients.invoke_on_all(&client::start, ipv4_addr{server}, test, ncon);
          });
        });

    });
}
