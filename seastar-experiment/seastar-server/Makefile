# SEASTAR ="/home/sungho/seastar"
SEASTAR="/data1/seastar"
TARGET="server"
TARGET_2="client"

all:
	c++ `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}
	c++ ${TARGET_2}.cc -o ${TARGET_2}

.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_2}
