all: VIlain
VIlain: VIlain.o buffer.o configuration.o
	gcc -o VIlain VIlain.o buffer.o configuration.o -lncurses
VIlain.o: VIlain.c
	gcc -c -g -Wall VIlain.c
buffer.o: buffer.c buffer.h
	gcc -c -g -Wall buffer.c
configuration.o: configuration.c configuration.h
	gcc -c -g -Wall configuration.c
clean:
	rm *~ *.o ._* VIlain
