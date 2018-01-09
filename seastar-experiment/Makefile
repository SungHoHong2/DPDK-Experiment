SEASTAR ="/home/sungho/seastar"
TARGET="e01_threads_memory"
TARGET_2="e02_futures_continuation"


all:
	c++ `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}
	c++ `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET_2}.cc -o ${TARGET_2}

.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TAEGET_2}
