#include "core/app-template.hh"
#include "util/log.hh"
#include "core/sleep.hh"
#include <iostream>
#include <stdexcept>

seastar::future<> f();

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

seastar::future<int> slow() {
    using namespace std::chrono_literals;
    return seastar::sleep(100ms).then([] { return 3; });
}

seastar::future<int> fast() {
    return seastar::make_ready_future<int>(3);
}

seastar::future<> f() {  // a future which is useful for chaining multiple continuations one after another
    std::cout << "Sleeping... " << std::flush;
    using namespace std::chrono_literals;
    seastar::sleep(200ms).then([] { std::cout << "200ms " << std::flush; });
    seastar::sleep(100ms).then([] { std::cout << "100ms " << std::flush; });

    fast().then([] (int val) {
            std::cout << "Fast " << val << "\n";
    });

    slow().then([] (int val) {
        std::cout << "Slow " << val << "\n";
    });
    return seastar::sleep(1s).then([] {
        std::cout << "Done.\n";
    });
}
