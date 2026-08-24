#pragma once
#include "Card.h"
class CardDatabase
{
public:
	CardDatabase();
	~CardDatabase();
	Card* getcard(int index);
private:
	static const int cardcount = 54;
	Card* cards[cardcount];
};

