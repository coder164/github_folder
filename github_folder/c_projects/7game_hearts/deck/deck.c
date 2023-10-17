#include <stdlib.h>
#include "deck.h"
#include "cards.h"
#include "vector.h"

#define SHUFFLE_FACTOR 64

/* declare inner func */
static Vector* CreateCards(void);
static void Swap(Vector* _deck, int _first, int _second);
/* declare inner func */

struct Deck {
    Vector* m_vectorOfCards;
};

Deck* DeckCreate(void)
{
    int i;
    Deck* newDeck = NULL;
    Vector* vectorOfCards = NULL;
    newDeck = (Deck*)malloc(sizeof(Deck));
    if (NULL == newDeck)
    {
        return NULL;
    }
    vectorOfCards = CreateCards();
    if (NULL == vectorOfCards)
    {
        return NULL;
    }
    newDeck -> m_vectorOfCards = vectorOfCards;
    return newDeck;
}

void DeckDestroy(Deck** _deck)
{
    if (NULL == _deck || NULL == *_deck)
    {
        return;
    }
    VectorDestroy(&((*_deck) -> m_vectorOfCards), NULL);
    free(*_deck);
    *_deck = NULL;
}

Deck* ShuffleCards(Deck* _deck)
{
    int i, j, nMix;
    if (NULL == _deck)
    {
        return NULL;
    }
    for (nMix = 0; nMix < SHUFFLE_FACTOR; ++nMix)
    {
        i = rand() % CARDS_FACTOR;
        j = rand() % CARDS_FACTOR;
        Swap(_deck -> m_vectorOfCards, i, j);
    }
    return _deck;
}

Cards* TakeCardFromDeck(Deck* _deck)
{
    void* card;
    if (NULL == _deck)
    {
        return NULL;
    }
    VectorRemove(_deck -> m_vectorOfCards, &card);
    return card;
}

/**************************************************************/
/******************** Assistance Functions ********************/
/**************************************************************/

static Vector* CreateCards(void)
{
    int i;
    Cards* newCard = NULL;
    Vector* vectorOfCards;
    vectorOfCards = VectorCreate(CARDS_FACTOR, 0);
    if (NULL == vectorOfCards) 
    {
        return NULL;
    }
    for (i = 0; i < CARDS_FACTOR; ++i)
    {
        newCard = (Cards*)malloc(sizeof(Cards));
        if (NULL == newCard) 
        {
            VectorDestroy(&vectorOfCards, NULL);
            return NULL;
        }
        newCard -> m_suit =  i / NUM_OF_RANK;
        newCard -> m_rank = i % NUM_OF_RANK;
        VectorAppend(vectorOfCards, newCard);
    }
    return vectorOfCards;
}

static void Swap(Vector* _vectorOfCards, int _first, int _second)
{
    void *a, *b;
    VectorGet(_vectorOfCards, _first, &a);
    VectorGet(_vectorOfCards, _second, &b);
    VectorSet(_vectorOfCards, _first, b);
    VectorSet(_vectorOfCards, _second, b);
}

