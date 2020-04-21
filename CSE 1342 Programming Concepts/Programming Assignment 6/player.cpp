#include "player.h"

Player::Player(){
	toPlay = new Pile;
	played = new Pile;
}

Player::~Player(){
	delete toPlay;
	delete played;
}

Pile * Player::GetToPlayPile(){
	return toPlay;
}

Pile * Player::GetPlayedPile(){
	return played;
}
