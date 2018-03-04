#include "core/reactor.hh"
#include "core/app-template.hh"
#include "core/temporary_buffer.hh"
#include "core/distributed.hh"
#include <vector>
#include <iostream>

using namespace seastar;
size_t BUFFER_SIZE = 64;

class tcp_server {
    std::vector<server_socket> _tcp_listeners;

public:
    future<> listen(ipv4_addr addr) {
        listen_options lo;
        lo.proto = transport::TCP;
        lo.reuse_address = true;
        _tcp_listeners.push_back(engine().listen(make_ipv4_address(addr), lo));
        do_accepts(_tcp_listeners);
        return make_ready_future<>();
    }

    future<> stop() {
        return make_ready_future<>();
    }

    void do_accepts(std::vector<server_socket>& listeners) {
        int which = listeners.size() - 1;
        listeners[which].accept().then([this, &listeners] (connected_socket fd, socket_address addr) mutable {
            auto conn = new connection(*this, std::move(fd), addr);
            conn->process().then_wrapped([conn] (auto&& f) {
                delete conn;
                try {
                    f.get();
                } catch (std::exception& ex) {
                    std::cout << "request error " << ex.what() << "\n";
                }
            });
            do_accepts(listeners);
        }).then_wrapped([] (auto&& f) {
            try {
                f.get();
            } catch (std::exception& ex) {
                std::cout << "accept failed: " << ex.what() << "\n";
            }
        });
    }
    class connection {
        connected_socket _fd;
        input_stream<char> _read_buf;
        output_stream<char> _write_buf;
    public:
        connection(tcp_server& server, connected_socket&& fd, socket_address addr)
            : _fd(std::move(fd))
            , _read_buf(_fd.input())
            , _write_buf(_fd.output()) {}
        future<> process() {
             return read();
        }
        future<> read() {
            if (_read_buf.eof()) {
                return make_ready_future();
            }
            // Expect 4 bytes cmd from client
            return _read_buf.read_exactly(BUFFER_SIZE).then([this] (temporary_buffer<char> buf) {
                if (buf.size() == 0) {
                    return make_ready_future();
                }
                auto cmd = std::string(buf.get(), buf.size());
                // pingpong test
                    return _write_buf.write(cmd).then([this] {
                        return _write_buf.flush();
                    }).then([this] {
                        return this->read();
                    });
            });
        }
        future<> do_write(int end) {
            if (end == 0) {
                return make_ready_future<>();
            }
            return _write_buf.write(str_txbuf).then([this] {
                return _write_buf.flush();
            }).then([this, end] {
                return do_write(end - 1);
            });
        }
        future<> do_read() {
            return _read_buf.read_exactly(rx_msg_size).then([this] (temporary_buffer<char> buf) {
                if (buf.size() == 0) {
                    return make_ready_future();
                } else {
                    return do_read();  // read the file until it
                }
            });
        }
    };
};

namespace bpo = boost::program_options;

int main(int ac, char** av) {
    app_template app;
    app.add_options()
        ("buffer", bpo::value<unsigned>()->default_value(64), "buffer size")
    ;

    return app.run_deprecated(ac, av, [&app] {
        uint16_t port = 1234; // assign the port value from the app_template
        auto server = new distributed<tcp_server>; // run distributed object
        // The distributed template manages a sharded service,
        // by creating a copy of the service on each shard, providing mechanisms
        auto&& config = app.configuration();
        // to communicate with each shard's copy, and a way to stop the service.
        BUFFER_SIZE = config["buffer"].as<unsigned>();
        //Starts Service by constructing an instance on every logical core with a copy of args passed to the constructor.
        server->start().then([server = std::move(server), port] () mutable {
            engine().at_exit([server] {
                return server->stop();
            });
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
            // Invoke a method on all Service instances in parallel.
        }).then([port] {
            std::cout << "Seastar TCP server listening on port " << port << " ...\n";
        });
    });
}
