SEASTAR ="/home/sungho/seastar"
TARGET = "server"
TARGET_2 = "client"


all:
	g++-5 -g `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}
	g++-5 -g `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET_2}.cc -o ${TARGET_2}


.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_2}
