### Memaslap
- researching about the possiblility of swapping the memaslap transfer location into Seastar version
- One problem is that Memaslap is built based on global lock which is not good for multi processing

### Located the send and recv section
- the logic is similar to the Seastar version
- memaslap benchmark provides comprehensive test for memcacheD
- however it is built in C, fortunately, it is not complicated as MPI library.
- only the protocols have to be equal, so I am trying to convert memaslap into C++ version
- I need to check whether it is possilbe to `wait` `Seastar` to send data when there is none. in MPI library they just send dummy - data with dummy packets. and MPI library ignores it. However, I believe this is the right way.



```

ms_warmup_server BEGIN
ms_warmup_server END


ms_add_msghdr BEGIN
ms_add_msghdr END

socket::SENDMSG

ms_try_read_network BEGIN
socket::READ
ms_try_read_network END



```
