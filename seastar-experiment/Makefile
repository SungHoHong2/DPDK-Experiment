SEASTAR ="/data1/sungho/seastar"
TARGET="e04_when_all"


all:
	c++ --compiler g++-5 `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
