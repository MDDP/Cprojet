CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS = -Wall $(shell pkg-config --libs check)
OBJS = Test.o configuration.o

all: test_config

test_config: test_config.o configuration.o

test: test_config
	./$<

%.o: %.c
	gcc -c -g -Wall $<

clean:
	rm *.o test_config
