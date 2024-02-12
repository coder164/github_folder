# makefile for the testgame of the project

TARGET = testgame.out
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = testgame.o game.o round.o deck.o player.o ui.o vector.o
P_ROUND = ../round/
P_CARDS = ../cards/
P_DECK = ../deck/
P_PLAYER = ../player/
P_UI = ../ui/
P_VEC = ../../2genvector/
P_ERRSTAT = ../

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

game.o: game.c game.h $(P_ROUND)round.h $(P_PLAYER)player.h \
	$(P_ERRSTAT)errstat.h

	$(CC) $(CFLAGS) -I $(P_ROUND) -I $(P_PLAYER) \
	-I $(P_ERRSTAT) -c game.c

round.o: $(P_ROUND)round.c $(P_ROUND)round.h $(P_DECK)deck.h \
	$(P_PLAYER)player.h $(P_ERRSTAT)errstat.h $(P_VEC)vector.h \
	$(P_ERRSTAT) $(P_CARDS)cards.h

	$(CC) $(CFLAGS) -I $(P_ROUND) -I $(P_DECK) -I $(P_PLAYER) \
	-I $(P_CARDS) -I $(P_VEC) -c $(P_ROUND)round.c

deck.o: $(P_DECK)deck.c $(P_DECK)deck.h $(P_CARDS)cards.h \
	$(P_VEC)vector.h

	$(CC) $(CFLAGS) -I $(P_DECK) -I $(P_CARDS) -I $(P_VEC) \
	-c $(P_DECK)deck.c

player.o: $(P_PLAYER)player.c $(P_PLAYER)player.h \
	$(P_CARDS)cards.h $(P_VEC)vector.h $(P_ERRSTAT)errstat.h \
	$(P_DECK)deck.h
	
	$(CC) $(CFLAGS) -I $(P_PLAYER) -I $(P_CARDS) -I $(P_VEC) \
	-I $(P_ERRSTAT) -I $(P_DECK) -c $(P_PLAYER)player.c

ui.o: $(P_UI)ui.c $(P_UI)ui.h
	$(CC) $(CFLAGS) -I $(P_UI) -c $(P_UI)ui.c

vector.o: $(P_VEC)vector.c $(P_VEC)vector.h
	$(CC) $(CFLAGS) -I $(P_VEC) -c $(P_VEC)vector.c

testgame.o: testgame.c game.h $(P_ROUND)round.h \
	$(P_PLAYER)player.h $(P_ERRSTAT)errstat.h

	$(CC) $(CFLAGS) -I $(P_ROUND) -I $(P_PLAYER) \
	-I $(P_ERRSTAT) -c testgame.c

valgrind:
	valgrind --log-file=V2.log --leak-check=full --track-origins=yes ./testgame.out

clean:
	rm -f $(TARGET) $(OBJS) V2.log
	
	
	

