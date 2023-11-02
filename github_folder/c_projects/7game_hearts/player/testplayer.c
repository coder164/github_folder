#include <stdio.h>
#include <string.h> /* for strcmp */
#include <stdlib.h>	/* for free() */

#include "player.h"
#include "cards.h"	/* for Test GiveCardToPlayer */
#include "deck.h"	/* for Test GiveCardToPlayer */

#define MAX_NAME_LENGTH 30
#define OK 0

static void TestPlayerCreate(void);
static void TestDestroy(void);
static void TestGiveCardToPlayer(void);
static void TestTakeCardFromPlayer(void);

int main(void)
{
	TestPlayerCreate();
	TestDestroy();
	TestGiveCardToPlayer();
	TestTakeCardFromPlayer();
	return OK;
}

static void TestPlayerCreate(void)
{
	Player* ptrPlayer = NULL;
	char playerName[] = "David";
	char resName[MAX_NAME_LENGTH];
	printf("Test PlayerCreate() 'David', HUMAN ");
	ptrPlayer = PlayerCreate(playerName, HUMAN);
	ptrPlayer != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	PlayerDestroy(&ptrPlayer);
	printf("Test PlayerCreate() 'David', BOT ");
	ptrPlayer = PlayerCreate(playerName, BOT);
	ptrPlayer != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	PlayerDestroy(&ptrPlayer);
	printf("Test PlayerCreate() NULL, BOT ");
	ptrPlayer = PlayerCreate(NULL, HUMAN);
	ptrPlayer == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test PlayerCreate() correct name assumption ");
	ptrPlayer = PlayerCreate(playerName, HUMAN);
	GetName(ptrPlayer, resName);
	strcmp(resName, playerName) == 0 ? printf("- PASS\n") :
		printf("- FAIL \n");
	PlayerDestroy(&ptrPlayer);
}

static void TestDestroy(void)
{
	Player* ptrPlayer = NULL;
	char playerName[] = "David";
	printf("Test PlayerDestroy() ptrPlayer ");
	ptrPlayer = PlayerCreate(playerName, HUMAN);
	PlayerDestroy(&ptrPlayer);
	ptrPlayer == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test PlayerDestroy() ptrPlayer double destroy ");
	PlayerDestroy(&ptrPlayer);
	ptrPlayer == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test PlayerDestroy() NULL ");
	PlayerDestroy(NULL);
	printf("- PASS\n");
}

static void TestGiveCardToPlayer(void)
{
	Player* ptrPlayer = NULL;
	ERRStat resGiveCard;
	Deck* deck = NULL;
	Card* card = NULL;
	char playerName[] = "David";
	printf("Test GiveCardToPlayer(): ptrPlayer, card, index ");
	ptrPlayer = PlayerCreate(playerName, HUMAN);
	deck = DeckCreate();
	card = TakeCardFromDeck(deck);
	resGiveCard = GiveCardToPlayer(ptrPlayer, card);
	resGiveCard == ERROR_SUCCESS ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test GiveCardToPlayer(): NULL, card, index ");
	resGiveCard = GiveCardToPlayer(NULL, card);
	resGiveCard == ERROR_POINTER_NULL ? printf("- PASS\n") :
		printf("- FAIL \n");
	printf("Test GiveCardToPlayer(): ptrPlayer, NULL, index ");
	resGiveCard = GiveCardToPlayer(ptrPlayer, NULL);
	resGiveCard == ERROR_POINTER_NULL ? printf("- PASS\n") :
		printf("- FAIL \n");
	printf("Test GiveCardToPlayer(): correct num of cards 1 card in hand");
	GetNumOfCards(ptrPlayer) == 1 ? printf("- PASS\n") : printf("- FAIL \n");
	free(card);
	DeckDestroy(&deck);
	PlayerDestroy(&ptrPlayer);
}

static void TestTakeCardFromPlayer(void)
{
	Player* ptrPlayer = NULL;
	ERRStat resTakeCard;
	Deck* deck = NULL;
	Card* card = NULL;
	char playerName[] = "David";
	printf("Test TakeCardFromPlayer(): ptrPlayer, card");
	ptrPlayer = PlayerCreate(playerName, HUMAN);
	deck = DeckCreate();
	card = TakeCardFromDeck(deck);
	GiveCardToPlayer(ptrPlayer, card);
	resTakeCard = TakeCardFromPlayer(ptrPlayer, card);
	resTakeCard == ERROR_OK ? printf("- PASS\n") :
		printf("- FAIL \n");
	printf("Test TakeCardFromPlayer(): when there is no cards");
	resTakeCard = TakeCardFromPlayer(ptrPlayer, card);
	resTakeCard == ERROR_GENERAL ? printf("- PASS\n") :
		printf("- FAIL \n");
	free(card);
	printf("Test TakeCardFromPlayer(): ptrPlayer, NULL");
	GiveCardToPlayer(ptrPlayer, NULL);
	resTakeCard = TakeCardFromPlayer(ptrPlayer, NULL);
	resTakeCard == ERROR_POINTER_NULL ? printf("- PASS\n") :
		printf("- FAIL \n");
	printf("Test TakeCardFromPlayer(): NULL, card");
	card = TakeCardFromDeck(deck);
	GiveCardToPlayer(ptrPlayer, card);
	resTakeCard = TakeCardFromPlayer(NULL, card);
	resTakeCard == ERROR_POINTER_NULL ? printf("- PASS\n") :
		printf("- FAIL \n");
	free(card);
	DeckDestroy(&deck);
	PlayerDestroy(&ptrPlayer);
}
