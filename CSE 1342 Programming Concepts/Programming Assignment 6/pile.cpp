#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <time.h>
#include "Pile.h"

void Pile::AddCardToPile(Card * card){
	// adds a card to the end of the array		
	pile.push(card);
}

Card * Pile::RemoveTopCard(){
	// removes a card from the end of the array
	Card * cardToReturn = pile.top();
	pile.pop();
	return cardToReturn;
}

int Pile::GetNumCards(){
	return pile.size();
}

void Pile::Shuffle(){
	// do random swaps
	std::vector<Card*> temp;
	while(!pile.empty()){
		temp.push_back(pile.top());
		pile.pop();
	}
	srand(time(NULL));
	for(int i = 0; i < 7; i++){
		for(int j = 0; j < temp.size(); j++){
			Swap(temp[j], temp[rand() % temp.size()]);
		}
	}
	for(int i = 0; i < temp.size(); i++){
		pile.push(temp[i]);
	}
}

void Pile::Swap(Card*& a, Card*& b){
	Card* temp = b;
	b = a;
	a = temp;
}

void Pile::PrintCards(){
	std::stack<Card*> temp;
	std::cout << "There are " << pile.size() << " cards in the pile." << std::endl;
	while(!pile.empty()){
		temp.push(pile.top());
		std::cout << "Card " << temp.size() << ", " << temp.top()->GetRankString() << " of " << temp.top()->GetSuitString() << "s" << std::endl;
		pile.pop();
	}
	while(!temp.empty()){
		pile.push(temp.top());
		temp.pop();
	}
}