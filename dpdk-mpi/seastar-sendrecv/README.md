###  Server Code
```c++
std::vector<server_socket> _tcp_listeners;

int main(int ac, char** av)
app_template app;
app.add_options()
app.run_deprecated(ac, av, [&app] { } // app continued
      uint16_t port = 1234;
      auto server = new distributed<tcp_server>;
      auto&& config = app.configuration();
      BUFFER_SIZE = config["buffer"].as<unsigned>();
      server->start().then([server = std::move(server), port] () mutable {}
            engine().at_exit([server] {}
                  return server->stop();
            server->invoke_on_all(&tcp_server::listen, ipv4_addr{port});
                  future<> listen(ipv4_addr addr) {}
                        _tcp_listeners.push_back(engine().listen(make_ipv4_address(addr), lo));
                        // loop for accept
                        do_accepts(_tcp_listeners);
                              Listeners[which].accept().then([this, &listeners] (connected_socket fd, socket_address addr)
                                    auto conn = new connection(*this, std::move(fd), addr);
                                            connection(tcp_server& server, connected_socket&& fd, socket_address addr)
                                                future<> process() return read();
                                                future<> read()
                                                        read_buf.read_exactly(BUFFER_SIZE).then([this]
                                                               _write_buf.write(cmd).then([this]
                                                                       return this->read();
                                    conn->process().then_wrapped([conn] (auto&& f)
                                    do_accepts(listeners); // loop for accept end
           print end
```
