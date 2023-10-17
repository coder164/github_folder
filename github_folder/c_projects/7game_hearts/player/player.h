#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../errstat.h" /* for statuses of errors*/
#define NUM_OF_PLAYERS 4

typedef struct Player Player;
typedef enum PlayerType {
    BOT,
    HUMAN
} PlayerType;

/*
description:	create new Player.
arguments:		_name: player's name.
                _type: player type, BOT or HUMAN.
return value:	pointer to the new player.
errors:			NULL - if the creation failed.*/
Player* PlayerCreate(char _name[], PlayerType _type);

/*
description:	destroy player object and all of it's elements.
arguments:		_player: pointer of pointer to the player.
return value:	none.
errors:			none.*/
void PlayerDestroy(Player** _player);

/*
description:	destroy Vector of cards at the player object.
arguments:		_player: pointer of pointer to the player.
return value:	none.
errors:			none.*/
void CardsDestroy(Player** _player);

/*
description:	give a single card to the specified player.
arguments:		_player: pointer to the player.
                _card: the card.
return value:	ERROR_SUCCESS: if all went well.
errors:			ERROR_POINTER_NULL: if _player or _card are
                    invalid. */
ERRStat GiveCardToPlayer(Player* _player, void* _card);

/*
description:	take card from player.
arguments:		_player: pointer to the player.
return value:	the removed card from player.
errors:			ERROR_POINTER_NULL: if _player is invalid. */
void* TakeCardFromPlayer(Player* _player);
#endif /* __PLAYER_H__ */
