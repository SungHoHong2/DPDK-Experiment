#include "core/app-template.hh"
#include "core/future.hh"
#include "core/sleep.hh"
#include <iostream>


seastar::future<int> incr(int i) {
    using namespace std::chrono_literals;
    return seastar::sleep(10ms).then([i] { return i + 1; });
}

seastar::future<> f() {
    return incr(3).then([] (int val) {
        std::cout << "Got " << val << "\n";
    });
}


    return 0;
}
