CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS = -Wall $(shell pkg-config --libs check)

all: buffertest

buffertest: buffertest.o ../src/buffer.o

%.o: %.c
	gcc -c -g -Wall $<

clean:
	rm *.o main_test
