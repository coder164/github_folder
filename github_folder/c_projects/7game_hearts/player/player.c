#include <stdlib.h>                     /* for malloc */
#include <string.h>                     /* for strcpy */
#include <stdio.h>

#include "player.h"
#include "../../2genvector/vector.h"    /* for cards vector */
#include "../cards/cards.h"             /* for Card object*/
#include "../deck/deck.h"               /* for CARDS_FACTOR*/
#include "../errstat.h"                 /* for status errors*/

#define MAX_NAME_LENGTH 30

/***************** Assitance Inner Functions ******************/
static int SearchCorrectIndex(Player* _player, Card* _card);
static void DestroyCard(void* _card);
static ERRStat IsSuitLower(Card* _card, Card* _tempCard);
static ERRStat IsSameSuit(Card* _card, Card* _tempCard);
static ERRStat IsRankLower(Card* _card, Card* _tempCard);
static ERRStat DoInsertion(Player* _player, Card* _card,
    int _index);

int IsSameCard(void* _card, size_t _index, void* _tempCard);

/*************** Assistance Functions for Tests ***************/
void GetName(Player* _player, char* _item);
int GetNumOfCards(Player* _player);
/**************************************************************/

struct Player {
    char m_name[MAX_NAME_LENGTH];
    Vector* m_cards;
    PlayerType m_type;
    int m_numOfCards; /* actual number of cards at the player */
};

Player* PlayerCreate(char _name[], PlayerType _type)
{
    Player* newPlayer;
    Vector* newCardsVector;
    if (NULL == _name)
    {
        return NULL;
    }
    newPlayer = (Player*)malloc(sizeof(Player));
    if (NULL == newPlayer)
    {
        return NULL;
    }
    newCardsVector = VectorCreate((CARDS_FACTOR / NUM_OF_PLAYERS), 0);
    if (NULL == newCardsVector)
    {
        free(newPlayer);
        return NULL;
    }
    newPlayer -> m_cards = newCardsVector;
    strcpy(newPlayer -> m_name, _name);
    newPlayer -> m_type = _type;
    newPlayer -> m_numOfCards = 0;
    return newPlayer;
}

void PlayerDestroy(Player** _player)
{
    if (NULL == _player || NULL == *_player)
    {
        return;
    }
    else if (NULL != (*_player) -> m_cards)
    {
        VectorDestroy(&((*_player) -> m_cards), DestroyCard);
        free((*_player) -> m_cards);
        (*_player) -> m_cards = NULL;
    }
    free(*_player);
    *_player = NULL;
}

ERRStat GiveCardToPlayer(Player* _player, void* _card)
{
    VectorResult result;
    if (NULL == _player || NULL == _card)
    {
        return ERROR_POINTER_NULL;
    }
    result = VectorAppend(_player -> m_cards, _card);
    if (result != VECTOR_OK)
    {
        return ERROR_GENERAL;
    }
    _player -> m_numOfCards++;
    return ERROR_SUCCESS;
}

ERRStat TakeCardFromPlayer(Player* _player, void** _card)
{
    if (NULL == _player || NULL == _card)
    {
        return ERROR_POINTER_NULL;
    }
    else if (0 == _player -> m_numOfCards)
    {
        return ERROR_GENERAL;
    }
    else
    {
        VectorRemove(_player -> m_cards, _card);
        _player -> m_numOfCards--;
        return ERROR_OK;
    }
}

PlayerType GetPlayerType(Player* _player)
{
    if (NULL == _player)
    {
        return UNDEFINED;
    }
    return _player -> m_type;
}

ERRStat IsHavingTwoOfClubs(const Player* const _player)
{
    size_t indexFound = 0;
    Card twoOfClubs = {TWO, CLUBS};
    void* ptrTwoOfClubs = &twoOfClubs;
    indexFound = VectorForEach(_player -> m_cards, IsSameCard, ptrTwoOfClubs);
    if (indexFound < _player -> m_numOfCards)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************** Assistance Functions ********************/

static ERRStat IsSuitLower(Card* _card, Card* _tempCard)
{
    return ((_card -> m_suit) < (_tempCard -> m_suit)) ? TRUE : FALSE;
}

static ERRStat IsSameSuit(Card* _card, Card* _tempCard)
{
    return ((_card -> m_suit) == (_tempCard -> m_suit)) ? TRUE : FALSE;
}

static ERRStat IsRankLower(Card* _card, Card* _tempCard)
{
    return ((_card -> m_rank) < (_tempCard -> m_rank)) ? TRUE : FALSE;
}

static void DestroyCard(void* _card)
{
    free(_card);
}

int IsSameCard(void* _card, size_t _index, void* _tempCard)
{
    if ( ( (*(Card*)_card).m_suit == (*(Card*)_tempCard).m_suit)
        &&
        ( (*(Card*)_card).m_rank == (*(Card*)_tempCard).m_rank) )
        {
            return TRUE;
        }
    else
    {
        return FALSE;
    }
}

/*************** Assistance Functions for Tests ***************/

void GetName(Player* _player, char* _item)
{
    strcpy(_item, _player -> m_name);
}

int GetNumOfCards(Player* _player)
{
    if (NULL == _player)
    {
        return 0;
    }
    return _player -> m_numOfCards;
}
