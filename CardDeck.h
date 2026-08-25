#pragma once
#include "Card.h"
class CardDeck
{
public:
	CardDeck();
	~CardDeck();

	void addcardtodraw(Card* card);

	Card* drawcard();
	void discardcard(int index);
	void resetdrawpile();

	Card* getcardfromhand(int index);

	int getdrawcount();
	int gethandcount();
	int getdiscardcount();
	void cleardeck();

	void shuffle();
private:
	int drawcount;
	int handcount;
	int discardcount;
	Card* drawpile[40];
	Card* hand[12];
	Card* discardpile[40];
};

