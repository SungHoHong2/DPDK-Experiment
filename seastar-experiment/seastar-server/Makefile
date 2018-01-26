# SEASTAR ="/home/sungho/seastar"
SEASTAR ="/data1/sungho/seastar"
TARGET ="server"

all:
	g++-5  -Wl,--whole-archive `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}


.PHONY: clean
clean:
	rm -f *.o ${TARGET}
