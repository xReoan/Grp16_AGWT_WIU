#pragma once
#include "Card.h"
class CardDatabase
{
public:
	CardDatabase();
	~CardDatabase();
	Card* getcard(int index);
private:
	static const int cardcount = 50;
	Card* cards[cardcount];
};

