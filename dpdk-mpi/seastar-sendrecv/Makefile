SEASTAR ="/home/sungho/seastar"
TARGET ="tcp_test"

all:
	g++-5  `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
