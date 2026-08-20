#pragma once
#include "item.h"
class itemDatabase
{
public:
	itemDatabase();
	item* getitem(int index);
private:
	item* items[10];
};



