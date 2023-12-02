#include <stdlib.h>                     /* for malloc */
#include <stdio.h>

#include "round.h"
#include "../../2genvector/vector.h"    /* for m_deck */
#include "../cards/cards.h"             /* for Cards object*/
#include "../deck/deck.h"
#include "../player/player.h"
#include "../errstat.h"                 /* for error statuses */

#define SIZE_ASSISTANCE_CARDS_ARRAY (13)
#define NUM_OF_SUITS (4)

/***************** Assitance Inner Functions ******************/
static ERRStat HandoutCards(Player** _players, Round* _round);
static ERRStat SortCards(Player** _players, int _roundNum, int _numPlayers);
static ERRStat TransferCards(Round* _round, TransferDirection _direction);

static void SortByRank(void** _hand, int _cardsInHand);

/*** TO TRANFER INTO UI MODULE ***/
void AskPlayerToSelectThreeCards(Player* _player, Card* _cards);
void PrintCard(const Card* const _card);
const char* TranslateRankToStr(Rank _rank);
const char* TranslateSuitToStr(Suit _suit);

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
    int m_roundNum;
};

/**************************************************************/
Round* RoundCreate(Player** _players, int _numOfPlayers, int _roundNum)
{
    Round* newRound;
    Deck* newDeck;
    int* playersPoints;
    int i;
    if (_numOfPlayers < 1 || _numOfPlayers > 4 || NULL == _players ||
        NULL == *_players || _roundNum < 0)
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
    newRound -> m_roundNum = _roundNum;
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
    if (ERROR_SUCCESS != HandoutCards(_round -> m_players, _round))
    {
        return ERROR_POINTER_NULL;
    }
    if (ERROR_SUCCESS != SortCards(_round -> m_players,
        _round -> m_roundNum, _round -> m_numOfPlayers))
        {
            return ERROR_ALLOCATION_FAILED;
        }
    /*
    if (_direction != NO_TRANSFER)
    {
        TransferCards(_round, _direction);
    }
    */
    /* to continue here complete round */
    return ERROR_SUCCESS;
}
/******************** Assistance Functions ********************/

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

static ERRStat SortCards(Player** _players, int _roundNum, int _numPlayers)
{
    int cardsInHand = (CARDS_FACTOR / _numPlayers) - _roundNum;
    int i, r,  minRankInd;
    int w = 0;
    Suit suit;
    Rank minRank;
    int suitCount[NUM_OF_SUITS] = {0};
    void* hand[SIZE_ASSISTANCE_CARDS_ARRAY];
    for (i = 0; i != cardsInHand; ++i)  /* take all cards from the player into 'hand' */
    {
        TakeCardFromPlayer(_players[0], &(hand[i]));
        PrintCard((Card*)hand[i]);
    }
    SortByRank(hand, cardsInHand);

    printf("\n\nAFTER SUITE SORT\n");
    for (i = 0; i != cardsInHand; ++i)  /* give back to the player all his cards */
    {
        PrintCard((Card*)hand[i]);
        GiveCardToPlayer(_players[0], hand[i]);
    }

    for (i = 0; i != cardsInHand; ++i)  /* take all cards from the player into 'hand' */
    {
        TakeCardFromPlayer(_players[0], &(hand[i]));
    }

    minRank = ( (Card*)hand[0]) -> m_rank;
    printf("\n\n\n");
    PrintCard((Card*)hand[0]);

    /*
    minRankInd = 0;
    w = 0;
    for (r = 1; r != cardsInHand; ++r)
    {
        for (i = 0; i != suitCount[HEARTS]; ++i)
        {
            if ( TWO == ((Card*)assitance[i]) -> m_rank)
            {
                minRankInd = r;
                break;
            }
            else if ( ( ( (Card*)assitance[i]) -> m_rank < minRank))
            {
                minRank = ( (Card*)assitance[i]) -> m_rank;
            }
        }
        hand[w] = assitance[minRankInd];
    }

    printf("\n\nAFTER RANK SORT\n");
    for (i = 0; i != cardsInHand; ++i)
    {
        PrintCard((Card*)hand[i]);
        GiveCardToPlayer(_players[0], tempCards[i]);
    }
    */
    putchar('\n');
    return ERROR_SUCCESS;
}

static void SortByRank(void** _hand, int _cardsInHand)
{
    int i, r;
    int w = 0;
    Suit suit;
    int suitCount[NUM_OF_SUITS] = {0};
    void* assitance[SIZE_ASSISTANCE_CARDS_ARRAY];
    for (suit = HEARTS; suit != NUM_OF_SUITS; ++suit)   /* sort by suit */
    {
        for (r = 0; r != _cardsInHand; ++r)
        {
            if ( ( (Card*)_hand[r]) -> m_suit == suit)
            {
                assitance[w] = _hand[r];
                ++suitCount[suit];
                ++w;
            }
        }
    }
    for (i = 0; i != _cardsInHand; ++i)
    {
        _hand[i] = assitance[i];
    }
}

static ERRStat TransferCards(Round* _round, TransferDirection _direction)
{
    int i;
    Card cards[SIZE_ASSISTANCE_CARDS_ARRAY];
    for (i = 0; i < (_round -> m_numOfPlayers); ++i)
    {
        AskPlayerToSelectThreeCards(_round -> m_players[i], cards);
    }
}

/*** TO TRANFER INTO UI MODULE ***/
void AskPlayerToSelectThreeCards(Player* _player, Card* _cards)
{
    int i;
    for (i = 0; i != 3; ++i)
    {
        printf("need to be completed\n");
    }
}

void PrintCard(const Card* const _card)
{
    if (NULL == _card)
    {
        printf("ERROR: at PrintCard() _card is NULL!!!\n");
        return;
    }
    putchar('\n');
    printf("%s of %s", TranslateRankToStr(_card -> m_rank),
        TranslateSuitToStr(_card -> m_suit));
}

const char* TranslateRankToStr(Rank _rank)
{
    switch(_rank)
    {
        case(TWO): return "TWO";
        case(THREE): return "THREE";
        case(FOUR): return "FOUR";
        case(FIVE): return "FIVE";
        case(SIX): return "SIX";
        case(SEVEN): return "SEVEN";
        case(EIGHT): return "EIGHT";
        case(NINE): return "NINE";
        case(TEN): return "TEN";
        case(JACK): return "JACK";
        case(QUEEN): return "QUEEN";
        case(KING): return "KING";
        case(ACE): return "ACE";
        default: return "ERROR: rank not valid";
    }    
}

const char* TranslateSuitToStr(Suit _suit)
{
    switch(_suit)
    {
        case(HEARTS): return "HEARTS";
        case(LEEF): return "LEEF";
        case(DIAMOND): return "DIAMOND";
        case(CLUBS): return "CLUBS";
        default: return "ERROR: suit not valid";
    }    
}

/* not working
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
