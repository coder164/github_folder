# makefile for the testdeck of the project

TARGET = testdeck.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = testdeck.o deck.o vector.o
P_CARDS = ../cards/
P_VEC = ../../2genvector/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

deck.o: deck.c deck.h $(P_CARDS)cards.h $(P_VEC)vector.h
	$(CC) $(CFLAGS)  -c deck.c

vector.o: $(P_VEC)vector.c $(P_VEC)vector.h
	$(CC) $(CFLAGS) -c $(P_VEC)vector.c

testdeck.o: testdeck.c deck.h $(P_VEC)vector.h $(P_CARDS)cards.h
	$(CC) $(CFLAGS) -c testdeck.c

valgrind:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./testdeck.out

clean:
	rm -f $(TARGET) $(OBJS) V2.log
