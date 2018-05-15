all: VIlain

VIlain: VIlain.o buffer.o configuration.o vue.o menu.o
	gcc -o VIlain VIlain.o buffer.o configuration.o vue.o menu.o -lncurses -lmenu
VIlain.o: VIlain.c
	gcc -c -g -Wall VIlain.c

vue.o: vue.c
	gcc -c -g -Wall vue.c

buffer.o: buffer.c
	gcc -c -g -Wall buffer.c

configuration.o: configuration.c
	gcc -c -g -Wall configuration.c

menu.o: menu.c
	gcc -c -g -Wall menu.c

clean:
	rm *~ *.o ._* VIlain
