### Where the data transmission start
- TCP_SERVER class starts the connection and then send the data
- when server class is running it brings up the `sharded_cache struct` which is the logic for memcached


```c++

struct expiration {

};


class item : public slab_item_base {
};

class cache {
};


class sharded_cache {
};

class ascii_protocol {
};


class tcp_server {
  lw_shared_ptr<server_socket> _listener;
  sharded_cache& _cache;
  distributed<system_stats>& _system_stats;
  uint16_t _port;

  struct connection {
      connected_socket _socket;
      socket_address _addr;
      input_stream<char> _in;
      output_stream<char> _out;
      ascii_protocol _proto;
      distributed<system_stats>& _system_stats;

      connection(connected_socket&& socket, socket_address addr, sharded_cache& c, distributed<system_stats>& system_stats)
      {
        _system_stats.local()._curr_connections++;
        _system_stats.local()._total_connections++;
      }

      ~connection() {
        _system_stats.local()._curr_connections--;
      }
  };

  tcp_server(sharded_cache& cache, distributed<system_stats>& system_stats, uint16_t port = 11211)
  : _cache(cache)
  , _system_stats(system_stats)
  , _port(port)
  {}

  void start() {
    _listener = engine().listen(make_ipv4_address({_port}), lo);
        keep_doing([this] {
                return _listener->accept().then([this] (connected_socket fd, socket_address addr){
                        do_until([conn] { return conn->_in.eof(); }, [conn] {
                              return conn->_proto.handle(conn->_in, conn->_out).then([conn] {
                                    return conn->_out.flush();
                              }
                        }
                }
        }
  };

};  // end of tcp_server class

class sharded_cache {
    future<bool> set(item_insertion_data& insertion) {

    }



};


```
