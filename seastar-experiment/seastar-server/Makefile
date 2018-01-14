# SEASTAR ="/home/sungho/seastar"
SEASTAR ="/data1/sungho/seastar"
TARGET ="server"
TARGET_2="client"

all:
	c++  `pkg-config --cflags --libs ${SEASTAR}/build/release/seastar.pc` ${TARGET}.cc -o ${TARGET}
	c++  ${TARGET_2}.cc -o ${TARGET_2}

.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_2}

	sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5
