#include <stdio.h>
#include "game.h"
#include "round.h"
#include "player.h"
#include "errstat.h" /* for error statuses */
#define NUM_OF_PLAYERS 4

static void TestGameCreate(void);
static void TestGameDestory(void);
static void TestGameRun(void);

int main(void)
{
	printf("Tests\n");
	TestGameCreate();
	TestGameDestory();
	/*
	TestGameRun();
	*/

	return ERROR_OK;
}

static void TestGameCreate(void)
{
	Game* ptrGame;
	char* playerNames4[] = {"David", "Shalom", "Lisa", "Irit"};
	printf("Test GameCreate() 4 nameplayers, 4 players, BOT ");
	ptrGame = GameCreate(playerNames4, NUM_OF_PLAYERS, BOT);
	ptrGame != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() NULL nameplayers, 4 players, BOT ");
	ptrGame = GameCreate(NULL, NUM_OF_PLAYERS, BOT);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, 0 players, BOT ");
	ptrGame = GameCreate(playerNames4, 0, BOT);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, -1 players, BOT ");
	ptrGame = GameCreate(playerNames4, -1, BOT);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, 4 players, BOT ");
	ptrGame = GameCreate(playerNames4, NUM_OF_PLAYERS, HUMAN);
	ptrGame != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() NULL nameplayers, 4 players, HUMAN ");
	ptrGame = GameCreate(NULL, NUM_OF_PLAYERS, HUMAN);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, 0 players, HUMAN ");
	ptrGame = GameCreate(playerNames4, 0, HUMAN);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	GameDestroy(&ptrGame);
	printf("Test GameCreate() 4 nameplayers, -1 players, HUMAN ");
	ptrGame = GameCreate(playerNames4, -1, HUMAN);
	ptrGame == NULL ? printf("- PASS\n") : printf("- FAIL \n");
}

static void TestGameDestory(void)
{
	Game* ptrGame;
	char* playerNames4[4] = {"David", "Shalom", "Lisa", "Irit"};
	printf("Test GameDestroy() ptrGame ");
	ptrGame = GameCreate(playerNames4, NUM_OF_PLAYERS, BOT);
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
	printf("Test GameRun() for valid ptrGame ");
	ptrGame = GameCreate(playerNames4, NUM_OF_PLAYERS, BOT);
	resGameRun = GameRun(ptrGame);
	resGameRun == ERROR_SUCCESS ? printf("- PASS\n") : printf("- FAIL \n");
	/* to continue here */
	GameDestroy(&ptrGame);
}



