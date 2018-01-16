# SEASTAR ="/home/sungho/seastar"
SEASTAR ="/data1/sungho/seastar"
TARGET ="server"

all:
	g++-5  `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` /usr/lib/libboost_program_options.so ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
