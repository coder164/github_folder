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
#define POINTS_QUEEN_SPADES (13)

/***************** Assitance Inner Functions ******************/
static ERRStat HandoutCards(Player** _players, Round* _round);

static void GiveBackCards(Player* _player, void** _hand, int _startIndex, int _endIndex);
static void FirstStage(Round* _round, TransferDirection _direction);
static void TransferCards(Round* _round, TransferDirection _direction);
static void SortCards(Player** _players, int _roundNum, int _numPlayers);
static void SortBySuit(void** _hand, int _cardsInHand, int* _suitCount);
static void SortByRank(void** _hand, int _start, int _end);
static void CopyCardsPointers(void** _to, void** _from, int _start, int _end);
static void TakeThreeCards(Player* _player, void** _cards);
static void GiveThreeCards(Player* _player, void** _cards);
static void AddPoints(Round* _round, Vector* _cardsOnTable ,int _indexOfPlayer);
static void EmptyTheTable(Vector* _table);

static Card* SelectTwoOfClubs(Player* _player);
static Card* SelectCard(Player* _player, Suit _leadingSuit);
static Card* SelectFirstCard(Player* _player, ERRStat _canStartHearts);

static int SecondStage(Round* _round, Vector* _table, Player** _players);
static int ThirdStage(Round* _round, Player** _players, Vector* _table, int _startingPlayer);
static int FindTwoClubs(Player** _players, int _numOfPlayers);
static int WhoTakesTheCards(const Vector* const _cardsOnTable, int _startingPlayer);

/*** TO TRANFER INTO UI MODULE ***/
void PrintName(Player* _player);
void PrintAllCards(Player* _player, int _numOfCards);
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
    ERRStat resultStage;
    Vector* table;
    int nextStarting, i, remainingCards;
    if (NULL == _round)
    {
        return ERROR_POINTER_NULL;
    }
    table = VectorCreate(_round -> m_numOfPlayers, 0);
    {
        if (NULL == table)
        {
            return ERROR_ALLOCATION_FAILED;
        }
    }
    shuffledDeck = ShuffleCards((_round) -> m_deck);
    (_round) -> m_deck = shuffledDeck;
    if (ERROR_SUCCESS != HandoutCards(_round -> m_players, _round))
    {
        return ERROR_POINTER_NULL;
    }
    SortCards(_round -> m_players, _round -> m_roundNum, _round -> m_numOfPlayers);
    FirstStage(_round, _direction);

    putchar('\n');
    PrintName(_round -> m_players[0]);
    PrintAllCards(_round -> m_players[0], INITIAL_NUM_OF_CARDS);
    putchar('\n');
    PrintName(_round -> m_players[1]);
    PrintAllCards(_round -> m_players[1], INITIAL_NUM_OF_CARDS);
    putchar('\n');
    PrintName(_round -> m_players[2]);
    PrintAllCards(_round -> m_players[2], INITIAL_NUM_OF_CARDS);
    putchar('\n');
    PrintName(_round -> m_players[3]);
    PrintAllCards(_round -> m_players[3], INITIAL_NUM_OF_CARDS);

    nextStarting = SecondStage(_round, table, _round -> m_players);
	remainingCards = GetNumOfCards(_round -> m_players[nextStarting]);
    /*
    for (i = 0; i != remainingCards; ++i)
    {
        nextStarting = ThirdStage(_round, _round -> m_players, table, nextStarting);
    }
    */
    VectorDestroy(&table, NULL);
    return ERROR_SUCCESS;
}

/******************** Assistance Functions ********************/

static int ThirdStage(Round* _round, Player** _players, Vector* _table, int _startingPlayer)
{
    int i, remainingPlayers, currentPlayer, numOfPlayers, playerTakesCards;
    ERRStat haveOnlyHerts = MayStartWithHearts(_players[_startingPlayer]);
    Card* selectedCard;
    Suit leadingSuit;
    void* tempCard;     /* for printing */
    numOfPlayers = _round -> m_numOfPlayers;
    selectedCard = SelectFirstCard(_players[_startingPlayer], haveOnlyHerts);
    leadingSuit = selectedCard -> m_suit;
    VectorAppend(_table, selectedCard);
    remainingPlayers = numOfPlayers - 1;
    currentPlayer = _startingPlayer + 1;
    for (i = 0; i != remainingPlayers; ++i)
    {
        selectedCard = SelectCard(_players[currentPlayer % numOfPlayers], leadingSuit);
        VectorAppend(_table, selectedCard);
        ++currentPlayer;
    }
    
    for (i = _startingPlayer; i != _startingPlayer + numOfPlayers; ++i)
    {
        VectorGet(_table, i % numOfPlayers, &tempCard);
        putchar('\n');
        PrintName(_players[i % numOfPlayers]);
        printf(" puts: ");
        PrintCard((Card*)tempCard);
    }

    playerTakesCards = WhoTakesTheCards(_table, _startingPlayer);
    printf("\nplayer takes cards = %d\n", playerTakesCards);

    AddPoints(_round, _table, playerTakesCards);
    EmptyTheTable(_table);
    return playerTakesCards;
}

static int SecondStage(Round* _round, Vector* _table, Player** _players)
{
    Suit leadingSuit = CLUBS;
    Card* selectedCard;
    void* tempCard;     /* for printing */
    int i, currentPlayer, remainingPlayers, playerTakesCards;
    int startingPlayer = 0;
    int numOfPlayers = _round -> m_numOfPlayers;
    startingPlayer = FindTwoClubs(_players, numOfPlayers);
    selectedCard = SelectTwoOfClubs(_players[startingPlayer]);
    VectorAppend(_table, selectedCard);
    remainingPlayers = numOfPlayers - 1;
    currentPlayer = startingPlayer + 1;
    for (i = 0; i != remainingPlayers; ++i)
    {
        selectedCard = SelectCard(_players[currentPlayer %numOfPlayers], leadingSuit);
        VectorAppend(_table, selectedCard);
        ++currentPlayer;
    }

    putchar('\n');
    for (i = 0; i != numOfPlayers; ++i)
    {
        VectorGet(_table, i, &tempCard);
        printf("\nPlayer: ");
        PrintName(_players[_table, (startingPlayer + i) % numOfPlayers]);
        PrintCard((Card*)tempCard);
    }
    putchar('\n');

    playerTakesCards = WhoTakesTheCards(_table, startingPlayer);
    AddPoints(_round, _table, playerTakesCards);

    printf("player takes cards: ");
    PrintName(_players[playerTakesCards]);
    putchar('\n');

	EmptyTheTable(_table);
    return playerTakesCards;
}

static int WhoTakesTheCards(const Vector* const _cardsOnTable, int _startingPlayer)
{
    void* data;
    Suit leadingSuit;
    Rank highestRank;
    int whoTakes, i, numOfPlayers, current;
    whoTakes = _startingPlayer;
    VectorGet(_cardsOnTable, 0, &data);
    leadingSuit = ((Card*)data) -> m_suit;
    highestRank = ((Card*)data) -> m_rank;
	numOfPlayers = VectorSize(_cardsOnTable);
    for (i = 0; i < numOfPlayers; ++i)
    {
        VectorGet(_cardsOnTable, i, &data);
        if ( ((Card*)data) -> m_suit == leadingSuit
            && ((Card*)data) -> m_rank > highestRank)
        {
            highestRank = ((Card*)data) -> m_rank;
            whoTakes = (i + _startingPlayer) % numOfPlayers;
        }
    }
    return whoTakes;
}

static int FindTwoClubs(Player** _players, int _numOfPlayers)
{
    int i;
    for (i = 0; i != _numOfPlayers; ++i)
    {
        if (IsHavingTwoOfClubs(_players[i]))
        {
            return i;
        }
    }
    return _numOfPlayers;
}

static Card* SelectFirstCard(Player* _player, ERRStat _canStartHearts)
{
    int i, numOfCards, indexSelected;
    void* hand[INITIAL_NUM_OF_CARDS];
    if (BOT == GetPlayerType(_player))
    {
        numOfCards = GetNumOfCards(_player);
        TakeAllCardsFromPlayer(_player, hand, numOfCards);
        indexSelected = 0;
        if (FALSE == _canStartHearts && HEARTS == ((Card*)hand[indexSelected]) -> m_suit)
        {
            while ( ((Card*)hand[indexSelected]) -> m_suit == HEARTS)
            {
                ++indexSelected;
            }
        }
        GiveBackCards(_player, hand, 0, indexSelected);
        GiveBackCards(_player, hand, indexSelected + 1, numOfCards);
        return (Card*)hand[indexSelected];
    }
    else if (HUMAN == GetPlayerType(_player))
    {
        printf("\n\n\n ERROR: HUMAN IS NOT DEALT WITH\n");
    }
}

static Card* SelectCard(Player* _player, Suit _leadingSuit)
{
    int i, numOfCards, indexOfHighestRank;
    Rank highest;
    void* hand[INITIAL_NUM_OF_CARDS];
    if (BOT == GetPlayerType(_player))
    {
        numOfCards = GetNumOfCards(_player);
        TakeAllCardsFromPlayer(_player, hand, numOfCards);
        indexOfHighestRank = 0;
        highest = ((Card*)hand[0]) -> m_rank;
        for (i = 0; i < numOfCards; ++i)
        {
            if ( ((Card*)hand[i]) -> m_suit == _leadingSuit)
            {
                indexOfHighestRank = i;
                highest = ((Card*)hand[i]) -> m_rank;
                break;
            }
        }
        if ( ( ((Card*)hand[indexOfHighestRank]) -> m_suit == _leadingSuit) && (indexOfHighestRank != numOfCards - 1) )
        {
            for (i = indexOfHighestRank + 1; i < numOfCards; ++i)
            {
                if ( ((Card*)hand[i]) -> m_rank > highest && ((Card*)hand[i]) -> m_suit == _leadingSuit)
                {
                    highest = ((Card*)hand[i]) -> m_rank;
                    indexOfHighestRank = i;
                }
            }
        }
        GiveBackCards(_player, hand, 0, indexOfHighestRank);
        GiveBackCards(_player, hand, indexOfHighestRank + 1, numOfCards);
        return (Card*)hand[indexOfHighestRank];
    }
    else if (HUMAN == GetPlayerType(_player))
    {
        printf("\n\n\n ERROR: HUMAN IS NOT DEALT WITH\n");
    }
}

static Card* SelectTwoOfClubs(Player* _player)
{
    int indexOfTwoClubs;
    void* hand[INITIAL_NUM_OF_CARDS];
    PlayerType type = GetPlayerType(_player);
    if (type == BOT)
    {
        indexOfTwoClubs = FindIndexOfTwoOfClubs(_player);
        TakeAllCardsFromPlayer(_player, hand, INITIAL_NUM_OF_CARDS);
        GiveBackCards(_player, hand, 0, indexOfTwoClubs);
        GiveBackCards(_player, hand, indexOfTwoClubs + 1, INITIAL_NUM_OF_CARDS);
        return (Card*)hand[indexOfTwoClubs];
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

static void GiveBackCards(Player* _player, void** _hand, int _startIndex, int _endIndex)
{
    int i;
    for (i = _startIndex; i < _endIndex; ++i)
    {
        GiveCardToPlayer(_player, _hand[i]);
    }
}

static void AddPoints(Round* _round, Vector* _cardsOnTable ,int _indexOfPlayer)
{
    int i, accumulated;
    void* currentData;
    Card currentCard;
    accumulated = 0;
    for (i = 0; i != VectorSize(_cardsOnTable); ++i)
    {
        VectorGet(_cardsOnTable, i, &currentData);
        currentCard = *(Card*)currentData;
        if (QUEEN == currentCard.m_rank && SPADES == currentCard.m_suit)
        {
            accumulated += POINTS_QUEEN_SPADES;
        }
        else if (HEARTS == currentCard.m_suit)
        {
            ++accumulated;
        }
    }
    _round -> m_playersPoints[_indexOfPlayer] += accumulated;
}

static void SortCards(Player** _players, int _roundNum, int _numPlayers)
{
    int cardsInHand = ((CARDS_FACTOR / _numPlayers) - _roundNum);
    int i, startHearts, endHearts, startSpades, endSpades, startDiamonds, endDiamonds, startClubs, endClubs, current;
    int suitCount[NUM_OF_SUITS] = {0};
    void* hand[INITIAL_NUM_OF_CARDS];
    for (current = 0; current != _numPlayers; ++current)
    {
        TakeAllCardsFromPlayer(_players[current], hand, cardsInHand);
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
            GiveCardToPlayer(_players[current], hand[i]);
        }
        for (i = 0; i != NUM_OF_SUITS; ++i)
        {
            suitCount[i] = 0;
        }
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

static void FirstStage(Round* _round, TransferDirection _direction)
{
    if (NO_TRANSFER == _direction)
    {
        return;
    }
    else
    {
        TransferCards(_round, _direction);
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

static void TakeAllCardsFromPlayer(Player* _player, void** _hand, int _numOfCards)
{
    int i;
    for (i = _numOfCards - 1; i > -1 ; --i)
    {
        TakeCardFromPlayer(_player, &(_hand[i]));
    }
}

void PrintName(Player* _player)
{
	char name[30];
	GetName(_player, name);
	GetName(_player, name);
	printf("%s", name);
}

void PrintAllCards(Player* _player, int _numOfCards)
{
	int i;
	void* hand[INITIAL_NUM_OF_CARDS];
	for (i = _numOfCards - 1; i > -1; --i)
	{
		TakeCardFromPlayer(_player, &(hand[i]));
	}
	for (i = 0; i < _numOfCards; ++i)
	{
		PrintCard((Card*)hand[i]);
		GiveCardToPlayer(_player, hand[i]);
	}
    putchar('\n');
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

static void EmptyTheTable(Vector* _table)
{
	int i, size;
	void* item;
	size = VectorSize(_table);
	for (i = 0; i != size; ++i)
	{
		VectorRemove(_table, &item);
		free(item);
	}
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
