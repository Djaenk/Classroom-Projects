#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "tabletop.h"

TableTop::TableTop(){
	srand(time(NULL));
	std::cout << "Welcome to the Game of War!" << std::endl << std::endl;

	for(int i = 0; i < MAXCARDS; i++){
		deck.push(new Card);
		int suit = i / 13;
		int rank = i % 13;
		deck.top()->SetSuitAndRank(suit,rank);
	}

	while(!deck.empty()){
		currentlyInPlay.AddCardToPile(deck.top());
		deck.pop();
	}
	std::cout << "Shuffling initial deck..." << std::endl << std::endl;
	currentlyInPlay.Shuffle();
	
	// Divvy up the initial pile to the players
	for(int i = 0; i < MAXCARDS; i++){
		// Pull a card off the top of the pile
		Card * card = currentlyInPlay.RemoveTopCard();
		
		if(i % 2 == 0){
			playerA.GetToPlayPile()->AddCardToPile(card);
		}
		else{
			playerB.GetToPlayPile()->AddCardToPile(card);
		}
	}
	
	std::cout << "Initial 'to play' piles:" << std::endl << std::endl;
	std::cout << "Player A:" << std::endl;
	playerA.GetToPlayPile()->PrintCards();
	std::cout << std::endl;
	std::cout << "Player B:" << std::endl;
	playerB.GetToPlayPile()->PrintCards();
	std::cout << std::endl;
}

TableTop::~TableTop(){
	while(playerA.GetPlayedPile()->GetNumCards() != 0){
		delete playerA.GetPlayedPile()->RemoveTopCard();
	}
	while(playerA.GetToPlayPile()->GetNumCards() != 0){
		delete playerA.GetToPlayPile()->RemoveTopCard();
	}
	while(playerB.GetPlayedPile()->GetNumCards() != 0){
		delete playerB.GetPlayedPile()->RemoveTopCard();
	}
	while(playerB.GetToPlayPile()->GetNumCards() != 0){
		delete playerB.GetToPlayPile()->RemoveTopCard();
	}
	while(currentlyInPlay.GetNumCards() != 0){
		delete currentlyInPlay.RemoveTopCard();
	}
	while(!deck.empty()){
		delete deck.top();
		deck.pop();
	}
}

bool TableTop::DoBattle(){
	// get a card from each playerA
	Card * cardA = playerA.GetToPlayPile()->RemoveTopCard();
	Card * cardB = playerB.GetToPlayPile()->RemoveTopCard();
	currentlyInPlay.AddCardToPile(cardA);
	currentlyInPlay.AddCardToPile(cardB);
	std::cout << "Player A plays " << cardA->GetRankString() << " of " << cardA->GetSuitString() << "s" << std::endl;
	std::cout << "Player B plays " << cardB->GetRankString() << " of " << cardB->GetSuitString() << "s" << std::endl;
	
	bool tie = false;
	
	if(cardA->GetRank() > cardB->GetRank()){
		std::cout << "Player A wins the 'currently in play' pile." << std::endl << std::endl;
		while(currentlyInPlay.GetNumCards() > 0){
			Card * wonCard = currentlyInPlay.RemoveTopCard();
			playerA.GetPlayedPile()->AddCardToPile(wonCard);
		}
	} else if (cardA->GetRank() < cardB->GetRank()){
		std::cout << "Player B wins the 'currently in play' pile." << std::endl << std::endl;
		while(currentlyInPlay.GetNumCards() > 0){
			Card * wonCard = currentlyInPlay.RemoveTopCard();
			playerB.GetPlayedPile()->AddCardToPile(wonCard);
		}
	} else {
		std::cout << "There is a tie... Doing another battle." << std::endl << std::endl;
		tie = true;
	}
	
	// Replace cards if the 'to play' deck is empty
	
	if(playerA.GetToPlayPile()->GetNumCards() == 0 && playerA.GetPlayedPile()->GetNumCards() > 0){
		std::cout << "Player A ran out of cards in their 'to play' pile.  Getting cards from the 'played' pile." << std::endl;
		while(playerA.GetPlayedPile()->GetNumCards() > 0){
			Card * replacementCard = playerA.GetPlayedPile()->RemoveTopCard();
			playerA.GetToPlayPile()->AddCardToPile(replacementCard);
		}
		
		std::cout << "Shuffling player A cards..." << std::endl << std::endl;
		playerA.GetToPlayPile()->Shuffle();
	}
	
	if(playerB.GetToPlayPile()->GetNumCards() == 0 && playerB.GetPlayedPile()->GetNumCards() > 0){
		std::cout << "Player B ran out of cards in their 'to play' pile.  Getting cards from the 'played' pile." << std::endl;
		while(playerB.GetPlayedPile()->GetNumCards() > 0){
			Card * replacementCard = playerB.GetPlayedPile()->RemoveTopCard();
			playerB.GetToPlayPile()->AddCardToPile(replacementCard);
		}

		std::cout << "Shuffling player B cards..." << std::endl << std::endl;
		playerB.GetToPlayPile()->Shuffle();
	}
	
	// Print the current piles.
	
	std::cout << "Player A has " << playerA.GetToPlayPile()->GetNumCards() << " in their 'to play' pile and " << playerA.GetPlayedPile()->GetNumCards() << " in their 'played' pile." << std::endl;
	std::cout << "Player B has " << playerB.GetToPlayPile()->GetNumCards() << " in their 'to play' pile and " << playerB.GetPlayedPile()->GetNumCards() << " in their 'played' pile." << std::endl;
	std::cout << std::endl;

	// Check if anyone has lost.
	
	bool someoneRanOutOfCards = false;
	if(playerA.GetToPlayPile()->GetNumCards() == 0){
		someoneRanOutOfCards = true;
		std::cout << "Player A ran out of cards.  Player A has lost." << std::endl;
	}
	if(playerB.GetToPlayPile()->GetNumCards() == 0){
		someoneRanOutOfCards = true;
		std::cout << "Player B ran out of cards.  Player B has lost." << std::endl;
	}
	
	// Report to main
	
	if(!someoneRanOutOfCards && tie){
		return DoBattle(); // recursively call DoBattle
	}
	else{
		return someoneRanOutOfCards;
	}
}
