SEASTAR ="/data1/sungho/seastar"
TARGET="getting-started"


all:
	$(CC) -g `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
