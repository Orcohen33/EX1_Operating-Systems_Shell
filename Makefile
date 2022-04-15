
CC = gcc
CFLAGS = -g -Wall

HEADERS=shell.h
OBJECTS=shell.o
SOURCES=shell.c

main: $(TARGET)
	$(CC) $(CFLAGS) $^ -o main 


shell: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o shell


clean:
	$(RM) *.o shell server
