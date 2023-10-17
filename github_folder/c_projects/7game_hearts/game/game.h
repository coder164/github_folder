#ifndef __GAME_H__
#define __GAME_H__

#include "../player/player.h" /* for PlayerType */
#include "../errstat.h" /* for error statuses */


typedef struct Game Game;

/*
description:	create a new Game object.
arguments:		_playerNames: array of player names.
                _numOfPlayers: the number of players.
                _type: player type, BOT or HUMAN.
return value:	pointer of the new Game.
errors:			NULL - if number of players is less than 1.
                     - if _playerNames is NULL.
                     - if _playerNames contains less names than _numOfPlayers.
                     - if creation failed due to allocation error. */
Game* GameCreate(char* _playerNames[], int _numOfPlayers,
    PlayerType _type);

/*
description:	destroy the Game.
arguments:		_game: pointer to the heap location of the game.
return value:	none.
errors:			none.*/
void GameDestroy(Game** _game);

ERRStat GameRun(Game* _game);

#endif /* __GAME_H__ */
