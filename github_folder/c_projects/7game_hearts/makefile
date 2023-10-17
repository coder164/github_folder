# makefile for integrated game parts all together

TARGET = testall.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = vector.o ui.o deck.o player.o round.o game.o testall.o 
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
	$(P_PLAYER)player.h $(P_CARDS)cards.h $(P_VEC)vector.h \
	errstat.h $(P_DECK)deck.h

	$(CC) $(CFLAGS) -I $(P_PLAYER) -I $(P_ROUND) -I \
	-I $(P_GAME) -c $(P_GAME)game.c

round.o: $(P_ROUND)round.c $(P_ROUND)round.h $(P_DECK)deck.h \
	$(P_PLAYER)player.h $(P_CARDS)cards.h $(P_GAME)game.h \
	$(P_VEC)vector.h

	$(CC) $(CFLAGS) -I $(P_ROUND) -I $(P_DECK) -I $(P_PLAYER) \
	-I $(P_CARDS) -I $(P_GAME) -I $(P_VEC) -c $(P_ROUND)round.c

deck.o: $(P_DECK)deck.c $(P_DECK)deck.h $(P_CARDS)cards.h \
	$(P_VEC)vector.h

	$(CC) $(CFLAGS) -I $(P_DECK) -I $(P_CARDS) -I $(P_VEC) \
	-c $(P_DECK)deck.c

player.o: $(P_PLAYER)player.c $(P_PLAYER)player.h \
	$(P_CARDS)cards.h $(P_VEC)vector.h $(P_DECK)deck.h errstat.h

	$(CC) $(CFLAGS) -I $(P_PLAYER) -I $(P_CARDS) -c $(P_PLAYER)player.c

ui.o: $(P_UI)ui.c
	$(CC) $(CFLAGS) -I $(P_UI) -c $(P_UI)ui.c

vector.o: $(P_VEC)vector.c $(P_UI)ui.h
	$(CC) $(CFLAGS) -I $(P_VEC) -c $(P_VEC)vector.c

testall.o: testall.c $(P_GAME)game.h $(P_PLAYER)player.h \
	$(P_ROUND)round.h errstat.h

	$(CC) $(CFLAGS) -I $(P_PLAYER) -I $(P_ROUND) -I $(P_GAME) -c testall.c

clean:
	rm -f $(TARGET) $(OBJS)
