### Where the data transmission start
- TCP_SERVER class starts the connection and then send the data
- when server class is running it brings up the `sharded_cache struct` which is the logic for memcached
- it seems the cache and sharded cache is the only classes that are outside of Seastar
- The rest of the implementation is in the distritbution class of Seastar

**Basic Logic**
```
cache::cache
seastar memcached v1.0
tcp_server::start
tcp_server::accept
tcp_server::make_lw_shared
tcp_server::conn->_proto.handle
ascii_protocol::handle

tcp_server::accept
tcp_server::make_lw_shared
tcp_server::conn->_proto.handle
ascii_protocol::handle

tcp_server::accept
tcp_server::make_lw_shared
tcp_server::conn->_proto.handle
ascii_protocol::handle


tcp_server::conn->_proto.handle
ascii_protocol::handle
ascii_protocol::state::cmd_set
ascii_protocol::prepare_insertion
sharded_cache::set
sharded_cache::get_cpu
cache::set
cache::find
cache::add_new
cache::maybe_rehash
tcp_server::conn->_out.flush


tcp_server::conn->_proto.handle
ascii_protocol::handle
ascii_protocol::state::cmd_get
ascii_protocol::handle_get
sharded_cache::get
sharded_cache::get_cpu
cache::get
cache::find
item::compare
item::get_slab_page_index
ascii_protocol::append_item
item::key
item::ascii_prefix
item::value
tcp_server::conn->_out.flush

distributed<memcache::cache> cache_peers;
memcache::sharded_cache cache(cache_peers);
distributed<memcache::system_stats> system_stats;
distributed<memcache::tcp_server> tcp_server;
```

Hello Professor
Do you have time for the Weekly Report for today?


### Finding the source of the distribution class
- shareded header serves as a interface
- the actual implementation is in the `memcached.cc` in the name of `cache`

**class sharded**
- Support for exploiting multiple cores on a server
- Seastar supports multicore servers by using \i sharding.
- Each logical core (lcore) runs a separate event loop with its own memory allocator TCP/IP stack, and other services
- Shards communicate by explicit message passing rather than using locks and condition variables as with traditional
- sharded template manages a sharded service, by creating a copy of the service on each logical core
- providing mechanisms to communicate  with each shard's copy
- Service a class to be instantiated on each core.

**start**
Starts \c Service by constructing an instance on every logical core


**invoke_on_all**
Invoke a method on all \c Service instances in parallel.
