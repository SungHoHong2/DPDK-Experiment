#include "core/app-template.hh"
#include "core/future.hh"
#include "core/sleep.hh"
#include <iostream>


eastar::future<int> slow() {
    using namespace std::chrono_literals;
    return seastar::sleep(100ms).then([] { return 3; });
}

seastar::future<> f() {
    return slow().then([] (int val) {
        std::cout << "Got " << val << "\n";
    });
}



int main(int argc, char** argv) {
    seastar::app_template app;
    app.run(argc, argv, f);
}
