SEASTAR ="/data1/sungho/seastar"
TARGET="getting-started"


all:
	g++-5 `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pk` ${TARGET}.cc -o ${TARGET}

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
