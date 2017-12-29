objects = ku-latency send-data
all: $(objects)

$(objects): %: %.c
				$(CC) $(CFLAGS) -o $@ $<
