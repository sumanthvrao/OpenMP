CC=gcc # compiler
TARGET=main # target file name

CFLAGS = -Wall -fopenmp # set the flags (options) to be used with the default compiler
all:	main.o FILLPT.o
	$(CC) $(CFLAGS) main.c FILLPT.c -o $(TARGET)

clean:
	rm *.o $(TARGET)