# makefile for integrated game parts all together

TARGET = testall.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = vector.o deck.o player.o round.o game.o testall.o 
P_GAME = game/
P_ROUND = round/
P_CARDS = cards/
P_DECK = deck/
P_PLAYER = player/
P_UI = ui/
P_VEC = ../2genvector/

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

game.o: $(P_GAME)game.c $(P_GAME)game.h $(P_ROUND)round.h \
	$(P_PLAYER)player.h errstat.h

	$(CC) $(CFLAGS) -c $(P_GAME)game.c

round.o: $(P_ROUND)round.c $(P_ROUND)round.h $(P_VEC)vector.h \
	$(P_CARDS)cards.h $(P_DECK)deck.h $(P_PLAYER)player.h   \
	errstat.h

	$(CC) $(CFLAGS) -c $(P_ROUND)round.c

deck.o: $(P_DECK)deck.c $(P_DECK)deck.h $(P_VEC)vector.h \
	$(P_CARDS)cards.h	

	$(CC) $(CFLAGS) -c $(P_DECK)deck.c

player.o: $(P_PLAYER)player.c $(P_PLAYER)player.h \
	$(P_VEC)vector.h $(P_CARDS)cards.h $(P_DECK)deck.h errstat.h

	$(CC) $(CFLAGS) -c $(P_PLAYER)player.c

vector.o: $(P_VEC)vector.c $(P_VEC)vector.h
	$(CC) $(CFLAGS) -c $(P_VEC)vector.c

testall.o: testall.c
	$(CC) $(CFLAGS) -c testall.c

clean:
	rm -f $(TARGET) $(OBJS)
