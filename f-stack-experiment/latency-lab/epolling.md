### Epolling


**What is epolling?**
- Event polling
- `/dev/poll` patch from Provos-Lever
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


<br>


**Optimization***
- avoiding unnecessary copies of data through a common set of shared pages
    - only by mmapping the device file descriptor
    - copy-data-to-user-space has been discarded for efficiency reasons.

- refrain from linear scan
    - `driver` allocates two sets of pages
    - double buffer to store files events
      - while working on one set
      - the kernel can use the other one to store incoming events
    - events coming from the same file are collapsed into a single slot
    - EP_POLL function will never do a linear scan


```
if ((kdpfd = open("/dev/epoll", O_RDWR)) == -1) {

 }
 if (ioctl(kdpfd, EP_ALLOC, maxfds))
 {

 }
 if ((map = (char *) mmap(NULL, EP_MAP_SIZE(maxfds), PROT_READ,
                 MAP_PRIVATE, kdpfd, 0)) == (char *) -1)
 {

 }
```

<br>

**Comparison between select and event polling***
[reference link](https://www.safaribooksonline.com/library/view/linux-system-programming/0596009585/ch04s02.html)
- `file descriptor` is an abstract indicator (handle) used to access a file or other input/output resource, such as a pipe or network socket. [link](https://en.wikipedia.org/wiki/File_descriptor)
  - `eventfd()` creates an "eventfd object" that can be used as an event wait/notify mechanism by user-space applications

- `select()` system call provides a mechanism for implementing synchronous multiplexing I/O:
  - this call blocks until the given file descriptors are ready to perform I/O,
  - select() returns the number of file descriptors ready for I/O,
  - **select()'s fd_set is a bit mask and therefore has some fixed size.**

- `poll()` employs a single array of `nfds pollfd` structures, pointed to by fds
  - unlike select(), you need not explicitly ask for reporting of exceptions.unlike select(), you need not explicitly ask for reporting of exceptions.
  - pollfd structure specifies a single file descriptor to watch
  - If none of the events requested (and no error) has occurred for any of the file descriptors, then `poll()` blocks until one of the events occurs
  - **the user must allocate an array of pollfd structures, and pass the number of entries in this array, so there's no fundamental limit**


<br>

**Common things in poll and select**
- `poll()` and `select()` require the full list of file descriptors to watch on each invocation. The kernel must then walk the list of each file descriptor to be monitored. When this list grows large—it may contain hundreds or even thou‐ sands of file descriptors—walking the list on each invocation becomes a scalability bottleneck.
- both handle file descriptors in a linear way. The more descriptors you ask them to check the slower they get
- they all copy file descriptor from kernel to user



<br>

- `epoll()` circumvents this problem by decoupling the monitor registration from the actual monitoring
  - `epoll_create()` intiialize epoll context
  - `epoll_ctl` adds monitored file descriptors or removes them
  - `epoll_wait` do the actual event wait

- `level triggered` is the default behavior. It is how poll() and select() behave, and it is what most developers expect
  - Level-triggered interrupts are useful when the state of the event (the asserted line) is of interest.
  - you’ll receive a notification so long as the file descriptor is ready for reading. It is the level of the line that causes notification.

- `Edge-triggered` behavior requires a different approach to programming, commonly utilizing nonblocking I/O, and careful checking for EAGAIN.
  - `Edge- triggered` interrupts are useful when the event itself (the line being asserted) is of interest
  - With `edge-triggered`, you’ll receive the notification but once, when the data first becomes readable: it is the edge, or the change, that causes notification.

<br>

**main advantage of epoll**
- The cost of epoll is closer to the number of file descriptors that actually have events on them.
- If you're monitoring 200 file descriptors, but only 100 of them have events on them, then you're (very roughly) only paying for those 100 active file descriptors.   
- If you have a thousand clients that are mostly idle, then when you use select you're still paying for all one thousand of them. However, with epoll, it's like you've only got a few - you're only paying for the ones that are active at any given time.
- All this means that epoll will lead to less CPU usage for most workloads
