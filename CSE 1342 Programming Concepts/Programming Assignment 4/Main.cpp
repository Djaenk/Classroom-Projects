#include "Gameplay.h"
#include "DeckManipulation.h"
#include <iostream>

int main(){
	Game game = Game("John", "Andy");
	while((game.getPlayer1Score() == 0) && (game.getPlayer2Score() == 0)){
		game.displayRound();
		game.play();
		game.resetDrawCount();
		game.givePoints();
	}
	if(game.getPlayer1Score() == 1){
		std::cout << std::endl << game.getPlayer1Name() << " has won the game of war." << std::endl;
	}
	if(game.getPlayer2Score() == 1){
		std::cout << std::endl << game.getPlayer2Name() << " has won the game of war." << std::endl;
	}
}