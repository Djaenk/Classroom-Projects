#ifndef TABLETOP_H
#define TABLETOP_H

#include "card.h"
#include "pile.h"
#include "player.h"
#include <stack>

class TableTop{
public:
	TableTop();
	~TableTop();
	bool DoBattle();
private:
	Player playerA;
	Player playerB;
	Pile currentlyInPlay;
	std::stack<Card*> deck;
};

#endif