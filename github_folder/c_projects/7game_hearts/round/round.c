#include <stdlib.h>                     /* for malloc */
#include <stdio.h>

#include "round.h"
#include "../../2genvector/vector.h"    /* for m_deck */
#include "../cards/cards.h"             /* for Cards object*/
#include "../deck/deck.h"
#include "../player/player.h"
#include "../errstat.h"                 /* for error statuses */

#define INITIAL_NUM_OF_CARDS (13)
#define NUM_OF_SUITS (4)
#define TRANSFER_NUM_OF_CARDS (3)

/***************** Assitance Inner Functions ******************/
static ERRStat HandoutCards(Player** _players, Round* _round);
static ERRStat StartRound(Round* _round, Player** _players);

static void TransferCards(Round* _round, TransferDirection _direction);
static void SortCards(Player** _players, int _roundNum, int _numPlayers);
static void SortBySuit(void** _hand, int _cardsInHand, int* _suitCount);
static void SortByRank(void** _hand, int _start, int _end);
static void CopyCardsPointers(void** _to, void** _from, int _start, int _end);
static void TakeThreeCards(Player* _player, void** _cards);
static void GiveThreeCards(Player* _player, void** _cards);
static void DestroyCard(void* _card);

static Card* SelectTwoOfClubs(Player* _player);

static int FindTwoClubs(Player** _players, int _numOfPlayers);


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
    if (ERROR_SUCCESS != StartRound(_round, _round -> m_players))
    {
        return ERROR_OUT_OF_MEMMORY;
    }
    /*
    StartRound(Round* _round, Player** _players)
    {
        int counter, i, playerGetsCards, points;
        Card** CardsOnTheTable[4];
        Card* cardRecieved;
        Suit leadingSuit;
        currentPlayer = FindPLayerOwnsTwoClubs(Player** _players)
        for (counter = 0; counter != INITIAL_NUM_OF_CARDS; ++counter)
        {
            for (i = 0; i != _round.m_numOfPlayers; ++i)
            {
                cardRecieved = Card* PlayHand(_players[currentPlayer]);
                if (0 == i)
                {
                    leadingSuit = cardRecieved.m_suit;
                }
                Card[currentPlayer] = cardRecieved;
                ++(currentPlayer);
                currentPlayer %= 4;
            }
            points = CalculatePenalties(CardsOnTheTable);
            cardRecieved = BiggestCard(CardsOnTheTable, leadingSuit);
            playerGetsCards = int FindPlayer(CardsOnTheTable, cardRecieved, numOfPlayers)
            {
                int indexOfPlayer;
                for (indexOfPlayer = 0; indexOfPlayer != numOfPlayers; ++i)
                {
                    if (CardsOnTheTable[indexOfPlayer].m_suit == cardRecieved.m_suit
                        && CardsOnTheTable[indexOfPlayer].m_rank == cardRecieved.m_rank)
                        {
                            break;
                        }
                }
                return indexOfPlayer;
            }
            _players[playerGetsCards].m_playersPoints += points;
        }
    }
    */
    return ERROR_SUCCESS;
}

/******************** Assistance Functions ********************/

static ERRStat StartRound(Round* _round, Player** _players)
{
    Suit leadingSuit = CLUBS;
    Card* selectedCard;
    int startingPlayer = 0;
    int numOfPlayers = _round -> m_numOfPlayers;
    Vector* cardsOnTable = VectorCreate(numOfPlayers, 0);
    {
        if (NULL == cardsOnTable)
        {
            return ERROR_ALLOCATION_FAILED;
        }
    }
    startingPlayer = FindTwoClubs(_players, numOfPlayers);
    selectedCard = SelectTwoOfClubs(_players[startingPlayer]);

    /* PrintCard(selectedCard); */
    VectorAppend(cardsOnTable, selectedCard);

    VectorDestroy(&cardsOnTable, DestroyCard);
    return ERROR_SUCCESS;
}

static int FindTwoClubs(Player** _players, int _numOfPlayers)
{
    int i, j;
    void* hand[13];
    for (i = 0; i != _numOfPlayers; ++i)
    {
        if (IsHavingTwoOfClubs(_players[i]))
        {
            /*
            printf("\nPlayer %d has Two of Clubs\n", i);
            TakeAllCardsFromPlayer(_players[i], hand, 13);
            for (j = 0; j != 13; ++j)
            {
                PrintCard((Card*) hand[j]);
                GiveCardToPlayer(_players[i], hand[j]);
            }
            putchar('\n');
            */
            return i;
        }
    }
    
    return _numOfPlayers;
}

static Card* SelectTwoOfClubs(Player* _player)
{
    int i, indexOfTwoClubs, readAssistance, writeHand, end;
    void* assistance[INITIAL_NUM_OF_CARDS];
    PlayerType type = GetPlayerType(_player);
    if (type == BOT)
    {
        indexOfTwoClubs = FindIndexOfTwoOfClubs(_player);
        for (i = INITIAL_NUM_OF_CARDS - 1; i >= indexOfTwoClubs; --i)
        {
            TakeCardFromPlayer(_player, &(assistance[i]));
        }
        readAssistance = INITIAL_NUM_OF_CARDS - 1;
        end = INITIAL_NUM_OF_CARDS - 1;
        for (writeHand = indexOfTwoClubs; writeHand != end; ++writeHand)
        {
            GiveCardToPlayer(_player, assistance[readAssistance]);
            --readAssistance;
        }
        return (Card*)assistance[indexOfTwoClubs];
    }
    else if (type == HUMAN)
    {
        printf("\n\n\n ERROR: HUMAN IS NOT DEALT WITH\n");
    }
}

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
    int i, startHearts, endHearts, startSpades, endSpades, startDiamonds, endDiamonds, startClubs, endClubs;
    int suitCount[NUM_OF_SUITS] = {0};
    void* hand[INITIAL_NUM_OF_CARDS];
    TakeAllCardsFromPlayer(_players[0], hand, cardsInHand);
    SortBySuit(hand, cardsInHand, suitCount);
    startHearts = 0;
    endHearts = suitCount[HEARTS];
    startSpades = endHearts;
    endSpades = startSpades + suitCount[SPADES];
    startDiamonds = endSpades;
    endDiamonds = startDiamonds + suitCount[DIAMONDS];
    startClubs = endDiamonds;
    endClubs = startClubs + suitCount[CLUBS];
    SortByRank(hand, startHearts, endHearts);
    SortByRank(hand, startSpades, endSpades);
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
    void* assistance[INITIAL_NUM_OF_CARDS];
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
    void* assistance[INITIAL_NUM_OF_CARDS];
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

static void TransferCards(Round* _round, TransferDirection _direction)
{
    int i, r;
    void* cardsFromFirstPlayer[TRANSFER_NUM_OF_CARDS];
    void* cardsFromSecondPlayer[TRANSFER_NUM_OF_CARDS];
    void* cardsFromThirdPlayer[TRANSFER_NUM_OF_CARDS];
    void* cardsFromFourthPlayer[TRANSFER_NUM_OF_CARDS];
    void* hand[INITIAL_NUM_OF_CARDS];
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
}

static void TakeThreeCards(Player* _player, void** _cards)
{
    int r, w;
    void* threeCards[TRANSFER_NUM_OF_CARDS];
    PlayerType type = GetPlayerType(_player);   /* if type is human then to add the UI interface */
    for (w = 0; w != TRANSFER_NUM_OF_CARDS; ++w)
    {
        TakeCardFromPlayer(_player, &(threeCards[w]));
    }
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
        case(SPADES): return "SPADES";
        case(DIAMONDS): return "DIAMONDS";
        case(CLUBS): return "CLUBS";
        default: return "ERROR: suit not valid";
    }    
}

static void TakeAllCardsFromPlayer(Player* _player, void** _hand, int _numOfCards)
{
    int i;
    void* assistance[INITIAL_NUM_OF_CARDS];
    for (i = 0; i != _numOfCards; ++i)
    {
        TakeCardFromPlayer(_player, &(assistance[i]));
    }
    CopyCardsPointers(_hand, assistance, 0, _numOfCards);
}

static void DestroyCard(void* _card)
{
    free( _card);
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
