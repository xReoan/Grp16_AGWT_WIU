#include "item.h"

item::item(std::string name, std::string description, itemtype itemcategory, equipment equipmenttier, combattype combatcategory, int attackvalue, int defensevalue, int healvalue, int duration, int price) {
	this->itemname = name;
	this->itemdescription = description;
	this->itemcategory = itemcategory;
	this->combatcategory = combatcategory;
	this->attackvalue = attackvalue;
	this->defensevalue = defensevalue;
	this->healvalue = healvalue;
	this->duration = duration;
	this->price = price;
	this->passiveeffect = passive::none;
}

std::string item::getname() {
	return itemname;
}

std::string item::getdescription() {
	return itemdescription;
}

int item::getattackvalue() {
	return attackvalue;
}

int item::getdefensevalue() {
	return defensevalue;
}

int item::gethealvalue() {
	return healvalue;
}

int item::getduration() {
	return duration;
}

int item::getprice() {
	return price;
}

item::itemtype item::getitemcategory() {
	return itemcategory;
}

item::combattype item::getcombatcategory() {
	return combatcategory;
}

item::equipment item::getequipmenttier() {
	return equipmenttier;
}

item::passive item::getpassiveeffect()
{
	return passiveeffect;
}