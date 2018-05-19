#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/distributed.hh"
#include "testIpcShardMemory.h"

using namespace seastar;
using namespace net;
using namespace std::chrono_literals;
static shared_use_st *pShardStuff;
static steady_clock_type::time_point started;
static steady_clock_type::time_point ended;


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


        future<> ping() {
            std::string str = "1";
            if(pShardStuff->written_by_you == 1){
                // std::cout << "[Servier]echo data:" << pShardStuff->data << std::endl;
                started = steady_clock_type::now();
                std::string packetii(pShardStuff->data);
                str = packetii;
                pShardStuff->written_by_you = 0;
            }

            return _write_buf.write(str).then([this] {
                return _write_buf.flush();
            }).then([this] {
                return _read_buf.read().then([this] (temporary_buffer<char> buf) {
                    auto str = std::string(buf.get(), buf.size());
                    if(buf.size()!=1){
                            ended = steady_clock_type::now();
                            auto elapsed = ended-started;
                            auto usecs = (elapsed).count();
                            std::cout << "message size: " << buf.size() <<  "\t latency(usec): " << usecs << std::endl;
                    }
                    return ping();

                });
            });
        }
    };

    // future<> ping_test(connection *conn) {
    //     auto started = lowres_clock::now();
    //     return conn->ping().then([started] {
    //         auto finished = lowres_clock::now();
    //         clients.invoke_on(0, &client::ping_report, started, finished);
    //     });
    // }

    // void ping_report(lowres_clock::time_point started, lowres_clock::time_point finished) {
    //     if (_earliest_started > started)
    //         _earliest_started = started;
    //     if (_latest_finished < finished)
    //         _latest_finished = finished;
    //     if (++_num_reported == _concurrent_connections) {
    //         auto elapsed = _latest_finished - _earliest_started;
    //         auto usecs = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    //         auto secs = static_cast<double>(usecs) / static_cast<double>(1000 * 1000);
    //         fprint(std::cout, "========== ping ============\n");
    //         fprint(std::cout, "Server: %s\n", _server_addr);
    //         fprint(std::cout,"Connections: %u\n", _concurrent_connections);
    //         fprint(std::cout, "Total PingPong: %u\n", _total_pings);
    //         fprint(std::cout, "Total Time(Secs): %f\n", secs);
    //         fprint(std::cout, "Requests/Sec: %f\n",
    //             static_cast<double>(_total_pings) / secs);
    //         clients.stop().then([] {
    //             engine().exit(0);
    //         });
    //     }
    // }


    future<> start(ipv4_addr server_addr,  unsigned ncon) {
        _server_addr = server_addr;
        _concurrent_connections = ncon * smp::count;
        _total_pings = _pings_per_connection * _concurrent_connections;

        for (unsigned i = 0; i < ncon; i++) {
            socket_address local = socket_address(::sockaddr_in{AF_INET, INADDR_ANY, {0}});
            engine().net().connect(make_ipv4_address(server_addr), local, protocol).then([this] (connected_socket fd) {
                auto conn = new connection(std::move(fd));

                 conn->ping().then_wrapped([conn] (auto&& f) {
                     delete conn;
                     try {
                         f.get();
                     } catch (std::exception& ex) {
                         fprint(std::cerr, "request error: %s\n", ex.what());
                     }
                 });

                //
                // (this->*tests.at("ping"))(conn).then_wrapped([conn] (auto&& f) {
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

    int running = 1;
    void *pShardMemory = (void*)0;
    int shmId;

    srand((unsigned int)getpid());
    shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if(shmId == -1){
        std::cout << "[shared memory][Error]shmget fail. id:" << shmId << running << pShardStuff << pShardMemory << std::endl;;
        exit(EXIT_FAILURE);
    }

    pShardMemory = shmat(shmId, (void*)0, 0);
    if(pShardMemory == (void*)-1){
        std::cout << "[shared memory][Error]shmat fail."<< std::endl;;
        exit(EXIT_FAILURE);
    }

    // you will have to put this as a argument
    pShardStuff = (struct shared_use_st *) pShardMemory;
    pShardStuff->written_by_you = 0;
    std::cout << "[shared memory]shmat success. flag:" << pShardStuff->written_by_you << std::endl;;


    app_template app;
    app.add_options()
        ("server", bpo::value<std::string>()->default_value("192.168.56.101:1234"), "Server address")
        ("test", bpo::value<std::string>()->default_value("ping"), "test type(ping | rxrx | txtx)")
        ("conn", bpo::value<unsigned>()->default_value(1), "nr connections per cpu");

    return app.run_deprecated(ac, av, [&app] {
        auto&& config = app.configuration();
        auto server = config["server"].as<std::string>();
        auto ncon = config["conn"].as<unsigned>();

        clients.start().then([server, ncon] () {
            clients.invoke_on_all(&client::start, ipv4_addr{server}, ncon);
        });
    });
}

// const std::map<std::string, client::test_fn> client::tests = {
//         {"ping", &client::ping_test},
// };
