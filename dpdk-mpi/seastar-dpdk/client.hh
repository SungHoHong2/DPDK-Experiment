static steady_clock_type::time_point started;
static steady_clock_type::time_point ended;
// static transport protocol = transport::TCP;

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
            } else {

              // if (!_read_buf.eof()) {
              //   return make_ready_future();
              // }
              //
              //   return _read_buf.read().then([this] (temporary_buffer<char> buf) {
              //       auto str = std::string(buf.get(), buf.size());
              //       // if(buf.size()!=1){
              //       //         ended = steady_clock_type::now();
              //       //         auto elapsed = ended-started;
              //       //         auto usecs = (elapsed).count();
              //       //         std::cout << "message size: " << buf.size() <<  "\t latency(usec): " << usecs << std::endl;
              //       // }
              //       return ping();
              //     }

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


    future<> start(ipv4_addr server_addr,  unsigned ncon) {
        _server_addr = server_addr;
        _concurrent_connections = ncon * smp::count;
        _total_pings = _pings_per_connection * _concurrent_connections;

        for (unsigned i = 0; i < ncon; i++) {
            socket_address local = socket_address(::sockaddr_in{AF_INET, INADDR_ANY, {0}});
            engine().net().connect(make_ipv4_address(server_addr), local, transport::TCP).then([this] (connected_socket fd) {
                auto conn = new connection(std::move(fd));

                 conn->ping().then_wrapped([conn] (auto&& f) {
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
};
