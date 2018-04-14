#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;

// static int tx_msg_total_size = 100 * 1024 * 1024;
// static int tx_msg_size = 4 * 1024;
// static int tx_msg_nr = tx_msg_total_size / tx_msg_size;
// static std::string str_txbuf(tx_msg_size, 'X');


static time_t start, end; //adding timer

uint64_t getTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

static int total_ping_identifier = 0;

class client;
distributed<client> clients;

transport protocol = transport::TCP;

class client {
private:
    static constexpr unsigned _pings_per_connection = 10000;
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


        future<> ping(int times) {

            std::string str = "";
            int v, tenth;
            int total = 4;

            std::string s = std::to_string(total_ping_identifier);
            tenth = s.length();
            for(v=0; v<(total-tenth); v++){
                str.append("0");
            }
            str.append(s);

            total_ping_identifier++;
            // std::cout << str << std::endl;
            if(str.length()>4){
              str = "ping";
            }

            usleep(1);
            return _write_buf.write(str).then([this] {
                return _write_buf.flush();
            }).then([this, times] {
                return _read_buf.read_exactly(4).then([this, times] (temporary_buffer<char> buf) {
                    if (buf.size() != 4) {
                        fprint(std::cerr, "illegal packet received: %d\n", buf.size());
                        return make_ready_future();
                    }
                    auto str = std::string(buf.get(), buf.size());
                    // std::cout << "after: "  << str << std::endl;

                    if (times > 0) {
                        return ping(times - 1);
                    } else {
                        return make_ready_future();
                    }
                });
            });
        }
    };

    future<> ping_test(connection *conn) {
        auto started = lowres_clock::now();
        return conn->ping(_pings_per_connection).then([started] {
            auto finished = lowres_clock::now();
            clients.invoke_on(0, &client::ping_report, started, finished);
        });
    }

    void ping_report(lowres_clock::time_point started, lowres_clock::time_point finished) {
        if (_earliest_started > started)
            _earliest_started = started;
        if (_latest_finished < finished)
            _latest_finished = finished;
        if (++_num_reported == _concurrent_connections) {
            auto elapsed = _latest_finished - _earliest_started;
            auto usecs = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            auto secs = static_cast<double>(usecs) / static_cast<double>(1000 * 1000);
            fprint(std::cout, "========== ping ============\n");
            // fprint(std::cout, "Server: %s\n", _server_addr);
            // fprint(std::cout,"Connections: %u\n", _concurrent_connections);
            // fprint(std::cout, "Total PingPong: %u\n", _total_pings);
            // fprint(std::cout, "Total Time(Secs): %f\n", secs);
            // fprint(std::cout, "Requests/Sec: %f\n",
                // static_cast<double>(_total_pings) / secs);

            end_time = getTimeStamp();
            printf("latency: %ld\n", end_time - start_time);
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

        start_time = getTimeStamp();
        for (unsigned i = 0; i < ncon; i++) {
            socket_address local = socket_address(::sockaddr_in{AF_INET, INADDR_ANY, {0}});
            engine().net().connect(make_ipv4_address(server_addr), local, protocol).then([this, test] (connected_socket fd) {
                auto conn = new connection(std::move(fd));
                (this->*tests.at(test))(conn).then_wrapped([conn] (auto&& f) {
                    delete conn;
                    try {
                        f.get();
                    } catch (std::exception& ex) {
                        fprint(std::cerr, "request error: %s\n", ex.what());
                    }
                });
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
        ("server", bpo::value<std::string>()->default_value("192.168.56.101:1234"), "Server address")
        ("test", bpo::value<std::string>()->default_value("ping"), "test type(ping | rxrx | txtx)")
        ("conn", bpo::value<unsigned>()->default_value(1), "nr connections per cpu")
        ("proto", bpo::value<std::string>()->default_value("tcp"), "transport protocol tcp|sctp")
        ("smp", bpo::value<unsigned>()->default_value(1), "smp");

    return app.run_deprecated(ac, av, [&app] {
        auto&& config = app.configuration();
        auto server = config["server"].as<std::string>();
        auto test = config["test"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();
        auto proto = config["proto"].as<std::string>();

        if (proto == "tcp") {
            protocol = transport::TCP;
        } else if (proto == "sctp") {
            protocol = transport::SCTP;
        } else {
            fprint(std::cerr, "Error: --proto=tcp|sctp\n");
            return engine().exit(1);
        }

        if (!client::tests.count(test)) {
            fprint(std::cerr, "Error: -test=ping | rxrx | txtx\n");
            return engine().exit(1);
        }

        clients.start().then([server, test, ncon] () {

            clients.invoke_on_all(&client::start, ipv4_addr{server}, test, ncon);
        });
    });
}

const std::map<std::string, client::test_fn> client::tests = {
        {"ping", &client::ping_test},
};
