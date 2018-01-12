
#include <cmath>
#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/sleep.hh"
#include "net/dns.hh"
#include "tls_echo_server.hh"

using namespace seastar;
namespace bpo = boost::program_options;


int main(int ac, char** av) {
    app_template app;
    app.add_options()
                    ("port", bpo::value<uint16_t>()->default_value(1234), "Server port")
                    ("address", bpo::value<std::string>()->default_value("10.218.111.252"), "Server address")
                    ("cert,c", bpo::value<std::string>()->required(), "Server certificate file")
                    ("key,k", bpo::value<std::string>()->required(), "Certificate key")
                    ("verbose,v", bpo::value<bool>()->default_value(false)->implicit_value(true), "Verbose")
                    ;
    return app.run_deprecated(ac, av, [&] {
        auto&& config = app.configuration();
        uint16_t port = config["port"].as<uint16_t>();
        auto crt = config["cert"].as<std::string>();
        auto key = config["key"].as<std::string>();
        auto addr = config["address"].as<std::string>();
        auto verbose = config["verbose"].as<bool>();

        std::cout << "Starting..." << std::endl;
        return net::dns::resolve_name(addr).then([=](net::inet_address a) {
            ipv4_addr ia(a, port);

            auto server = ::make_shared<seastar::sharded<echoserver>>();
            return server->start(verbose).then([=]() {
                return server->invoke_on_all(&echoserver::listen, socket_address(ia), sstring(crt), sstring(key), tls::client_auth::NONE);
            }).handle_exception([=](auto e) {
                std::cerr << "Error: " << e << std::endl;
                engine().exit(1);
            }).then([=] {
                std::cout << "TLS echo server running at " << addr << ":" << port << std::endl;
                engine().at_exit([server] {
                    return server->stop();
                });
            });
        });
    });
}
