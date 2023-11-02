#include <stdlib.h>                     /* for malloc */
#include <stdio.h>

#include "round.h"
#include "../../2genvector/vector.h"    /* for m_deck */
#include "../cards/cards.h"             /* for Cards object*/
#include "../deck/deck.h"
#include "../player/player.h"
#include "../errstat.h"                 /* for error statuses */

/***************** Assitance Inner Functions ******************/
static ERRStat HandoutCards(Player** _players, Round* _round);
static ERRStat TakeoutCards(Player** _players, Round* _round);

ERRStat ChangeThreeCards(Round* _round, TransferDirection _direction);
static ERRStat TakeThreeCardsFromPlayer(Player* _player, Card* _arrCards);
static ERRStat GiveThreeCardsToPlayer(Player* _player, Card* _arrCards);
ERRStat GiveCardsFromLeft(Round* _round, Card* _arrCards);
static ERRStat CreateSingleCard(void** _card); /* for _arrCards */
void DestroyAllPlayers(Round** _round);
/**************************************************************/

struct Round {
    Player** m_players; /* array of Players*/
    Deck* m_deck;       /* pointer to the Deck */
    int* m_playersPoints;
    int m_numOfPlayers;
};

/**************************************************************/
Round* RoundCreate(Player** _players, int _numOfPlayers)
{
    Round* newRound;
    Deck* newDeck;
    int* playersPoints;
    int i;
    if (_numOfPlayers < 1 || _numOfPlayers > 4 || NULL == _players ||
        NULL == *_players)
    {
        return NULL;
    }
    newRound = (Round*)malloc(sizeof(Round));
    if (NULL == newRound) 
    {
        return NULL;
    }
    newDeck = DeckCreate();
    if (NULL == newDeck)
    {
        free(newRound);
        return NULL;
    }
    playersPoints = (int*)calloc(_numOfPlayers, sizeof(int));
    if (NULL == playersPoints)
    {
        free(newRound);
        free(newDeck);
        return NULL;
    }
    newRound -> m_players = _players;
    newRound -> m_deck = newDeck;
    newRound -> m_playersPoints = playersPoints;
    newRound -> m_numOfPlayers = _numOfPlayers;
    return newRound;
}
/**************************************************************/
void RoundDestroy(Round** _round)
{
    if (NULL == _round || NULL == *_round)
    {
        return;
    }
    free((*_round) -> m_playersPoints);
    DeckDestroy(&(*_round) -> m_deck);
    DestroyAllPlayers(_round);
    free(*_round);
    *_round = NULL;
}
/**************************************************************/

ERRStat RunRound(Round* _round, TransferDirection _direction)
{
    Deck* shuffledDeck;
    if (NULL == _round)
    {
        return ERROR_POINTER_NULL;
    }
    shuffledDeck = ShuffleCards((_round) -> m_deck);
    (_round) -> m_deck = shuffledDeck;
    if (HandoutCards(_round -> m_players, _round) != ERROR_SUCCESS)
    {
        return ERROR_POINTER_NULL;
    }
    /*
    else if (TakeoutCards(_round -> m_players, _round) != ERROR_SUCCESS)
    {
        return ERROR_POINTER_NULL;
    }
    ChangeThreeCards(_round, _direction);
    */
    /* to continue here complete round */
    return ERROR_SUCCESS;
}
/******************** Assistance Functions ********************/
/* not working
ERRStat ChangeThreeCards(Round* _round, TransferDirection _direction)
{
    int i, j;
    void* card;
    ERRStat resStatus = CreateSingleCard(&card);
    Cards arrCards[12] = {(Cards)card};
    if (resStatus != ERROR_SUCCESS)
    {
        return resStatus;
    }
    TakeThreeCardsFromPlayer(_round -> m_players[i], arrCards);
    for (i = 0; i < (_round -> m_numOfPlayers); ++i)
    {
        j = i * 3;
        resStatus = TakeThreeCardsFromPlayer(_round -> m_players[i],
            arrCards[j]);
        if (resStatus != ERROR_SUCCESS);
        {
            return resStatus;
        }
    }
    if (_direction == PLAYER_FROM_LEFT)
    {
        resStatus = GiveCardsFromLeft(_round, arrCards);
        if (resStatus != ERROR_SUCCESS);
        {
            return resStatus;
        }
    }
}

static ERRStat TakeThreeCardsFromPlayer(Player* _player, Cards* _arrCards)
{
    int j;
    for (j = 0; j < 3; ++j)
    {
        _arrCards[j] = TakeCardFromPlayer(_player);
        if (_arrCards[j] == NULL)
        {
            return ERROR_POINTER_NULL;
        }
    }
    return ERROR_SUCCESS;
}

ERRStat GiveCardsFromLeft(Round* _round, Cards* _arrCards)
{
    int i, j;
    ERRStat resTranfer;
    for (i = (_round -> m_numOfPlayers); i >  2; --i)
    {
        j = i * 3 - 6;
        resTranfer = GiveThreeCardsToPlayer(_round -> m_players[i],
            _arrCards[j]);
        if (resTranfer != ERROR_SUCCESS);
        {
            return resTranfer;
        }
    }
    GiveThreeCardsToPlayer(_round -> m_players[0], _arrCards[9]);
    return ERROR_SUCCESS;
}

static ERRStat GiveThreeCardsToPlayer(Player* _player, Cards* _arrCards)
{
    int j;
    ERRStat resGiveCard;
    for (j = 0; j < 3; ++j)
    {
        resGiveCard = GiveCardToPlayer(_player, _arrCards[j]);
        if (resGiveCard != ERROR_SUCCESS);
        {
            return resGiveCard;
        }
    }
    return ERROR_SUCCESS;
}
*/
static ERRStat HandoutCards(Player** _players, Round* _round)
{
    int i, j;
    void* card = NULL;
    for (i = 0; i < (CARDS_FACTOR / NUM_OF_PLAYERS); ++i)
    {
        for (j = 0; j < NUM_OF_PLAYERS; ++j)
        {
            card = TakeCardFromDeck(_round -> m_deck);
            if (NULL == card)
            {
                return ERROR_POINTER_NULL;
            }
            else
            {
                GiveCardToPlayer(_players[j], card);
            }
        }
    }
    return ERROR_SUCCESS;
}

static ERRStat TakeoutCards(Player** _players, Round* _round)
{
    int i, j;
    Card* card;
    for (i = 0; i < (CARDS_FACTOR / NUM_OF_PLAYERS); ++i)
    {
        for (j = 0; j < NUM_OF_PLAYERS; ++j)
        {
            TakeCardFromPlayer(_players[j], card);
            if (NULL == card)
            {
                return ERROR_POINTER_NULL;
            }
            free(card);
        }
    }
    return ERROR_SUCCESS;
}

/************** Assistance Functions for Tests ****************/
/*
static ERRStat CreateSingleCard(void** _card)
{
    Cards newCard = (Cards*)malloc(sizeof(Cards))
    if (NULL == newCard)
    {
        return ERROR_ALLOCATION_FAILED;
    }
    *_card = newCard;
    return ERROR_SUCCESS;
}
*/

void DestroyAllPlayers(Round** _round)
{
    int i;
    for (i = 0; i < (*_round) -> m_numOfPlayers; ++i)
    {
        PlayerDestroy(&((*_round) -> m_players[i]));
    }
}
