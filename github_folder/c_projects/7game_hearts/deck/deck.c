#include <stdlib.h>

#include "deck.h"
#include "../cards/cards.h"
#include "../../2genvector/vector.h"

#define SHUFFLE_FACTOR 64

/******************** Assistance Functions ********************/
static Vector* CreateCards(void);
static void Swap(Vector* _deck, int _first, int _second);
static void DestroyCard(void* _card);
/**************************************************************/

struct Deck {
    Vector* m_cards;
};

Deck* DeckCreate(void)
{
    int i;
    Deck* newDeck = NULL;
    Vector* cards = NULL;
    newDeck = (Deck*)malloc(sizeof(Deck));
    if (NULL == newDeck)
    {
        return NULL;
    }
    cards = CreateCards();
    if (NULL == cards)
    {
        return NULL;
    }
    newDeck -> m_cards = cards;
    return newDeck;
}

void DeckDestroy(Deck** _deck)
{
    if (NULL == _deck || NULL == *_deck)
    {
        return;
    }
    VectorDestroy(&((*_deck) -> m_cards), DestroyCard);
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
        Swap(_deck -> m_cards, i, j);
    }
    return _deck;
}

Card* TakeCardFromDeck(Deck* _deck)
{
    void* card;
    if (NULL == _deck)
    {
        return NULL;
    }
    if (VectorRemove(_deck -> m_cards, &card) != VECTOR_OK)
    {
        return NULL;
    }
    else
    {
        return card;
    }
}

/******************** Assistance Functions ********************/

static Vector* CreateCards(void)
{
    int i;
    Card* newCard = NULL;
    Vector* cards;
    cards = VectorCreate(CARDS_FACTOR, 0);
    if (NULL == cards) 
    {
        return NULL;
    }
    for (i = 0; i < CARDS_FACTOR; ++i)
    {
        newCard = (Card*)malloc(sizeof(Card));
        if (NULL == newCard) 
        {
            VectorDestroy(&cards, NULL);
            return NULL;
        }
        newCard -> m_suit =  i / NUM_OF_RANK;
        newCard -> m_rank = i % NUM_OF_RANK;
        VectorAppend(cards, newCard);
    }
    return cards;
}

static void DestroyCard(void* _card)
{
    free(_card);
}

static void Swap(Vector* _vectorOfCards, int _first, int _second)
{
    void *a, *b;
    VectorGet(_vectorOfCards, _first, &a);
    VectorGet(_vectorOfCards, _second, &b);
    VectorSet(_vectorOfCards, _first, b);
    VectorSet(_vectorOfCards, _second, a);
}
