static steady_clock_type::time_point started;
static steady_clock_type::time_point ended;

class tcp_server {
    std::vector<server_socket> _tcp_listeners;
    std::vector<server_socket> _sctp_listeners;
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
            conn->ping().then_wrapped([conn] (auto&& f) {
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


        future<> ping() {
            if (_read_buf.eof()) {
                return make_ready_future();
            }
            return _read_buf.read().then([this] (temporary_buffer<char> buf) {

                    auto cmd = std::string(buf.get(), buf.size());

                    if(cmd.size()!=1){
                            std::cout << buf.size() << std::endl;
                            pShardStuff->written_by_you = 0;
                    }

                    // std::string str = "1";
                    if(pShardStuff->written_by_you == 1){
                        // std::cout << "[Servier]echo data:" << pShardStuff->data << std::endl;
                        // started = steady_clock_type::now();
                        std::string packetii(pShardStuff->data);
                        cmd = packetii;
                    }

                    return _write_buf.write(str).then([this] {
                        return _write_buf.flush();
                    }).then([this] {
                        return this->ping();
                    });
            });
        }

    };
};
