#include <stdio.h>
#include "game.h"
#include "round.h"
#include "player.h"
#include "errstat.h" /* for error statuses */
#define NUM_OF_PLAYERS 4
#define OK 0

static void TestGameCreate(void);
static void TestGameDestory(void);
static void TestGameRun(void);

int main(void)
{
	/*
	TestGameCreate();
	TestGameDestory();
	*/
	TestGameRun();
	return OK;
}

static void TestGameCreate(void)
{
	Game* ptrGame;
	PlayerType fourBots[] = {BOT, BOT, BOT, BOT};
	PlayerType singleHumanThreeBots[] = {HUMAN, BOT, BOT, BOT};
	char* playerNames4[] = {"David", "Shalom", "Lisa", "Irit"};
	printf("Test GameCreate() nameplayers, %d BOTs, %d players ", NUM_OF_PLAYERS, NUM_OF_PLAYERS);
	ptrGame = GameCreate(playerNames4, fourBots, NUM_OF_PLAYERS);
	ptrGame != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() NULL, %d BOTs, %d players ", NUM_OF_PLAYERS, NUM_OF_PLAYERS);
	ptrGame = GameCreate(NULL, fourBots, NUM_OF_PLAYERS);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	
	printf("Test GameCreate() nameplayers, %d BOTs, 0 players ", NUM_OF_PLAYERS);
	ptrGame = GameCreate(playerNames4, fourBots, 0);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() nameplayers,  %d BOTs, -1 players ", NUM_OF_PLAYERS);
	ptrGame = GameCreate(playerNames4, fourBots, -1);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() nameplayers, 1 HUMAN 3 BOTs, %d players ", NUM_OF_PLAYERS);
	ptrGame = GameCreate(playerNames4, singleHumanThreeBots, NUM_OF_PLAYERS);
	ptrGame != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() NULL nameplayers, 1 HUMAN 3 BOTs, %d players ", NUM_OF_PLAYERS);
	ptrGame = GameCreate(NULL, singleHumanThreeBots, NUM_OF_PLAYERS);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, 1 HUMAN 3 BOTs, 0 players ");
	ptrGame = GameCreate(playerNames4, singleHumanThreeBots, 0);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, 1 HUMAN 3 BOTs, -1 players ");
	ptrGame = GameCreate(playerNames4, singleHumanThreeBots, -1);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
}

static void TestGameDestory(void)
{
	Game* ptrGame;
	char* playerNames4[4] = {"David", "Shalom", "Lisa", "Irit"};
	PlayerType fourBots[] = {BOT, BOT, BOT, BOT};
	printf("Test GameDestroy() ptrGame ");
	ptrGame = GameCreate(playerNames4, fourBots, NUM_OF_PLAYERS);
	GameDestroy(&ptrGame);
	ptrGame == NULL ? printf("- PASS\n") : printf(" FAIL \n");
	printf("Test GameDestroy() for double destroy ");
	GameDestroy(&ptrGame);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test GameDestroy() NULL ");
	GameDestroy(NULL);
	printf("- PASS\n");
}

static void TestGameRun(void)
{
	Game* ptrGame;
	ERRStat resGameRun;
	char* playerNames4[4] = {"David", "Shalom", "Lisa", "Irit"};
	PlayerType fourBots[] = {BOT, BOT, BOT, BOT};
	printf("Test GameRun() for valid ptrGame ");
	ptrGame = GameCreate(playerNames4, fourBots, NUM_OF_PLAYERS);
	resGameRun = GameRun(ptrGame);
	resGameRun == ERROR_SUCCESS ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
}



