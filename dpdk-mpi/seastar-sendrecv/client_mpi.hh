
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
        int running = 1;
        void *pShardMemory = (void*)0;
        struct shared_use_st *pShardStuff;
        int shmId;
        
    public:
        connection(connected_socket&& fd)
            : _fd(std::move(fd))
            , _read_buf(_fd.input())
            , _write_buf(_fd.output()) {}

        future<> ping() {
            std::string packeti(BUFFER_SIZE,'*');

            srand((unsigned int)getpid());
            shmId = shmget((key_t)KEY_ID, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

            if(shmId == -1){
                std::cout << "[Servier][Error]shmget fail. id:" << shmId << running << pShardStuff << pShardMemory << std::endl;;
                exit(EXIT_FAILURE);
            }


              // if(pShardStuff->written_by_you == 1){
              //     std::cout << "[Servier]echo data:" << pShardStuff->data << std::endl;
              //     pShardStuff->written_by_you = 0;
              // }


                return _write_buf.write(packeti).then([this] {
                    // std::cout << pShardStuff->data << std::endl;
                    std::cout << "write" << std::endl;
                    return _write_buf.flush();

                }).then([this] {
                    return _read_buf.read_exactly(BUFFER_SIZE).then([this] (temporary_buffer<char> buf) {
                        auto str = std::string(buf.get(), buf.size());
                        // std::cout << "read" << std::endl;
                        return ping();
                    });
                });

            // }

            // return ping();


        }
    };

    future<> start(ipv4_addr server_addr, std::string test, unsigned ncon) {
        _server_addr = server_addr;
        _concurrent_connections = ncon * smp::count;
        _total_pings = _pings_per_connection * _concurrent_connections;
        _test = test;

        for (unsigned i = 0; i < ncon; i++) {
            socket_address local = socket_address(::sockaddr_in{AF_INET, INADDR_ANY, {0}});
            engine().net().connect(make_ipv4_address(server_addr), local, protocol).then([this, test] (connected_socket fd) {
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

    typedef future<> (client::*test_fn)(connection *conn);
    static const std::map<std::string, test_fn> tests;
};
