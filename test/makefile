all: test test2 window
test: test.o
	gcc -lncurses -o test test.o
test.o: test.c
	gcc -c test.c
test2: test2.o
	gcc -lncurses -o test2 test2.o
test2.o: test2.c
	gcc -c test2.c
window: window.o
	gcc -lncurses -o window window.o
window.o: window.c
	gcc -c window.c
clean:
	rm *~ *.o ._* test test2