### implementing latency version

```c
#define MAX_SIZE   (128*1024)
#define NUM_ROUNDS 10000
#define PROBE_PROGRESS

int main(int argc, char **argv) {
  int        me, nproc, target;
  int        msg_length, round, i;
  double     t_start, t_stop;
  uint8_t  *snd_buf;  // Send buffer (byte array)
  uint8_t  *rcv_buf;  // Receive buffer (byte array)
  MPI_Win    window;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &me);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);


  MPI_Alloc_mem(MAX_SIZE, MPI_INFO_NULL, &rcv_buf);
  MPI_Alloc_mem(MAX_SIZE, MPI_INFO_NULL, &snd_buf);

  MPI_Win_create(rcv_buf, MAX_SIZE, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &window);

  for (i = 0; i < MAX_SIZE; i++) {
    snd_buf[i] = 1;
  }

```
> create buffers for sending packets

```c
    for (msg_length = 1; msg_length <= MAX_SIZE; msg_length *= 2) {  // packet size per latency
      MPI_Barrier(MPI_COMM_WORLD);
      t_start = MPI_Wtime();

        for (round = 0; round < NUM_ROUNDS*2; round++) { // Perform NUM_ROUNDS ping-pongs

          // I am the sender
          if (round % 2 == 0) {
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, me, 0, window);
            rcv_buf[0] = 0;
            rcv_buf[msg_length-1] = 0;
            MPI_Win_unlock(me, window);

            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, my_target, 0, window);
            MPI_Put(snd_buf, msg_length, MPI_BYTE, my_target, 0, msg_length, MPI_BYTE, window);
            MPI_Win_unlock(my_target, window);
          }
          // I am the receiver: Poll start and end markers
          else {
            uint8_t val;
            do {
              MPI_Win_lock(MPI_LOCK_EXCLUSIVE, me, 0, window);
              val = ((volatile uint8_t*)rcv_buf)[0];
              MPI_Win_unlock(me, window);
            } while (val == 0);
          }
        }

      MPI_Barrier(MPI_COMM_WORLD);
      t_stop = MPI_Wtime();

      if (me == 0)
        printf("%8d bytes \t %12.8f us\n", msg_length, (t_stop-t_start)/NUM_ROUNDS*1.0e6);
    }

  MPI_Win_free(&window);
  MPI_Free_mem(snd_buf);
  MPI_Free_mem(rcv_buf);
  MPI_Finalize();

  return 0;
}
```
