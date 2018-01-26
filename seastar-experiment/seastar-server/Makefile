# SEASTAR ="/home/sungho/seastar"
SEASTAR ="/data1/sungho/seastar"
TARGET ="server"

all:
	g++-5 --whole-archive --Wl, `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` --whole-archive -Wl, ${TARGET}.cc -o ${TARGET}


.PHONY: clean
clean:
	rm -f *.o ${TARGET}
