#include "core/app-template.hh"
#include "util/log.hh"
#include <iostream>
#include <stdexcept>
extern seastar::future<> f();
int main(int argc, char** argv) {
    seastar::app_template app;
    try {
        app.run(argc, argv, f);
    } catch(...) {
        std::cerr << "Couldn't start application: "
                  << std::current_exception() << "\n";
        return 1;
    }
    return 0;
}
