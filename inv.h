#pragma once
#include "itemDatabase.h"
class inv
{
private:
	static int invinside[16];
	item* invitem[15];
	itemDatabase database;

public:
	inv();
	void OpenInv() const;
	void ReceivedInv(int thing) const; //reciving something, checks if its full inside
	item* getarmorInv(int itemSlot);//like which of the 16 items slot is the item they used is from
	item* getweaponInv(int itemSlot);
	item* geteatInv(int itemSlot);
	int checkingType(int itemSlot);

};

