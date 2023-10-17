#include <stdlib.h> /* for malloc */
#include <string.h> /* for strcpy */
#include "player.h"
#include "../cards/cards.h"
#include "../../2genvector/vector.h" /* for cards vector */
#include "../errstat.h" /* for statuses of errors*/
#include "../deck/deck.h" /* for CARDS_FACTOR*/

#define MAX_NAME_LENGTH 30

/* assistance functions for tests */
void GetName(Player* _player, char* _item);
int GetNumOfCards(Player* _player);
/* assitance inner functions */
static int SearchCorrectIndex(Player* _player, Cards* _card);
static ERRStat IsSuitLower(Cards* _card, Cards* _tempCard);
static ERRStat IsSameSuit(Cards* _card, Cards* _tempCard);
static ERRStat IsRankLower(Cards* _card, Cards* _tempCard);
static ERRStat DoInsertion(Player* _player, Cards* _card,
    int _index);

struct Player {
    char m_name[MAX_NAME_LENGTH];
    Vector* m_cards;
    PlayerType m_type;
    int m_numOfCards; /* actual number of cards at the palyer */
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
    if (NULL == _player)
    {
        return;
    }
    CardsDestroy(_player);
    free(*_player);
    *_player = NULL;
}

void CardsDestroy(Player** _player)
{
    if (NULL == _player || NULL == *_player || 0 == (*_player) -> m_numOfCards)
    {
        return;
    }
    VectorDestroy(&((*_player) -> m_cards), NULL);
    free((*_player) -> m_cards);
    (*_player) -> m_cards = NULL;
}

ERRStat GiveCardToPlayer(Player* _player, void* _card)
{
    int _index;
    if (NULL == _player || NULL == _card)
    {
        return ERROR_POINTER_NULL;
    }
    if (0 == _player -> m_numOfCards)
    {
        DoInsertion(_player, _card, 0);
        return ERROR_SUCCESS;
    }
    _index = SearchCorrectIndex(_player, _card);
    DoInsertion(_player, _card, _index);
    return ERROR_SUCCESS;
}

void* TakeCardFromPlayer(Player* _player)
{
    void* removedCard;
    if (NULL == _player)
    {
        return NULL;
    }
    VectorRemove(_player -> m_cards, &removedCard);
    _player -> m_numOfCards -= 1;
    return removedCard;
}

/******************** Assistance Functions ********************/

static int SearchCorrectIndex(Player* _player, Cards* _card)
{
    void* tempCard;
    int index;
    for (index = 0; index < (_player -> m_numOfCards); ++index)
    {
        VectorGet(_player -> m_cards,
            (_player -> m_numOfCards) - 1, &tempCard);
        if (IsSuitLower(_card, tempCard) == TRUE)
        {
            return index;
        }
        if (IsSameSuit(_card, tempCard) == TRUE &&
            IsRankLower(_card, tempCard) == TRUE)
        {
            return index;
        }
    }
    return index;
}
static ERRStat IsSuitLower(Cards* _card, Cards* _tempCard)
{
    return ((_card -> m_suit) < (_tempCard -> m_suit)) ? TRUE : FALSE;
}

static ERRStat IsSameSuit(Cards* _card, Cards* _tempCard)
{
    return ((_card -> m_suit) == (_tempCard -> m_suit)) ? TRUE : FALSE;
}

static ERRStat IsRankLower(Cards* _card, Cards* _tempCard)
{
    return ((_card -> m_rank) < (_tempCard -> m_rank)) ? TRUE : FALSE;
}

static ERRStat DoInsertion(Player* _player, Cards* _card,
    int _index)
{
    int j;
    void* tempCard;
    for (j = (_player -> m_numOfCards); j > _index; --j)
    {
        VectorGet(_player -> m_cards, j - 1, &tempCard);
        VectorSet(_player -> m_cards, j, tempCard);
    }
    VectorSet(_player -> m_cards, _index, _card);
    _player -> m_numOfCards += 1;
    ERROR_SUCCESS;
}
/*************** assistance functions for tests ***************/
void GetName(Player* _player, char* _item)
{
    strcpy(_item, _player -> m_name);
}

int GetNumOfCards(Player* _player)
{
    return _player -> m_numOfCards;
}


