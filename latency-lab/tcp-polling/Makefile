TARGET="polling"

all: # for visasu
	cc -O -gdwarf-2 -g -o ${TARGET} ${TARGET}.c -pthread -lpthread

.PHONY: clean
clean:
	rm -f *.o ${TARGET}
