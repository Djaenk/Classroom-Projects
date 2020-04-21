#ifndef PILE_H
#define PILE_H

#include <stack>
#include "card.h"

#define MAXCARDS 52

class Pile{
public:
	void AddCardToPile(Card * card);
	Card * RemoveTopCard();
	int GetNumCards();
	void Shuffle();
	void Swap(Card*& a, Card*& b);
	void PrintCards();
private:
	std::stack<Card*> pile;
};

#endif