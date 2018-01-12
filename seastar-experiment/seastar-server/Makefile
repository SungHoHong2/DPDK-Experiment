SEASTAR ="/home/sungho/seastar"
TARGET="server"

all:
	c++ `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
