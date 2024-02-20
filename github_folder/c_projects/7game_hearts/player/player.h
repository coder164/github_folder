#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "../errstat.h" /* for statuses of errors*/

#define NUM_OF_PLAYERS 4

typedef struct Player Player;
typedef enum PlayerType {
    BOT,
    HUMAN,
    UNDEFINED
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
description:	give a single card to the specified player.
arguments:		_player: pointer to the player.
                _card: the card.
return value:	ERROR_SUCCESS: if all went well.
errors:			ERROR_POINTER_NULL: - if _player is invalid
                                    - if _card is invalid. */
ERRStat GiveCardToPlayer(Player* _player, void* _card);

/*
description:	take card from player.
arguments:		_player: pointer to the player.
                _card: the card to be moved to.
return value:	ERROR_OK.
errors:			ERROR_POINTER_NULL: - if _player is invalid
                                    - if _card is invalid. */
ERRStat TakeCardFromPlayer(Player* _player, void** _card);

/*
description:	get the type of the player.
arguments:		_player: pointer to the player.
return value:	type of the player.
errors:			UNDEFINED: if _player is invalid. */
PlayerType GetPlayerType(Player* _player);

/*
description:	get pointer to the name of the player.
arguments:		_player: pointer to the player.
return value:	pointer to the first letter of the name of the player.
errors:			NULL: if _player is invalid. */
char* GetPlayerName(Player* _player);

/*
description:    check if the player has the card two of clubs.
arguments:      _player: pointer to the player.
return value:   TRUE: if he has the card.
                False: if he doesn't has it.
errors:         ERROR_POINTER_NULL: if _player is invalid.
*/
ERRStat IsHavingTwoOfClubs(const Player* const _player);

/*
description:    finds the index of Two of Clubs if there it exist at the given player.
arguments:      _player: pointer to the player.
return value:   if it found - the index of the card.
                if it's not found - index of the number of cards in the hand of the player.
errors:         ERROR_POINTER_NULL - if _player is invalid.
*/
int FindIndexOfTwoOfClubs(Player* _player);

/*
description:    getting the number of cards in at the given player.
arguments:      _player: pointer to the player.
return value:   the number of cards at the player.
errors:         none.
*/
int GetNumOfCards(Player* _player);

/*
description:    check if the player is allowed to start with Hearts suit.
arguments:      _player: pointer to the player.
return value:   TRUE - if the player is allowed
                FALSE - if the player is not allowed
errors:         none.
*/
ERRStat MayStartWithHearts(Player* _player);

#endif /* __PLAYER_H__ */
