TARGET="helloworld"
TARGET_1="tutorial_1"


all:
	g++ -g -o ${TARGET} helloworld.cpp
	g++ -g -o ${TARGET_1} ${TARGET_1}.cpp


.PHONY: clean
clean:
	rm -f *.o ${TARGET} ${TARGET_1}
