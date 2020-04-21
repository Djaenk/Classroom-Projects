#ifndef DECK
#define DECK

enum class Suit{Clubs, Diamonds, Hearts, Spades};

enum class Rank{Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};

class Card{
	public:
		Card(int Suit, int Rank);
		void printCard();
		int getSuit();
		int getRank();
	private:
		int Suit;
		int Rank;
};

class Deck{
	public:
		Deck();
		Deck(bool full);
		void addCard(Card* card);
		Card* peekCard();
		Card* removeCard();
		int getDeckSize();
		void shuffle();
		void printCards();
		~Deck();
	private:
		int deck_size;
		Card* deck[52];
		void swap(Card*& a, Card*& b);
};

#endif