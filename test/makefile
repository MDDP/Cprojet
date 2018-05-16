all: buffertest
buffertest: buffertest.o buffer.o
	gcc -o buffertest buffertest.o buffer.o
buffertest.o: buffertest.c
	gcc -Wall -c buffertest.c
buffer.o: ../src/buffer.c
	gcc -Wall -c ../src/buffer.c

clean:
	rm *.o buffertest