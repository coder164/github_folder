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
#define TRANSFER_NUM_OF_CARDS (3)

/***************** Assitance Inner Functions ******************/
static ERRStat HandoutCards(Player** _players, Round* _round);
static ERRStat TransferCards(Round* _round, TransferDirection _direction);

static void SortCards(Player** _players, int _roundNum, int _numPlayers);
static void SortBySuit(void** _hand, int _cardsInHand, int* _suitCount);
static void SortByRank(void** _hand, int _start, int _end);
static void CopyCardsPointers(void** _to, void** _from, int _start, int _end);
static void TakeThreeCards(Player* _player, void** _cards);
static void GiveThreeCards(Player* _player, void** _cards);


/*** TO TRANFER INTO UI MODULE ***/
void PrintCard(const Card* const _card);
const char* TranslateRankToStr(Rank _rank);
const char* TranslateSuitToStr(Suit _suit);

static void TakeAllCardsFromPlayer(Player* _player, void** _hand, int _numOfCards);
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
    SortCards(_round -> m_players, _round -> m_roundNum, _round -> m_numOfPlayers);
    if (_direction != NO_TRANSFER)
    {
        TransferCards(_round, _direction);
    }
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

static void SortCards(Player** _players, int _roundNum, int _numPlayers)
{
    int cardsInHand = ((CARDS_FACTOR / _numPlayers) - _roundNum);
    int i, startHearts, endHearts, startLeef, endLeef, startDiamonds, endDiamonds, startClubs, endClubs;
    int suitCount[NUM_OF_SUITS] = {0};
    void* hand[SIZE_ASSISTANCE_CARDS_ARRAY];
    TakeAllCardsFromPlayer(_players[0], hand, cardsInHand);
    SortBySuit(hand, cardsInHand, suitCount);
    startHearts = 0;
    endHearts = suitCount[HEARTS];
    startLeef = endHearts;
    endLeef = startLeef + suitCount[LEEF];
    startDiamonds = endLeef;
    endDiamonds = startDiamonds + suitCount[DIAMOND];
    startClubs = endDiamonds;
    endClubs = startClubs + suitCount[CLUBS];
    SortByRank(hand, startHearts, endHearts);
    SortByRank(hand, startLeef, endLeef);
    SortByRank(hand, startDiamonds, endDiamonds);
    SortByRank(hand, startClubs, endClubs);
    for (i = 0; i != cardsInHand; ++i)
    {
        GiveCardToPlayer(_players[0], hand[i]);
    }
}

static void SortBySuit(void** _hand, int _cardsInHand, int* _suitCount)
{
    int i, r;
    int w = 0;
    Suit suit;
    void* assistance[SIZE_ASSISTANCE_CARDS_ARRAY];
    for (suit = HEARTS; suit != NUM_OF_SUITS; ++suit)
    {
        for (r = 0; r != _cardsInHand; ++r)
        {
            if ( ( (Card*)_hand[r]) -> m_suit == suit)
            {
                assistance[w] = _hand[r];
                ++_suitCount[suit];
                ++w;
            }
        }
    }
    CopyCardsPointers(_hand, assistance, 0, _cardsInHand);
}

static void SortByRank(void** _hand, int _start, int _end)
{
    void* assistance[SIZE_ASSISTANCE_CARDS_ARRAY];
    int r, w, min;
    for (w = _start; w < _end; ++w)
    {
        min = w;
        for (r = w + 1; r < _end; ++r)
        {
            if ( ( (Card*)_hand[r]) -> m_rank < ((Card*)_hand[min]) -> m_rank)
            {
                min = r;
            }
        }
        assistance[w] = _hand[min];
        _hand[min] = _hand[w];
    }
    CopyCardsPointers(_hand, assistance, _start, _end);
}

static void CopyCardsPointers(void** _to, void** _from, int _start, int _end)
{
    int i;
    for (i = _start; i != _end; ++i)
    {
        _to[i] = _from[i];
    }
}

static ERRStat TransferCards(Round* _round, TransferDirection _direction)
{
    int i, r;
    void* cardsFromFirstPlayer[TRANSFER_NUM_OF_CARDS];
    void* cardsFromSecondPlayer[TRANSFER_NUM_OF_CARDS];
    void* cardsFromThirdPlayer[TRANSFER_NUM_OF_CARDS];
    void* cardsFromFourthPlayer[TRANSFER_NUM_OF_CARDS];
    void* hand[SIZE_ASSISTANCE_CARDS_ARRAY];
    printf("\nTake three cards from each player");
    TakeThreeCards(_round -> m_players[0], cardsFromFirstPlayer);
    TakeThreeCards(_round -> m_players[1], cardsFromSecondPlayer);
    TakeThreeCards(_round -> m_players[2], cardsFromThirdPlayer);
    TakeThreeCards(_round -> m_players[3], cardsFromFourthPlayer);
    if (LEFT == _direction)
    {
        GiveThreeCards(_round -> m_players[0], cardsFromFourthPlayer);
        GiveThreeCards(_round -> m_players[1], cardsFromFirstPlayer);
        GiveThreeCards(_round -> m_players[2], cardsFromSecondPlayer);
        GiveThreeCards(_round -> m_players[3], cardsFromThirdPlayer);
    }
    else if (RIGHT == _direction)
    {
        GiveThreeCards(_round -> m_players[0], cardsFromSecondPlayer);
        GiveThreeCards(_round -> m_players[1], cardsFromThirdPlayer);
        GiveThreeCards(_round -> m_players[2], cardsFromFourthPlayer);
        GiveThreeCards(_round -> m_players[3], cardsFromFirstPlayer);
    }
    else if (OPPOSITE == _direction)
    {
        GiveThreeCards(_round -> m_players[0], cardsFromThirdPlayer);
        GiveThreeCards(_round -> m_players[1], cardsFromFourthPlayer);
        GiveThreeCards(_round -> m_players[2], cardsFromFirstPlayer);
        GiveThreeCards(_round -> m_players[3], cardsFromSecondPlayer);
    }
    printf("\nAfter transfer of three cards for player 0");
    TakeAllCardsFromPlayer(_round -> m_players[0], hand, SIZE_ASSISTANCE_CARDS_ARRAY);
    for (r = SIZE_ASSISTANCE_CARDS_ARRAY - 1; r != -1; --r)
    {
        PrintCard((Card*)hand[r]);
        GiveCardToPlayer(_round -> m_players[0], hand[r]);
    }
    putchar('\n');
}

static void TakeThreeCards(Player* _player, void** _cards)
{
    int r, w;
    void* threeCards[TRANSFER_NUM_OF_CARDS];
    PlayerType type = GetPlayerType(_player);
    for (w = 0; w != TRANSFER_NUM_OF_CARDS; ++w)
    {
        TakeCardFromPlayer(_player, &(threeCards[w]));
        PrintCard((Card*)threeCards[w]);
    }
    putchar('\n');
    CopyCardsPointers(_cards, threeCards, 0, TRANSFER_NUM_OF_CARDS);
}

static void GiveThreeCards(Player* _player, void** _cards)
{
    int i;
    for (i = 0; i != TRANSFER_NUM_OF_CARDS; ++i)
    {
        GiveCardToPlayer(_player, _cards[i]);
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

/* may be usefull for strategy for bot players */
static void TakeAllCardsFromPlayer(Player* _player, void** _hand, int _numOfCards)
{
    int i;
    void* assistance[SIZE_ASSISTANCE_CARDS_ARRAY];
    for (i = 0; i != _numOfCards; ++i)
    {
        TakeCardFromPlayer(_player, &(assistance[i]));
    }
    CopyCardsPointers(_hand, assistance, 0, _numOfCards);
}

/************** Assistance Functions for Tests ****************/

void DestroyAllPlayers(Round** _round)
{
    int i;
    for (i = 0; i < (*_round) -> m_numOfPlayers; ++i)
    {
        PlayerDestroy(&((*_round) -> m_players[i]));
    }
}
