#include <stdio.h>
#include "deck.h"
#include "../../2genvector/vector.h"
#define OK 0;


static void TestDeckCreate(void);
static void TestDeckDestroy(void);
static void TestShuffleCards(void);
static void TestTakeCardFromDeck(void);

int main(void)
{
	printf("Tests\n");
	/*
	TestDeckCreate();
	TestDeckDestroy();
	*/
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
	Deck* ptrDeck = NULL;
	Deck* resShuffle = NULL;
	printf("Test TestShuffleCards() for valid ptrDeck ");
	ptrDeck = DeckCreate();
	resShuffle = ShuffleCards(ptrDeck);
	resShuffle != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test TestShuffleCards() for NULL ");
	resShuffle = ShuffleCards(NULL);
	resShuffle == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DeckDestroy(&ptrDeck);
}

static void TestTakeCardFromDeck(void)
{
	Deck* ptrDeck = NULL;
	Cards* resTakeCard = NULL;
	printf("Test TakeCardFromDeck() for valid ptrDeck ");
	ptrDeck = DeckCreate();
	resTakeCard = TakeCardFromDeck(ptrDeck);
	resTakeCard != NULL ? printf("- PASS\n") : printf("- FAIL \n");
	printf("Test TakeCardFromDeck() for NULL ");
	resTakeCard = TakeCardFromDeck(NULL);
	resTakeCard == NULL ? printf("- PASS\n") : printf("- FAIL \n");
	DeckDestroy(&ptrDeck);
}

