#ifndef __GAME_H__
#define __GAME_H__


#include "../player/player.h" /* for PlayerType */
#include "../errstat.h" /* for error statuses */

#define MIN_POINTS_TO_FINISH (100)

typedef struct Game Game;

/*
description:	create a new Game object.
arguments:		_playerNames: array of player names.
                _types: array of types of players, BOT/HUMAN.
                _numOfPlayers: the number of players.
return value:	pointer of the new Game.
errors:			NULL - if number of players is less than 1.
                     - if _playerNames is NULL.
                     - if _playerNames contains less names than _numOfPlayers.
                     - if creation failed due to allocation error. */
Game* GameCreate(char* _playerNames[], PlayerType _types[],
    int _numOfPlayers);

/*
description:	destroy the Game.
arguments:		_game: pointer to the heap location of the game.
return value:	none.
errors:			none.*/
void GameDestroy(Game** _game);

/*
description:	running the given game until finish, someone reaches the minimum point to end the game.
arguments:		_game: pointer to the heap location of the game.
return value:	none.
errors:			none.*/
ERRStat GameRun(Game* _game);


#endif /* __GAME_H__ */
