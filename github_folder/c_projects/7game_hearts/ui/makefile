# makefile for the user interface part

TARGET = ui.out
CC = gcc
CFLAGS = -ansi -pedantic -g
OBJS = ui.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c

valgrind:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./ui.out

clean:
	rm -f $(TARGET) $(OBJS) V2.log
