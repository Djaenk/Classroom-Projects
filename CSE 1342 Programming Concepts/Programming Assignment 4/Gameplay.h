#ifndef GAMEPLAY
#define GAMEPLAY

#include "DeckManipulation.h"
#include <string>

class Player{
	public:
		Player(std::string name, Deck deck);
		std::string getName();
		int getScore();
		int getToPlaySize();
		int getPlayedSize();
		Card* removeToPlay();
		void addToPlay(Card* card);
		void addPlayed(Card* card);
		Card* removePlayed();
		void earnPoint();
		void losePoint();
	private:
		std::string name;
		int score;
		Deck to_play;
		Deck played;
};

class Game{
	public:
		Game(std::string player1_name, std::string player2_name);
		void play();
		void displayRound();
		void givePoints();
		void resetDrawCount();
		void drawLimit();
		int getPlayer1Score();
		int getPlayer2Score();
		std::string getPlayer1Name();
		std::string getPlayer2Name();
	private:
		Deck dealer;
		Player player1;
		Player player2;
		Deck in_play;
		int round = 0;
		int draw_count;
};

#endif