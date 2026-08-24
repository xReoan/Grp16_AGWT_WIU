#pragma once
#include "itemDatabase.h"
#include"Player.h"
class inv
{
private:
	static int invinside[16];
	item* invitem[15];
	itemDatabase database;
	//Player player;

public:
	inv();
	void OpenInv() const;
	void RecivedInv(int thing) const; //reciving something, checks if its full inside
	void UsedInv(int itemSlot, item* armor, item* weapon) const; //like which of the 16 items slot is the item they used is from
};

