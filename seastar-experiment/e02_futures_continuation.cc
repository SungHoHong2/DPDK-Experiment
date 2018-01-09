#include "core/app-template.hh"
#include "core/reactor.hh"
#include <iostream>
int main(int argc, char** argv) {
    seastar::app_template app;

        app.run(argc, argv, [] {
                std::cout << seastar::smp::count << "\n"; // the number of started threads:
                return seastar::make_ready_future<>();
        }); // return 8
}

// can change the allocation of cores by using argument
// ./e01_threads_memory -c3
