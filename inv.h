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
	void RecivedInv(int thing) const; //reciving something, checks if its full inside
	void UsedInv(int itemSlot) const; //like which of the 16 items slot is the item they used is from
	
};

