#include <stdlib.h>                     /* for malloc() and for NULL*/
#include <stdbool.h>

#include "game.h"
#include "../round/round.h"
#include "../../2genvector/vector.h"    /* for m_players */
#include "../player/player.h"
#include "../errstat.h"                 /* for error statuses */
#include <stdio.h>                      /* for printing at developement */

/***************** Assitance Inner Functions ******************/
static Vector* CreatePlayers(char* _playerNames[], PlayerType _types[],
    int _numOfPlayers);

static ERRStat CheckParamCreate(char* _playerNames[], PlayerType _types[],
    int _numOfPlayers);

static ERRStat ExecuteRounds(Game* _game, Round* _round);

static void FreeMembers(Vector* _players, int _numOfPlayers);

static TransferDirection ChangeDirection(TransferDirection _lastDirection);

/**************************************************************/

struct Game {
    Vector* m_players;
    int* m_scores;
    int m_numOfPlayers;
    int m_roundNum;
};

/**************************************************************/
Game* GameCreate(char* _playerNames[], PlayerType _types[],
    int _numOfPlayers)
{
    Game* newGame;
    int* scores;
    ERRStat validParam;
    Vector* players;
    validParam = CheckParamCreate(_playerNames, _types, _numOfPlayers);
    if (validParam != ERROR_SUCCESS) 
    {
        return NULL;
    }
    newGame = (Game*)malloc(sizeof(Game));
    if (NULL == newGame) 
    {
        return NULL;
    }
    scores = (int*)calloc(_numOfPlayers, sizeof(int));
    if (NULL == scores) 
    {
        free(newGame);
        return NULL;
    }
    players = CreatePlayers(_playerNames, _types, _numOfPlayers);
    if (NULL == players) 
    {
        free(scores);
        free(newGame);
        return NULL;
    }
    newGame -> m_players = players;
    newGame -> m_scores = scores;
    newGame -> m_numOfPlayers = _numOfPlayers;
    newGame -> m_roundNum = 0;
    return newGame;
}

void GameDestroy(Game** _game)
{
    if (NULL == _game || NULL == *_game)
    {
        return;
    }
    if (((*_game) -> m_numOfPlayers) < 1)
    {
        return;
    }
    FreeMembers((*_game) -> m_players, (*_game) -> m_numOfPlayers);
    VectorDestroy(&((*_game) -> m_players), NULL);
    free((*_game) -> m_scores);
    free(*_game);
    *_game = NULL;
}

/*
ERRStat GameRun(Game* _game)
{
    Round* newRound = NULL;
    ERRStat resultRunRound;
    TransferDirection direction = LEFT;
    if (NULL == _game)
    {
        return ERROR_POINTER_NULL;
    }
    newRound = RoundCreate(_game -> m_players, _game -> m_numOfPlayers, 0);
    if (NULL == newRound)
    {
        return ERROR_GENERAL;
    }
        RunRound() is not working yet
        resultRunRound = RunRound(newRound, direction);
        if (resultRunRound != ERROR_SUCCESS)
        {
            return resultRunRound;
        }
        ExecuteRounds(_game, newRound);
        to continue here Check for losers
    RoundDestroy(&newRound);
    return ERROR_SUCCESS;
}
*/
/******************** Assistance Functions ********************/

static Vector* CreatePlayers(char* _playerNames[], PlayerType _types[],
    int _numOfPlayers)
{
    int i;
    Player* current;
    Vector* players = VectorCreate(_numOfPlayers, 0);
    if (NULL == players)
    {
        return NULL;
    }
    for (i = 0; i != _numOfPlayers; ++i)
    {
        current = PlayerCreate(_playerNames[i], _types[i]);
        if (NULL == current)
        {
            FreeMembers(players, _numOfPlayers);
            return NULL;
        }
        VectorAppend(players, current);
    }
    return players;
}

static ERRStat CheckParamCreate(char* _playerNames[], PlayerType _types[],
    int _numOfPlayers) 
{
    int i;
    if (NULL == _playerNames) 
    {
        return ERROR_POINTER_NULL;
    }
    if (_numOfPlayers < 1) 
    {
        return ERROR_NUM_PLAYERS;
    }
    for (i = 0; i != _numOfPlayers; ++i)
    {
        if (_types[i] != BOT && _types[i] != HUMAN)
        {
            return ERROR_TYPE;
        }
    }
    return ERROR_SUCCESS;
}

static void FreeMembers(Vector* _players, int _numOfPlayers) 
{
    int i;
    void* currentPlayer;
    Player* current;
    for (i = 0; i < _numOfPlayers; ++i)
    {
        VectorGet(_players, i, &currentPlayer);
        current = (Player*)currentPlayer;
        PlayerDestroy(&current);
    }
}

/*
static ERRStat ExecuteRounds(Game* _game, Round* _round)
{
    int ToConntinue = TRUE;
    TransferDirection direction = OPPOSITE;
    while (ToConntinue)
    {
        direction = ChangeDirection(direction);
        RunRound(_round, direction);
        to continue here for points update
        RoundDestroy(&_round);
        ToConntinue = FALSE;
    }
    return ERROR_SUCCESS;
}

static TransferDirection ChangeDirection(TransferDirection _lastDirection)
{
    if (LEFT == _lastDirection)
    {
        return RIGHT;
    }
    if (RIGHT == _lastDirection)
    {
        return OPPOSITE;
    }
    if (OPPOSITE == _lastDirection)
    {
        return NO_TRANSFER;
    }
}
*/
