#include "core/app-template.hh"
#include "core/sleep.hh"
#include <iostream>

int main(int argc, char** argv){
    seastar::app_template app;
    app.run(argc, argv, [] {
          std::cout << "Sleeping... " << std::flush;
          using namespace std::chrono_literals;
          return seastar::sleep(1s).then([] {
                std::cout << "Done.\n";
          });
    });
}
