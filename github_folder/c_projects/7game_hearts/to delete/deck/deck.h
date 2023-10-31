#ifndef __DECK_H__
#define __DECK_H__


#include "../cards/cards.h"
#define CARDS_FACTOR 52

typedef struct Deck Deck;

/*
description:	create a new Deck.
arguments:		none.
return value:	pointer of the new deck.
errors:			NULL - if VectorCreate failed due to allocation error. */
Deck* DeckCreate(void);

/*
description:	destroy the deck.
arguments:		_deck: the deck.
return value:	none.
errors:			none.*/
void DeckDestroy(Deck** _deck);

/*
description:	shuffle cards in a single deck.
arguments:		_deck: the deck.
return value:	the deck after shuffle process.
errors:			NULL - if _deck is invalid.*/
Deck* ShuffleCards(Deck* _deck);

/*
description:	remove single card from the deck.
arguments:		_deck: the deck.
return value:	the card that have been removed.
errors:			NULL - if _deck is invalid.*/
Card* TakeCardFromDeck(Deck* _deck);


#endif /* __DECK_H__ */
