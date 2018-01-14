SEASTAR ="/home/sungho/seastar"
TARGET="getting-started"


all:
	g++-6 `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
