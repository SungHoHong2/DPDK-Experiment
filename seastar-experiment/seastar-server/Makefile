# SEASTAR ="/home/sungho/seastar"
SEASTAR ="/data1/sungho/seastar"
TARGET ="server"
TARGET_2="client"

all:
	c++-5 `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}
	c++-5 ${TARGET_2}.cc -o ${TARGET_2}

.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_2}
