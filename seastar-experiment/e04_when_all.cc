#include "core/app-template.hh"
#include "util/log.hh"
#include "core/sleep.hh"
#include "core/reactor.hh"
#include <iostream>
#include <stdexcept>
#include <iostream>


seastar::future<> f() {

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
