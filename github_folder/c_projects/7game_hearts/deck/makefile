# makefile for testdeck for Hearts project

TARGET = testdeck.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = testdeck.o deck.o vector.o
P_CARDS = ../cards/
P_VEC = ../../2genvector/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

deck.o: deck.c deck.h $(P_CARDS)cards.h $(P_VEC)vector.h
	$(CC) $(CFLAGS) -I $(P_CARDS) -I $(P_VEC) -c deck.c

vector.o: $(P_VEC)vector.c $(P_VEC)vector.h
	$(CC) $(CFLAGS) -I $(P_VEC) -c $(P_VEC)vector.c

testdeck.o: testdeck.c deck.h $(P_VEC)vector.h $(P_CARDS)cards.h
	$(CC) $(CFLAGS) -I $(P_VEC) -I $(P_CARDS) -c testdeck.c

clean:
	rm -f $(TARGET) $(OBJS)
