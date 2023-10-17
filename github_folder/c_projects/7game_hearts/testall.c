#include <stdio.h>
#include "game/game.h"
#include "round/round.h"
#include "player/player.h"
#define NUM_OF_PLAYERS 4

int main(void)
{
	Game* ptrGame;
	char* playerNames[] = {"David", "Shalom", "Lisa", "Irit"};
	ptrGame = GameCreate(playerNames, NUM_OF_PLAYERS, BOT);
	GameRun(ptrGame);
	GameDestroy(&ptrGame);
	printf("Check - Pass\n");
	return 0;
}
