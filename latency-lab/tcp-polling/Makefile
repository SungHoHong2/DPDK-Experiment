TARGET="epolling"
TARGET_2="persocket"


all:
	cc -O -gdwarf-2 -g -o ${TARGET} ${TARGET}.c -pthread -lpthread
	cc -O -gdwarf-2 -g -o ${TARGET_2} ${TARGET_2}.c -pthread -lpthread

.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_2}
