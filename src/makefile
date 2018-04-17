all: configuration
	
VIlain: VIlain.o buffer.o configuration.o vue.o
	gcc -o VIlain VIlain.o buffer.o configuration.o -lncurses
VIlain.o: VIlain.c
	gcc -c -g -Wall VIlain.c
	
vue.o: vue.c
	gcc -c -g -Wall vue.c
	
buffer.o: buffer.c
	gcc -c -g -Wall buffer.c
	
configuration: configuration.o
	gcc -o configuration configuration.o
configuration.o: configuration.c
	gcc -c -g -Wall configuration.c
	
clean:
	rm *~ *.o ._* VIlain
