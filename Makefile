
CC = gcc
CFLAGS = -g -Wall

HEADERS=main.h
OBJECTS=main.o
SOURCES=main.c


main: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o main 

clean:
	$(RM) *.o main server
