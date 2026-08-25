#pragma once
#include "item.h"
class itemDatabase
{
public:
	itemDatabase();
	item* getitem(int index) const;
	int getItemCount() const;
private:
	item* items[15];
};

