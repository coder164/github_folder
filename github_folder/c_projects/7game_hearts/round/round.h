#ifndef __ROUND_H__
#define __ROUND_H__


#include "../errstat.h"         /* for error statuses */
#include "../player/player.h"   /* for RoundCreate() function */
#include "../cards/cards.h"     /* for the pointer functions */

typedef struct Round Round;

typedef enum TransferDirection {
    LEFT,
    RIGHT,
    OPPOSITE,
    NO_TRANSFER
} TransferDirection;

/*
description:	pointer function to take/give card from/to player at the
                    round start.
arguments:		_card: card to move from/to player.
                _context: context to be used.
return value:	ERROR_SUCCESS: if all went well.
errors:			ERROR_POINTER_NULL: if one of the cards is invalid. */
typedef ERRStat (*HeartsThreeCards)(Card* _card, void* _context);

/*
description:	pointer function for the implementation of the game rules
                    at the round play.
arguments:		_card: selected card from the player to put on the table.
                _table: the table that holding the selected card ftom
                    each player.
                _hand: the hand signature that the player played by the rules.
                _context: context to be used.
return value:	ERROR_SUCCESS: if all went well.
errors:			ERROR_POINTER_NULL: - if _card is invalid
                                    - if _table is invalid
                                    - if _hand is invalid. */
typedef ERRStat (*HeartsRules)(Card* _card, Card* _table, ERRStat _hand,
    void* _context);

/*
description:	create a new Round object.
arguments:		_players: pointer to pointers of players.
                _numOfPlayers: the number of palyers.
                _roundNum: thr number of the round
return value:	pointer of the new Round.
errors:			NULL - if allocation failed.*/
Round* RoundCreate(Player** _players, int _numOfPlayers, int _roundNum);

/*
description:	destroy the round with all it's elements.
arguments:		_round: the round to destroy.
return value:	none.
errors:			none.*/
void RoundDestroy(Round** _round);

/*
description:	run one round of the game.
arguments:		_round: pointer to the Round object.
                _direction: the direction of play start of moving the three
                beginning cards from each player.
return value:	ERROR_SUCCESS: if all went well.
errors:			ERROR_POINTER_NULL: if _round is invalid.*/
ERRStat RunRound(Round* _round, TransferDirection _direction);

int GetPoints(Round* _round, int _indexOfPlayer);

void EmptyRound(Round** _round);


#endif /* __ROUND_H__ */
