SEASTAR ="/data1/sungho/seastar"
TARGET="getting-started"


all:
	c++ -std=gnu++1y -g `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
