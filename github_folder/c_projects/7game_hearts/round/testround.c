#include <stdio.h>

#include "round.h"
#include "../player/player.h"
#include "../errstat.h" /* for error statuses */

#define NUM_OF_PLAYERS 4
#define OK 0

static void TestRoundCreate(void);
static void TestRoundDestroy(void);
static void TestRunRound(void);

int main(void)
{
	TestRoundCreate();
	TestRoundDestroy();
	TestRunRound();
	return OK;
}

static void TestRoundCreate(void)
{
	Round* ptrRound = NULL;
	Player* arrPlayers[NUM_OF_PLAYERS];
	char* playerNames4[NUM_OF_PLAYERS] = {"David", "Shalom", "Lisa", "Irit"};
	int i;
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		arrPlayers[i] = PlayerCreate(playerNames4[i], BOT);
	}
	printf("Test RoundCreate() 4 players ");
	ptrRound = RoundCreate(arrPlayers, NUM_OF_PLAYERS, 0);
	ptrRound != NULL ? printf("- PASS\n") : printf("- FAIL\n");
	RoundDestroy(&ptrRound);
	printf("Test RoundCreate() 5 players ");
	ptrRound = RoundCreate(arrPlayers, 5, 0);
	ptrRound == NULL ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test RoundCreate() 0 players ");
	ptrRound = RoundCreate(arrPlayers, 0, 0);
	ptrRound == NULL ? printf("- PASS\n") : printf("- FAIL\n");
	RoundDestroy(&ptrRound);
}

static void TestRoundDestroy(void)
{
	Round* ptrRound = NULL;
	Player* arrPlayers[NUM_OF_PLAYERS];
	char* playerNames4[NUM_OF_PLAYERS] = {"David", "Shalom", "Lisa", "Irit"};
	int i;
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		arrPlayers[i] = PlayerCreate(playerNames4[i], BOT);
	}
	printf("Test RoundDestroy() ptrRound ");
	ptrRound = RoundCreate(arrPlayers, NUM_OF_PLAYERS, 0);
	RoundDestroy(&ptrRound);
	ptrRound == NULL ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test RoundDestroy() double destroy ");
	RoundDestroy(&ptrRound);
	printf("- PASS\n");
	printf("Test RoundDestroy() NULL ");
	RoundDestroy(NULL);
	printf("- PASS\n");
}

static void TestRunRound(void)
{
	Round* ptrRound = NULL;
	Player* arrPlayers[NUM_OF_PLAYERS];
	char* playerNames4[NUM_OF_PLAYERS] = {"David", "Shalom", "Lisa", "Irit"};
	ERRStat resRun;
	int i;
	printf("Test RunRound(): 4 players ");
	arrPlayers[0] = PlayerCreate(playerNames4[0], BOT);
	for (i = 1; i < NUM_OF_PLAYERS; ++i)
	{
		arrPlayers[i] = PlayerCreate(playerNames4[i], BOT);
	}
	ptrRound = RoundCreate(arrPlayers, NUM_OF_PLAYERS, 0);
	resRun = RunRound(ptrRound, OPPOSITE);
	resRun == ERROR_SUCCESS ? printf("- PASS\n") : printf("- FAIL\n");
	RoundDestroy(&ptrRound);
	/*
	printf("Test RunRound(): NULL, LEFT ");
	resRun = RunRound(NULL, LEFT);
	resRun == ERROR_POINTER_NULL ? printf("- PASS\n") : printf("- FAIL\n");
	putchar('\n');
	*/
}
