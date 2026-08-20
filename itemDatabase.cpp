#include "itemDatabase.h"
itemDatabase::itemDatabase() {
	//	item(string name, string description, itemtype itemcategory, combattype combatcategory, int value);
	items[0] = new item("Rock", "rock", item::itemtype::weapon, item::combattype::melee, 10, 0, 0, 0, 0);
	items[1] = new item("Knife", "breaking news: knife found in kitchen", item::itemtype::weapon, item::combattype::melee, 12, 0, 0, 0, 5);
	items[2] = new item("Sword", "you might be arthur", item::itemtype::weapon, item::combattype::melee, 14, 0, 0, 0, 15);
	items[3] = new item("Nerf Gun", "cool nerf gun with one bullet missing", item::itemtype::weapon, item::combattype::projectile, 10, 0, 0, 0, 3);
	items[4] = new item("Pistol", "pew pew", item::itemtype::weapon, item::combattype::projectile, 12, 0, 0, 0, 5);
	items[5] = new item("Shotgun", "bigger pew pew", item::itemtype::weapon, item::combattype::projectile, 14, 0, 0, 0, 15);

	items[6] = new item("Cardboard Box", "makes you feel homeless. or like a hermit crab", item::itemtype::armor, item::combattype::none, 0, 4, 0, 0, 2);
	items[7] = new item("Lab Coat", "wearing this makes you feel slightly smarter. only slightly.", item::itemtype::armor, item::combattype::none, 0, 6, 0, 0, 3);
	items[8] = new item("oooh Shiny Armor", "so shiny you could die", item::itemtype::armor, item::combattype::melee, 0, 12, 0, 0, 7);
	items[9] = new item("Leftover Jelly", "leftover jelly left since (year the lab was abandoned idk). goes well with milk.", item::itemtype::armor, item::combattype::projectile, 0, 10, 0, 0, 7);
}


item* itemDatabase::getitem(int index) {
	return items[index];
}