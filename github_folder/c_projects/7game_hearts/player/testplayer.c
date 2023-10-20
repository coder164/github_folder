#include <stdio.h>
#include <string.h> /* for strcmp */
#include "player.h"
#include "cards.h"	/* for Test GiveCardToPlayer */
#include "deck.h"	/* for Test GiveCardToPlayer */
#define MAX_NAME_LENGTH 30
#define OK 0

static void TestPlayerCreate(void);
static void TestDestroy(void);
static void TestGiveCardToPlayer(void);

int main(void)
{
	printf("Tests\n");
	TestPlayerCreate();
	/*
	TestDestroy();
	TestGiveCardToPlayer();
	*/
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
	/*
	printf("Test PlayerCreate() 'David', BOT ");
	ptrPlayer = PlayerCreate(playerName, BOT);
	ptrPlayer != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	PlayerDestroy(&ptrPlayer);
	printf("Test PlayerCreate() NULL, BOT ");
	ptrPlayer = PlayerCreate(NULL, HUMAN);
	ptrPlayer == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test PlayerCreate correct name assumption ");
	ptrPlayer = PlayerCreate(playerName, HUMAN);
	GetName(ptrPlayer, resName);
	strcmp(resName, playerName) == 0 ? printf("- PASS\n") :
		printf("- FAIL \n");
	PlayerDestroy(&ptrPlayer);
	*/
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
	Deck* deck;
	Card* card;
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
	DeckDestroy(&deck);
	PlayerDestroy(&ptrPlayer);
}
