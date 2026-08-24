#include "Card.h"

Card::Card(std::string name, std::string description, cardtype type, item::combattype combat, effecttype effect1, effecttype effect2, effecttype effect3, int value, float multiplier, int hits, int duration) {
	this->name = name;
	this->description = description;
	this->type = type;
	this->combattype = combat;
	this->cardeffect[0] = effect1;
	this->cardeffect[1] = effect2;
	this->cardeffect[2] = effect3;
	this->value = value;
	this->multiplier = multiplier;
	this->hits = hits;
	this->duration = duration;
}

Card::effecttype Card::getcardeffect(int index) {
	return cardeffect[index];
}

Card::cardtype Card::gettype() {
	return type;
}

item::combattype Card::getcombatcategory() {
	return combattype;
}

std::string Card::getcardname() {
	return name;
}

std::string Card::getcarddescription() {
	return description;
}

int Card::getvalue() {
	return value;
}

float Card::getmultiplier() {
	return multiplier;
}

int Card::gethits() {
	return hits;
}

int Card::getduration() {
	return duration;
}
