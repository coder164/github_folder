#ifndef __CARDS_H__
#define __CARDS_H__


typedef enum Suit {
    HEARTS, SPADES, DIAMONDS, CLUBS, NUM_OF_SUITS
} Suit;

typedef enum Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, NUM_OF_RANK
} Rank;

typedef struct Card {
    Rank m_rank;
    Suit m_suit;
} Card;


#endif /* __CARDS_H__ */
