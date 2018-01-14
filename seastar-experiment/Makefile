SEASTAR ="/data1/sungho/seastar"
TARGET="getting-started"


all:
	c++ -std=c++11 `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
