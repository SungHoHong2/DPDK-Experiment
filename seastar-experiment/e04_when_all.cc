#include "core/app-template.hh"
#include "util/log.hh"
#include "core/sleep.hh"
#include "core/reactor.hh"
#include <iostream>
#include <stdexcept>
#include <iostream>

seastar::future<> service_loop();

seastar::future<> f() {
  return seastar::parallel_for_each(boost::irange<unsigned>(0, seastar::smp::count),
           [] (unsigned c) {
       return seastar::smp::submit_to(c, service_loop);
   });
}


int main(int argc, char** argv) {
    seastar::app_template app;
    try {
        app.run(argc, argv, f);


    } catch(...) {
        std::cerr << "Failed to start application: "
                  << std::current_exception() << "\n";
        return 1;
    }
    return 0;
}


future<> service_loop() {
    return seastar::do_with(seastar::listen(seastar::make_ipv4_address({1234})),
            [] (auto& listener) {
        return seastar::keep_doing([&listener] () {
            return listener.accept().then(
                [] (seastar::connected_socket s, seastar::socket_address a) {
                    std::cout << "Accepted connection from " << a << "\n";
                });
        });
    });
}
