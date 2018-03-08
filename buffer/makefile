all: test
test: test.o buffer.o
	gcc -o test test.o buffer.o
test.o: test.c
	gcc -c -g -Wall test.c
buffer.o: buffer.c buffer.h
	gcc -c -g -Wall buffer.c
clear:
	rm *~ *.o test *.exe