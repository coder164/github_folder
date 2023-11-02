#include <stdio.h>
#include <stdlib.h>	/* for free() in TestTakeCardFromDeck() */

#include "deck.h"
#include "../../2genvector/vector.h"

#define OK 0;

static void TestDeckCreate(void);
static void TestDeckDestroy(void);
static void TestShuffleCards(void);
static void TestTakeCardFromDeck(void);

int main(void)
{
	TestDeckCreate();
	TestDeckDestroy();
	TestShuffleCards();
	TestTakeCardFromDeck();
	return OK;
}

static void TestDeckCreate(void)
{
	Deck* ptrDeck = NULL;
	printf("Test DeckCreate() ");
	ptrDeck = DeckCreate();
	ptrDeck != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DeckDestroy(&ptrDeck);
}

static void TestDeckDestroy(void)
{
	Deck* ptrDeck = NULL;
	printf("Test DeckDestroy() for ptrDeck ");
	ptrDeck = DeckCreate();
	DeckDestroy(&ptrDeck);
	ptrDeck == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test DeckDestroy() for double destroy ptrDeck ");
	DeckDestroy(&ptrDeck);
	ptrDeck == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test DeckDestroy() NULL ");
	DeckDestroy(NULL);
	printf("- PASS\n");
}

static void TestShuffleCards(void)
{
	Deck* ptrDeck;
	printf("Test TestShuffleCards() for valid ptrDeck ");
	ptrDeck = DeckCreate();
	ptrDeck = ShuffleCards(ptrDeck);
	ptrDeck != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DeckDestroy(&ptrDeck);
	printf("Test TestShuffleCards() for NULL ");
	ptrDeck = ShuffleCards(NULL);
	ptrDeck == NULL ? printf("- PASS\n") : printf("- FAIL \n");
}

static void TestTakeCardFromDeck(void)
{
	Deck* ptrDeck = NULL;
	Card* resTakeCard = NULL;
	printf("Test TakeCardFromDeck() for valid ptrDeck ");
	ptrDeck = DeckCreate();
	resTakeCard = TakeCardFromDeck(ptrDeck);
	resTakeCard != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	free(resTakeCard);
	printf("Test TakeCardFromDeck() for NULL ");
	resTakeCard = TakeCardFromDeck(NULL);
	resTakeCard == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DeckDestroy(&ptrDeck);
}

