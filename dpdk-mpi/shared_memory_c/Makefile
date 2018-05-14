TARGET = client
TARGET_2 = server

all:
	gcc -g ${TARGET}.c -o ${TARGET}
	g++ -g ${TARGET_2}.cc -o ${TARGET_2}

.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_2}
