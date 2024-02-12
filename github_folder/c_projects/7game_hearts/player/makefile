# makefile for testplayer for Hearts project

TARGET = testplayer.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = testplayer.o player.o vector.o deck.o
P_DECK = ../deck/
P_CARDS = ../cards/
P_VEC = ../../2genvector/
P_ERRSTAT = ../

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

deck.o: $(P_DECK)deck.c $(P_DECK)deck.h $(P_CARDS)cards.h $(P_VEC)vector.h
	$(CC) $(CFLAGS) -I $(P_DECK) -I $(P_CARDS) -I $(P_VEC) -c $(P_DECK)deck.c

vector.o: $(P_VEC)vector.c $(P_VEC)vector.h
	$(CC) $(CFLAGS) -I $(P_VEC) -c $(P_VEC)vector.c

player.o: player.c player.h $(P_CARDS)cards.h $(P_VEC)vector.c $(P_DECK)deck.h
	$(CC) $(CFLAGS) -I $(P_CARDS) -I $(P_VEC) -I $(P_DECK) -c player.c

testplayer.o: testplayer.c $(P_CARDS)cards.h $(P_ERRSTAT)errstat.h $(P_DECK)deck.h
	$(CC) $(CFLAGS) -I $(P_CARDS) -I $(P_ERRSTAT) -I $(P_DECK) -c testplayer.c

valgrind:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./testplayer.out

clean:
	rm -f $(TARGET) $(OBJS) V2.log
