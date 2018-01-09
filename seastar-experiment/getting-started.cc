#include "core/app-template.hh"
#include "core/reactor.hh"
#include <iostream>
int main(int argc, char** argv) {
    seastar::app_template app;
    app.run(argc, argv, [] {
            std::cout << seastar::smp::count << "\n";
            return seastar::make_ready_future<>();
    });
}
