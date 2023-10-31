#include <stdio.h>
#include "round.h"
#include "player.h"
#include "errstat.h" /* for error statuses */
#define NUM_OF_PLAYERS 4

static void TestRoundCreate(void);
static void TestRoundDestroy(void);
static void TestRunRound(void);

int main(void)
{
	/*
	TestRoundCreate();
	TestRoundDestroy();
	*/
	TestRunRound();

	return ERROR_OK;
}

static void TestRoundCreate(void)
{
	Round* ptrRound = NULL;
	Player* _arrPlayers[NUM_OF_PLAYERS];
	char* playerNames4[NUM_OF_PLAYERS] = {"David", "Shalom", "Lisa", "Irit"};
	int i;
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		_arrPlayers[i] = PlayerCreate(playerNames4[i], BOT);
	}
	printf("Test RoundCreate() 4 players ");
	ptrRound = RoundCreate(_arrPlayers, NUM_OF_PLAYERS);
	ptrRound != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DestroyPlayersFromTest(ptrRound);
	RoundDestroy(&ptrRound);
	printf("Test RoundCreate() 5 players ");
	ptrRound = RoundCreate(_arrPlayers, 5);
	ptrRound == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test RoundCreate() 0 players ");
	ptrRound = RoundCreate(_arrPlayers, 0);
	ptrRound == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	RoundDestroy(&ptrRound);
}

static void TestRoundDestroy(void)
{
	Round* ptrRound = NULL;
	Player* _arrPlayers[NUM_OF_PLAYERS];
	char* playerNames4[NUM_OF_PLAYERS] = {"David", "Shalom", "Lisa", "Irit"};
	int i;
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		_arrPlayers[i] = PlayerCreate(playerNames4[i], BOT);
	}
	printf("Test RoundDestroy() ptrRound ");
	ptrRound = RoundCreate(_arrPlayers, NUM_OF_PLAYERS);
	RoundDestroy(&ptrRound);
	ptrRound == NULL ? printf("- PASS\n") : printf("- FAIL \n");
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
	Player* _arrPlayers[NUM_OF_PLAYERS];
	char* playerNames4[NUM_OF_PLAYERS] = {"David", "Shalom", "Lisa", "Irit"};
	ERRStat resRun;
	int i;
	printf("Test RunRound(): 4 players ");
	for (i = 0; i < NUM_OF_PLAYERS; ++i)
	{
		_arrPlayers[i] = PlayerCreate(playerNames4[i], BOT);
	}
	ptrRound = RoundCreate(_arrPlayers, NUM_OF_PLAYERS);
	resRun = RunRound(ptrRound, PLAYER_FROM_LEFT);
	resRun == ERROR_SUCCESS ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test RunRound(): NULL ");
	resRun = RunRound(NULL, PLAYER_FROM_LEFT);
	resRun == ERROR_POINTER_NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DestroyPlayersFromTest(ptrRound);
	RoundDestroy(&ptrRound);
}


