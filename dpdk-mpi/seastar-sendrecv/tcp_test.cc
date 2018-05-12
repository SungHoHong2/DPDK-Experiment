#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "core/sleep.hh"
#include <sys/time.h>

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;

time_t start; //adding timer
size_t BUFFER_SIZE = 64;
int LATENCY = 1, PINGS = 1000000;
double total_throughput = 0;
uint64_t start_time, end_time;
std::string packetz(BUFFER_SIZE,'*');


uint64_t getTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

class client;
distributed<client> clients;
transport protocol = transport::TCP;

class client {
private:
    static constexpr unsigned _pings_per_connection = 10;
    unsigned _total_pings;
    unsigned _concurrent_connections;
    ipv4_addr _server_addr;
    std::string _test;
    lowres_clock::time_point _earliest_started;
    lowres_clock::time_point _latest_finished;
    size_t _processed_bytes;
    unsigned _num_reported;
public:
    class connection {
        connected_socket _fd;
        input_stream<char> _read_buf;
        output_stream<char> _write_buf;
        size_t _bytes_read = 0;
        size_t _bytes_write = 0;
    public:
        connection(connected_socket&& fd)
            : _fd(std::move(fd))
            , _read_buf(_fd.input())
            , _write_buf(_fd.output()) {}

        future<> ping() {
            std::string packeti(BUFFER_SIZE,'*');
            return _write_buf.write(packeti).then([this] {
                std::cout << "write" << std::endl;
                return _write_buf.flush();

            }).then([this] {
                return _read_buf.read_exactly(BUFFER_SIZE).then([this] (temporary_buffer<char> buf) {
                    auto str = std::string(buf.get(), buf.size());
                    std::cout << "read" << std::endl;
                    // std::cout << str << str.length() << std::endl;
                    return ping();
                });
            });
        }
    };

    future<> ping_test(connection *conn) {
        return conn->ping().then([] {
            clients.invoke_on(0, &client::ping_report);
        });
    }


    void ping_report() {
        if (++_num_reported == _concurrent_connections) {
            clients.stop().then([] {
                engine().exit(0);
            });
        }
    }


    future<> start(ipv4_addr server_addr, std::string test, unsigned ncon) {
        _server_addr = server_addr;
        _concurrent_connections = ncon * smp::count;
        _total_pings = _pings_per_connection * _concurrent_connections;
        _test = test;

        for (unsigned i = 0; i < ncon; i++) {
            socket_address local = socket_address(::sockaddr_in{AF_INET, INADDR_ANY, {0}});
            engine().net().connect(make_ipv4_address(server_addr), local, protocol).then([this, test] (connected_socket fd) {
                auto conn = new connection(std::move(fd));
                ping_test(conn).then_wrapped([conn] (auto&& f) {
                    delete conn;
                    try {
                        f.get();
                    } catch (std::exception& ex) {
                        fprint(std::cerr, "request error: %s\n", ex.what());
                    }
                });

                //
                // (this->*tests.at(test))(conn).then_wrapped([conn] (auto&& f) {
                //     delete conn;
                //     try {
                //         f.get();
                //     } catch (std::exception& ex) {
                //         fprint(std::cerr, "request error: %s\n", ex.what());
                //     }
                // });


            });
        }


        return make_ready_future();
    }
    future<> stop() {
        return make_ready_future();
    }

    typedef future<> (client::*test_fn)(connection *conn);
    static const std::map<std::string, test_fn> tests;
};

namespace bpo = boost::program_options;

int main(int ac, char ** av) {
    app_template app;
    app.add_options()
        ("server", bpo::value<std::string>()->default_value("10.218.111.252:1234"), "Server address")
        ("test", bpo::value<std::string>()->default_value("ping"), "test type(ping | rxrx | txtx)")
        ("conn", bpo::value<unsigned>()->default_value(2), "nr connections per cpu")
        ("proto", bpo::value<std::string>()->default_value("tcp"), "transport protocol tcp|sctp")
        ("buffer", bpo::value<unsigned>()->default_value(64), "buffer size")
        ;

    // INITIALIZE THE TEST BEGIN
    if (LATENCY){
               start_time = getTimeStamp();
               total_throughput = 0;
    }

    return app.run_deprecated(ac, av, [&app] {
        auto&& config = app.configuration();
        auto server = config["server"].as<std::string>();
        auto test = config["test"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();
        auto proto = config["proto"].as<std::string>();
        BUFFER_SIZE = config["buffer"].as<unsigned>();
        protocol = transport::TCP;


        std::cout << "finding connection" << std::endl;
        using namespace std::chrono_literals;
        sleep(10s).then([server, test, ncon] {
          clients.start().then([server, test, ncon] () {
              clients.invoke_on_all(&client::start, ipv4_addr{server}, test, ncon);
          });
        });




    });
}

const std::map<std::string, client::test_fn> client::tests = {
        {"ping", &client::ping_test},
};
