### speed
Pipes and FIFOs (also known as named pipes) provide a unidirectional
interprocess communication channel.  A pipe has a read end and a
write end.  Data written to the write end of a pipe can be read from
the read end of the pipe.

- **commands**
```
// pipesize
cat /proc/sys/fs/pipe-max-size
```

<br>

- **results**

```
// visasu
1048576

//fiu

```
