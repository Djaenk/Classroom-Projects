#ifndef CARD_H
#define CARD_H

enum SUIT { HEART, DIAMOND, SPADE, CLUB };
enum RANK { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

class Card{

public:

	Card();
	
	void SetSuitAndRank(int suit, int rank);
	
	const char * GetRankString();
	
	int GetRank();
	
	const char * GetSuitString();
	
	int GetSuit();

private:
	int suit;
	int rank;
};

#endif