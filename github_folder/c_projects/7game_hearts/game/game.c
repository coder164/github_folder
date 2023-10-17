#include <stdlib.h>         /* for malloc() and for NULL*/
#include <stdbool.h>
#include "game.h"
#include "../errstat.h"     /* for error statuses */
#include "../round/round.h"
#include "../player/player.h"

struct Game {
    Player** m_players;     /* array of Players*/
    int* m_roundScores;
    int m_numOfPlayers;
    int m_roundNum;
};

/**************************************************************/
/* inner function declare */
static ERRStat CheckParamCreate(char* _playerNames[],
    int _numOfPlayers,PlayerType _type);
static Game* AllocateNewGame(char* _playerNames[], int _numOfPlayers);
static ERRStat CreatePlayers(Game* _newGame, char* _playerNames[],
    int _numOfPlayers, PlayerType _type);
static void FreeMembers(Game* _game, int _index);
ERRStat ExecuteRounds(Game* _game, Round* _round);
static TransferDirection ChangeDirection(TransferDirection _lastDirection);
/**************************************************************/
Game* GameCreate(char* _playerNames[], int _numOfPlayers,
    PlayerType _type)
{
    Game* newGame;
    ERRStat resInnerFunc;
    resInnerFunc = CheckParamCreate(_playerNames, _numOfPlayers, _type);
    if (resInnerFunc != ERROR_SUCCESS) 
    {
        return NULL;
    }
    newGame = AllocateNewGame(_playerNames, _numOfPlayers);
    if (NULL == newGame) 
    {
        free(newGame -> m_roundScores);
        free(newGame);
        return NULL;
    }
    resInnerFunc = CreatePlayers(newGame, _playerNames, _numOfPlayers, _type);
    if (resInnerFunc != ERROR_SUCCESS) 
    {
        return NULL;
    }
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
    FreeMembers(*_game, ((*_game) -> m_numOfPlayers) - 1);
    free((*_game) -> m_roundScores);
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
    newRound = RoundCreate(_game -> m_players, _game -> m_numOfPlayers);
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
static Game* AllocateNewGame(char* _playerNames[], int _numOfPlayers)
{
    Game* newGame = (Game*)malloc(sizeof(Game));
    int** roundScores;
    if (NULL == newGame) 
    {
        return NULL;
    }
    roundScores = (int**)calloc(_numOfPlayers, sizeof(int*));
    if (NULL == roundScores) 
    {
        free(newGame);
        return NULL;
    }
    newGame -> m_roundScores = *roundScores;
    return newGame;
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
static void FreeMembers(Game* _game, int _index) 
{
    while (_index >= 0) 
    {
        free(_game -> m_players[_index]);
        --_index;
    }
    free(_game -> m_players);
}
