#ifndef __CARDS_H__
#define __CARDS_H__


typedef enum Suits {
    HEART, LEEF, DIAMOND, CLUBS, NUM_OF_SUITS
} Suits;

typedef enum Rank {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, NUM_OF_RANK
} Rank;

typedef struct Card {
    Suits m_suit;
    Rank m_rank;
} Card;


#endif /* __CARDS_H__ */
