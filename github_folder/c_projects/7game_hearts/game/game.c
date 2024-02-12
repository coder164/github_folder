#include <stdlib.h>         /* for malloc() and for NULL*/
#include <stdbool.h>

#include "game.h"
#include "../round/round.h"
#include "../player/player.h"
#include "../errstat.h"     /* for error statuses */
#include <stdio.h>          /* for printing at developement */

struct Game {
    Player** m_players;     /* array of Players*/
    int* m_scores;
    int m_numOfPlayers;
    int m_roundNum;
};

/**************************************************************/
/* inner function declare */
static ERRStat CheckParamCreate(char* _playerNames[],
    int _numOfPlayers,PlayerType _type);
static Game* AllocateNewGame(int _numOfPlayers);
static ERRStat CreatePlayers(Game* _newGame, char* _playerNames[],
    int _numOfPlayers, PlayerType _type);
static void FreeMembers(Game* _game, int _lastIndex);
ERRStat ExecuteRounds(Game* _game, Round* _round);
static TransferDirection ChangeDirection(TransferDirection _lastDirection);
/**************************************************************/
Game* GameCreate(char* _playerNames[], int _numOfPlayers,
    PlayerType _type)
{
    Game* newGame;
    int* scores;
    ERRStat validParam;
    validParam = CheckParamCreate(_playerNames, _numOfPlayers, _type);
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
    newGame -> m_scores = scores;
    newGame -> m_numOfPlayers = _numOfPlayers;
    newGame -> m_roundNum = 0;
    /*
    resInnerFunc = CreatePlayers(newGame, _playerNames, _numOfPlayers, _type);
    if (resInnerFunc != ERROR_SUCCESS) 
    {
        return NULL;
    }
    */
    return newGame;
}
/**************************************************************/
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
    /*
    FreeMembers(*_game, ((*_game) -> m_numOfPlayers) - 1);
    */
    free((*_game) -> m_scores);
    free(*_game);
    *_game = NULL;
}
/**************************************************************/
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
    /* RunRound() is not working yet
    resultRunRound = RunRound(newRound, direction);
    if (resultRunRound != ERROR_SUCCESS)
    {
        return resultRunRound;
    }
    ExecuteRounds(_game, newRound);
    */
    /* to continue here Check for losers */
    RoundDestroy(&newRound);
    return ERROR_SUCCESS;
}

/******************** Assistance Functions ********************/

ERRStat ExecuteRounds(Game* _game, Round* _round)
{
    int ToConntinue = TRUE;
    TransferDirection direction = OPPOSITE;
    while (ToConntinue)
    {
        direction = ChangeDirection(direction);
        RunRound(_round, direction);
        /* to continue here for points update */
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

static ERRStat CheckParamCreate(char* _playerNames[],
    int _numOfPlayers,PlayerType _type) 
{
    int i, size = 0;
    if (NULL == _playerNames) 
    {
        return ERROR_POINTER_NULL;
    }
    if (_numOfPlayers < 1) 
    {
        return ERROR_NUM_PLAYERS;
    }
    if (_type != BOT && _type != HUMAN) 
    {
        return ERROR_TYPE;
    }
    return ERROR_SUCCESS;
}

/**************************************************************/

static ERRStat CreatePlayers(Game* _newGame, char* _playerNames[],
    int _numOfPlayers, PlayerType _type)
{
    int i;
    Player* resPlayerCreate;
     _newGame -> m_players = (Player**)malloc(_numOfPlayers * sizeof(Player*));
    if (NULL == _newGame -> m_players) 
    {
        return ERROR_ALLOCATION_FAILED;
    }
    for (i = 0; i < _numOfPlayers; ++i) 
    {
        resPlayerCreate = PlayerCreate(_playerNames[i], _type);
        if (NULL == resPlayerCreate)
        {
            FreeMembers(_newGame, i);
            return ERROR_ALLOCATION_FAILED;
        }
        _newGame -> m_players[i] = resPlayerCreate;
    }
    _newGame -> m_numOfPlayers = _numOfPlayers;
    return ERROR_SUCCESS;
}

/**************************************************************/
static void FreeMembers(Game* _game, int _lastIndex) 
{
    while (_lastIndex >= 0) 
    {
        free(_game -> m_players[_lastIndex]);
        --_lastIndex;
    }
    free(_game -> m_players);
}
