### memcached architecture
Memcached is a RAM based key-value store
mostly used as a cache infront of a slow, disk based, backend database
A client queries the front end cache and if the query key is not found there, it is retrieved from the database.
This usually leads to a key-value pair getting evicted from memcached.

The values corresponding to keys could be of different sizes (a few bytes for Facebook status messages, to a few kilobytes for cover photos),
so memcached uses slab based allocation
The RAM is divided into 1 MB sized pages and each page is divided into fixed size chunks (a chunk stores a value)
The key-value store is organized as a hash table, using chaining for collision resolution.
The eviction policy for the cache is LRU. The LRU policy is implemented by using a doubly linked list maintaining the LRU order.

Stock memcached scales poorly to multicore processors because it was written for single core systems.
A multi threaded version exists, but it uses global locks (every read or write must grab a mutex lock on the hash table as well and the LRU list).

https://www.usenix.org/system/files/conference/nsdi13/nsdi13-final170_update.pdf


**What is memcached?**
- general-purpose distributed memory caching system
- used to speed up dynamic database-driven websites by caching data and objects in RAM to reduce the number of times an external data source
- depends on the libevent library.
- Memcached's APIs provide a very large hash table distributed across multiple machines.
- When the table is full, subsequent inserts cause older data to be purged in least recently used (LRU) order.[3][4]
- Memcached was first developed by Brad Fitzpatrick for his website LiveJournal, on May 22, 2003


**Software architecture**
- The system uses a client–server architecture.
- The servers maintain a key–value associative array;
- the clients populate this array and query it by key.
- Keys are up to 250 bytes long and values can be at most 1 megabyte in size.
- Each client knows all servers
- the servers do not communicate with each other.
- If a client wishes to set or read the value corresponding to a certain key, the client's library first computes a hash of the key to determine which server to use
- This gives a simple form of sharding and scalable shared-nothing architecture across the servers.
- The server computes a second hash of the key to determine where to store or read the corresponding value.
- The servers keep the values in RAM;
- if a server runs out of RAM, it discards the oldest values


- If all client libraries use the same hashing algorithm to determine servers, then clients can read each other's cached data.
- A typical deployment has several servers and many clients
- However, it is possible to use Memcached on a single computer, acting simultaneously as client and server
- The size of its hash table is often very large.

**example code**
- The client would first check whether a Memcached value with the unique key "userrow:userid" exists, where userid is some number
- If the result does not exist, it would select from the database as usual, and set the unique key using the Memcached API add function call.
- in addition to creating an "add" call, an update call would also be needed using the Memcached set function.

**Design**
Memcached is a developer tool, not a "code accelerator",
- Client software, which is given a list of available memcached servers.
- A client-based hashing algorithm, which chooses a server based on the "key".
- Server software, which stores values with their keys into an internal hash table.
- LRU, which determine when to throw out old data (if out of memory), or reuse memory.

- Simple Key/Value Store
- Logic Half in Client, Half in Server
- Servers are Disconnected From Each Other
  - Memcached servers are unaware of each othe
  - There is no crosstalk
  - no syncronization, no broadcasting, no replication.
  - Adding servers increases the available memory.
  - Cache invalidation is simplified, as clients delete or overwrite data on the server which owns it directly.

**What the clients do?**
- Hashing
- Weighting
- simply proceed as though it was a cache miss.
