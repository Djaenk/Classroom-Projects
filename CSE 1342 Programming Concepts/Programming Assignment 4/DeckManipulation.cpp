#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "DeckManipulation.h"

Card::Card(int Suit, int Rank){
	this->Suit = Suit;
	this->Rank = Rank;
}

void Card::printCard(){
	switch (Rank)
	{
		case 0:
			std::cout << "Two of ";
			break;
		case 1:
			std::cout << "Three of ";
			break;
		case 2:
			std::cout << "Four of ";
			break;
		case 3:
			std::cout << "Five of ";
			break;
		case 4:
			std::cout << "Six of ";
			break;
		case 5:
			std::cout << "Seven of ";
			break;
		case 6:
			std::cout << "Eight of ";
			break;
		case 7:
			std::cout << "Nine of ";
			break;
		case 8:
			std::cout << "Ten of ";
			break;
		case 9:
			std::cout << "Jack of ";
			break;
		case 10:
			std::cout << "Queen of ";
			break;
		case 11:
			std::cout << "King of ";
			break;
		case 12:
			std::cout << "Ace of ";
			break;
	}
	switch (Suit){
		case 0:
			std::cout << "Clubs" << std::endl;
			break;
		case 1:
			std::cout << "Diamonds" << std::endl;
			break;
		case 2:
			std::cout << "Hearts" << std::endl;
			break;
		case 3:
			std::cout << "Spades" << std::endl;
			break;
	}
}

int Card::getSuit(){
	return Suit;
}

int Card::getRank(){
	return Rank;
}

Deck::Deck(){
	deck_size = 0;
}

Deck::Deck(bool full){
	if(full == true){
		deck_size = 52;
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 13; k++){
				deck[j * 13 + k] = new Card(j,k);
			}
		}
	}
	else{
		deck_size = 0;
	}
}

void Deck::addCard(Card* card){
	deck[deck_size] = card;
	deck_size++;
}

Card* Deck::peekCard(){
	return deck[deck_size - 1];
}

Card* Deck::removeCard(){
	deck_size--;
	return deck[deck_size];
}

int Deck::getDeckSize(){
	return deck_size;
}

void Deck::shuffle(){
	srand(time(NULL));
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < deck_size; j++){
			swap(deck[j], deck[rand() % deck_size]);
		}
	}
}

void Deck::printCards(){
	for(int i = 0; i < deck_size; i++){
		std::cout << "Card " << i + 1 << ", ";
		deck[i]->printCard();
	}
}

Deck::~Deck(){
	for(int i = 0; i < deck_size; i++){
		deck[i];
	}
}

void Deck::swap(Card*& a, Card*& b){
	Card* temp = b;
	b = a;
	a = temp;
}