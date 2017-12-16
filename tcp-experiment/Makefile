objects = client server
all: $(objects)

$(objects): %: %.c
        $(CC) $(CFLAGS) -o $@ $<
