#include <iostream>
#include "Gameplay.h"

Player::Player(std::string name, Deck deck){
	this->name = name;
	to_play = deck;
	score = 0;
}

std::string Player::getName(){
	return name;
}

int Player::getScore(){
	return score;
}

int Player::getToPlaySize(){
	return to_play.getDeckSize();
}

int Player::getPlayedSize(){
	return played.getDeckSize();
}

Card* Player::removeToPlay(){
	return to_play.removeCard();
}

void Player::addToPlay(Card* card){
	to_play.addCard(card);
}

void Player::addPlayed(Card* card){
	played.addCard(card);
}

Card* Player::removePlayed(){
	return played.removeCard();
}

void Player::earnPoint(){
	score++;
}

void Player::losePoint(){
	score--;
}

Game::Game(std::string player1_name, std::string player2_name) : player1(player1_name, Deck()), player2(player2_name, Deck()){
	Deck dealer = Deck(true);
	Deck player1_deck = Deck();
	Deck player2_deck = Deck();
	for(int i = 0; i < 52; i++){
		if(i % 2 == 0){
			player1_deck.addCard(dealer.removeCard());
		}
		else{
			player2_deck.addCard(dealer.removeCard());
		}
	}
	player1_deck.shuffle();
	player1_deck.printCards();
	player1 = Player(player1_name, player1_deck);
	player2_deck.shuffle();
	player1_deck.printCards();
	player2 = Player(player2_name, player2_deck);
}

void Game::displayRound(){
	std::cout << std::endl << "======== Round " << ++round << " ========" << std::endl;
}

void Game::play(){
	if(player1.getToPlaySize() == 0){
		while(player1.getPlayedSize() != 0){
			player1.addToPlay(player1.removePlayed());
		}
	}
	if(player2.getToPlaySize() == 0){
		while(player2.getPlayedSize() != 0){
			player2.addToPlay(player2.removePlayed());
		}
	}
	in_play.addCard(player1.removeToPlay());
	Card* player1_card = in_play.peekCard();
	std::cout << player1.getName() << " plays ";
	player1_card->printCard();
	in_play.addCard(player2.removeToPlay());
	Card* player2_card = in_play.peekCard();
	std::cout << player2.getName() << " plays ";
	player2_card->printCard();
	if(player1_card->getRank() > player2_card->getRank()){
		std::cout << "--" << player1.getName() << " wins the round" << "--" << std::endl;
		while(in_play.getDeckSize() != 0){
			player1.addToPlay(in_play.removeCard());
		}
		while(player1.getPlayedSize() != 0){
			player1.addToPlay(player1.removePlayed());
		}
		while(player2.getPlayedSize() != 0){
			player1.addToPlay(player2.removePlayed());
		}
		std::cout << player1.getName() << " has " << player1.getToPlaySize() << " cards in their deck" << std::endl;
		std::cout << player2.getName() << " has " << player2.getToPlaySize() << " cards in their deck" << std::endl;
	}
	else if(player1_card->getRank() < player2_card->getRank()){
		std::cout << "--" << player2.getName() << " wins the round" << "--" << std::endl;
		while(in_play.getDeckSize() != 0){
			player2.addToPlay(in_play.removeCard());
		}
		while(player1.getPlayedSize() != 0){
			player2.addToPlay(player1.removePlayed());
		}
		while(player2.getPlayedSize() != 0){
			player2.addToPlay(player2.removePlayed());
		}
		std::cout << player1.getName() << " has " << player1.getToPlaySize() << " cards in their deck" << std::endl;
		std::cout << player2.getName() << " has " << player2.getToPlaySize() << " cards in their deck" << std::endl;
	}
	else{
		draw_count++;
		if(draw_count == 26){
			drawLimit();
			return;
		}		
		std::cout << "--tie, round continues--" << std::endl;
		player2.addPlayed(in_play.removeCard());
		player1.addPlayed(in_play.removeCard());
		play();
	}
}

void Game::givePoints(){
	if(player1.getPlayedSize() == 0 && player1.getToPlaySize() == 0){
		player2.earnPoint();
	}
	if(player2.getPlayedSize() == 0 && player2.getToPlaySize() == 0){
		player1.earnPoint();
	}
}

void Game::resetDrawCount(){
	draw_count = 0;
}

void Game::drawLimit(){
	player1.losePoint();
	player2.losePoint();
}

int Game::getPlayer1Score(){
	return player1.getScore();
}

int Game::getPlayer2Score(){
	return player2.getScore();
}

std::string Game::getPlayer1Name(){
	return player1.getName();
}

std::string Game::getPlayer2Name(){
	return player2.getName();
}