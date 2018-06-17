### Memaslap
- researching about the possiblility of swapping the memaslap transfer location into Seastar version
- One problem is that Memaslap is built based on global lock which is not good for multi processing

### Located the send and recv section
- the logic is similar to the Seastar version
- memaslap benchmark provides comprehensive test for memcacheD
- however it is built in C, fortunately, it is not complicated as MPI library.
- only the protocols have to be equal, so I am trying to convert memaslap into C++ version
- I need to check whether it is possilbe to `wait` `Seastar` to send data when there is none. in MPI library they just send dummy - data with dummy packets. and MPI library ignores it. However, I believe this is the right way.

### BEGIN
### How the basic save and read is done in MemcachD
- I am figuring out the contents of the packet that are used in memcacheD
- the basic functions are `SET` and `GET`

### General features of sending the packet
- you have to choose whether the data has to be sent via binary or ascii
- the key has to by encryped with AES and ecrypted with AES
- I have converted the send data but doing this one by one will take too much time
- `memaslap implemented it's own transfer file, and it does not seem to use memcached library that much`
- we will try to convert memaslap into C++ and then Seastar
