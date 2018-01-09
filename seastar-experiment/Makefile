SEASTAR ="/home/sungho/seastar"
TARGET="e02_futures_continuation"


all:
	c++ `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
