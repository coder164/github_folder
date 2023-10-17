# makefile for the testrounds of the project

TARGET = testround.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = testround.o round.o deck.o player.o vector.o
P_DECK = ../deck/
P_PLAYER = ../player/
P_CARDS = ../cards/
P_VEC = ../../2genvector/# for deck.c
P_ERRSTAT = ../

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

round.o: round.c round.h $(P_DECK)deck.h $(P_PLAYER)player.h $(P_ERRSTAT)errstat.h $(P_VEC)vector.h $(P_CARDS)cards.h
	$(CC) $(CFLAGS) -I $(P_DECK) -I $(P_PLAYER) -I $(P_ERRSTAT) -I $(P_CARDS) -I $(P_VEC) -c round.c

deck.o: $(P_DECK)deck.c $(P_DECK)deck.h $(P_CARDS)cards.h $(P_VEC)vector.h $(P_ERRSTAT)errstat.h
	$(CC) $(CFLAGS) -I $(P_DECK) -I $(P_CARDS) -I $(P_VEC) -I $(P_ERRSTAT) -c $(P_DECK)deck.c

vector.o: $(P_VEC)vector.c $(P_VEC)vector.h
	$(CC) $(CFLAGS) -I $(P_VEC) -c $(P_VEC)vector.c

player.o: $(P_PLAYER)player.c $(P_PLAYER)player.h $(P_CARDS)cards.h $(P_VEC)vector.h $(P_DECK)deck.h $(P_ERRSTAT)errstat.h
	$(CC) $(CFLAGS) -I $(P_PLAYER) -I $(P_CARDS) -I $(P_VEC) -I $(P_DECK) -I $(P_ERRSTAT) -c $(P_PLAYER)player.c

testround.o: testround.c round.h $(P_PLAYER)player.h $(P_ERRSTAT)errstat.h $(P_CARDS)cards.h
	$(CC) $(CFLAGS) -I $(P_PLAYER) -I $(P_ERRSTAT) -I $(P_CARDS) -c testround.c

clean:
	rm -f $(TARGET) $(OBJS)



