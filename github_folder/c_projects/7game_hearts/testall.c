#include <stdio.h>

#include "game/game.h"
#define NUM_OF_PLAYERS 4
#define OK 0

int main(void)
{
	Game* ptrGame;
	char* playerNames[] = {"David", "Shalom", "Lisa", "Irit"};
	PlayerType types[] = {BOT, BOT, BOT, BOT};
	ptrGame = GameCreate(playerNames, types, NUM_OF_PLAYERS);
	GameRun(ptrGame);
	GameDestroy(&ptrGame);
	printf("Check - Pass\n");
	return OK;
}
