### Epolling


**What is epolling?**
- General way to implement tcp servers is “one thread/process per connection”.
- `epoll` is a new system call introduced in Linux 2.6.
    - replace select function in polling
    - select uses a linear search through the list of watched file descriptors - O(n)
    - epoll scales well O(1)


<br>

| title | description |
|--|--|
| EPOLL_CTL_ADD |  predefined command constant to add sockets to epoll |
| Listener | thread that performs bind() and listen() calls and waits for incoming conncetions |
| I/O-Worker(s) | one or more threads to `receive connections` from listener and to `add them to epoll`. Main loop of the generic I/O-worker looks like last step of epoll using pattern described above. |
| Data Processing Worker(s) |  one or more threads to receive data from and send data to I/O-workers and to perform data processing.|

<br>


**Advantages of Epoll**
- Linear scalability allows you to manage huge amounts of parallel connections with `small amount of worker processes`
- faster than one-thread per connection.


<br>

**epolling interface**
- `epoll_create`
    - Creates an epoll instance.
    - Returns an fd for the new instance.
- `epoll_ctl`
    - Manipulate an epoll instance "epfd"
    - Returns 0 in case of success
- `epoll_wait`
    - Wait for events on an epoll instance "epfd"
    - Returns the number of triggered events returned in "events" buffer
