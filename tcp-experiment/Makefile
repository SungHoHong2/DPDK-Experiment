objects = client server client_latency
all: $(objects)

$(objects): %: %.c
				$(CC) $(CFLAGS) -o $@ $<
