### Experiments overview
- it seems that memcached does not communicate with each other for synchronization
- therefore the only hope that we can find from Seastar communication is whether Seastar uses client side feature
- First we will try to run the `client side with Seastar-Memcaached` and then run th



### MEMCACHED POSIX version
- RAM based key-value store, mostly used as a cache infront of a slow, disk based, backend database
- client queries the front end cache
- if the query key is not found there, it is retrieved from the database.
- leads to a key-value pair getting evicted from memcached

- The values corresponding to keys could be of different sizes (a few bytes for Facebook status messages
- so memcached uses slab based allocation
- The RAM is divided into 1 MB sized pages and each page is divided into fixed size chunks

- The key-value store is organized as a hash table, using chaining for collision resolution
- The eviction policy for the cache is LRU.

- Stock memcached scales poorly to multicore processors because it was written for single core systems.
-  A multi threaded version exists, but it uses global locks (every read or write must grab a mutex lock on the hash table as well and the LRU list)

- [way to incraese the performance with multi thread]
 Compact and Concurrent Memcache with Dumber Caching and Smarter Hashing'' by Bin Fan, David G. Andersen, and Michael Kaminsky. In Proc. 10th USENIX NSDI,

### Components
- Client software, which is given a list of available memcached servers.
- A client-based hashing algorithm, which chooses a server based on the "key".
- Server software, which stores values with their keys into an internal hash table.
- LRU, which determine when to throw out old data (if out of memory), or reuse memory.

### Design
- Simple Key/Value Store
- The server does not care what your data looks like
- Items are made up of a key, an expiration time optional flags, and raw data.
- It does not understand data structures
- you must upload data that is pre-serialized


### Logic Half in Client, Half in Server
- Clients understand how to choose which server to read or write to for an item
- What to do when it cannot contact a server.
- The servers understand how store and fetch items
- They also manage when to evict or reuse memory.


### Servers are Disconnected From Each Other
- Memcached servers are unaware of each other.
- There is no crosstalk, no syncronization, no broadcasting, no replication.
- Adding servers increases the available memory.
- Cache invalidation is simplified, as clients delete or overwrite data on the server which owns it directly.


### O(1)
- All commands are implemented to be as fast and lock-friendly as possible.
- This gives allows near-deterministic query speeds for all use cases.
- Queries on slow machines should run in well under 1ms.
- High end servers can serve millions of keys per second in throughput.


### Forgetting is a Feature
- Memcached is, by default, a Least Recently Used cache.
- Items expire after a specified amount of time.
- Both of these are elegant solutions to many problems;
- Expire items after a minute to limit stale data being returned, or flush unused data in an effort to retain frequently requested information.
- No "pauses" waiting for a garbage collector ensures low latency, and free space is lazily reclaimed.


### Cache Invalidation
- Rather than broadcasting changes to all available hosts
- Clients directly address the server holding the data to be invalidated.
