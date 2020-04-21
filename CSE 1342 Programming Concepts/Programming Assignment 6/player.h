#ifndef PLAYER_H
#define PLAYER_H

#include "pile.h"

class Player{

public:
	Player();
	
	~Player();

	Pile * GetToPlayPile();
	
	Pile * GetPlayedPile();

private:
	Pile * toPlay;
	Pile * played;
	
};


#endif