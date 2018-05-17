CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS = -Wall -lncurses -lmenu
OBJS = VIlain.o buffer.o configuration.o vue.o menu.o

all: VIlain

VIlain: $(OBJS)

%.o: %.c
	gcc -c -g -Wall $<

clean:
	rm *~ *.o ._* VIlain
