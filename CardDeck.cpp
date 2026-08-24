#include "CardDeck.h"

CardDeck::CardDeck() {
	drawcount = 0;
	handcount = 0;
	discardcount = 0;
	for (int i = 0; i < 40; i++) {
		drawpile[i] = nullptr;
		discardpile[i] = nullptr;
	}

	for (int i = 0; i < 12; i++) {
		hand[i] = nullptr;
	}
}

void CardDeck::addcardtodraw(Card* card) {
	if (drawcount < 40) {
		drawpile[drawcount] = card;
		drawcount++;
	}
}

Card* CardDeck::drawcard() {
	if (drawcount == 0 && handcount < 12) {
		resetdrawpile();
	}

	if (drawcount > 0 && handcount < 12) {
		Card* drawncard = drawpile[drawcount - 1];
		hand[handcount] = drawncard;
		drawpile[drawcount - 1] = nullptr;
		drawcount--;
		handcount++;
		return drawncard;
	}
	return nullptr;
}

void CardDeck::discardcard(int index) {
	if (index >= 0 && index < handcount) {
		discardpile[discardcount] = hand[index];
		for (int i = index; i < handcount - 1; i++) {
			hand[i] = hand[i + 1];
		}
		hand[handcount - 1] = nullptr;
		discardcount++;
		handcount--;
	}
}

void CardDeck::cleardeck() {
	drawcount = 0;
	handcount = 0;
	discardcount = 0;
	for (int i = 0; i < 40; i++) {
		drawpile[i] = nullptr;
		discardpile[i] = nullptr;
	}

	for (int i = 0; i < 12; i++) {
		hand[i] = nullptr;
	}
}

void CardDeck::shuffle() {
	for (int i = 0; i < drawcount; i++) {
		int whatcard = rand() % drawcount;
		Card* newcard = drawpile[i];
		drawpile[i] = drawpile[whatcard];
		drawpile[whatcard] = newcard;
	}
}

void CardDeck::resetdrawpile() {
	if (drawcount == 0) {
		for (int i = 0; i < discardcount; i++) {
			drawpile[i] = discardpile[i];
			discardpile[i] = nullptr;
		}
		drawcount += discardcount;
		discardcount = 0;
		shuffle();
	}
}

Card* CardDeck::getcardfromhand(int index) {
	if (index >= 0 && index < handcount) {
		return hand[index];
	}
	else {
		return nullptr;
	}
}

int CardDeck::getdrawcount() {
	return drawcount;
}

int CardDeck::gethandcount() {
	return handcount;
}

int CardDeck::getdiscardcount() {
	return discardcount;
}

CardDeck::~CardDeck() {

}