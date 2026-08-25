#include "itemDatabase.h"
itemDatabase::itemDatabase() {
	//	item(std::string name, std::string description, itemtype itemcategory, equipment tier, combattype combatcategory, int attackvalue, int defensevalue, int healvalue, int duration, int price);
	items[0] = new item("Rock", "rock", item::itemtype::weapon, item::equipment::basic, item::combattype::melee, 10, 0, 0, 0, 0);
	items[1] = new item("Knife", "breaking news: knife found in kitchen", item::itemtype::weapon, item::equipment::basic, item::combattype::melee, 12, 0, 0, 0, 5);
	items[2] = new item("Sword", "you might be arthur", item::itemtype::weapon, item::equipment::advanced, item::combattype::melee, 14, 0, 0, 0, 15);
	items[3] = new item("Nerf Gun", "cool nerf gun with one bullet missing", item::itemtype::weapon, item::equipment::basic, item::combattype::projectile, 10, 0, 0, 0, 3);
	items[4] = new item("Pistol", "pew pew", item::itemtype::weapon, item::equipment::basic, item::combattype::projectile, 12, 0, 0, 0, 5);
	items[5] = new item("Shotgun", "bigger pew pew", item::itemtype::weapon, item::equipment::advanced, item::combattype::projectile, 14, 0, 0, 0, 15);

	items[6] = new item("Cardboard Box", "makes you feel homeless. or like a hermit crab", item::itemtype::armor, item::equipment::basic, item::combattype::none, 0, 4, 0, 0, 2);
	items[7] = new item("Lab Coat", "wearing this makes you feel slightly smarter. only slightly.", item::itemtype::armor, item::equipment::basic, item::combattype::none, 0, 6, 0, 0, 3);
	items[8] = new item("oooh Shiny Armor", "so shiny you could die", item::itemtype::armor, item::equipment::advanced, item::combattype::melee, 0, 12, 0, 0, 7);
	items[9] = new item("Leftover Jelly", "leftover jelly left since (year the lab was abandoned idk). goes well with milk.", item::itemtype::armor, item::equipment::advanced, item::combattype::projectile, 0, 10, 0, 0, 7);

	items[10] = new item("Cake...?", "a sus piece of cake. surprisingly fresh...?", item::itemtype::consumable, item::equipment::none, item::combattype::none, 0, 0, 7, 0, 7);
	items[11] = new item("Needle", "looks like its been used, do you have anything else? please say yes, dont use this.", item::itemtype::consumable, item::equipment::none, item::combattype::none, 0, 0, 10, 0, 5);
	items[12] = new item("Bandage", "random bandage. there doesn't seem to be a medkit, however...", item::itemtype::consumable, item::equipment::none, item::combattype::none, 0, 0, 2, 5, 5);
	items[13] = new item("Instant Ramen", "quick and easy meal. cleanses your bowels too, contrary to popular belief.", item::itemtype::consumable, item::equipment::none, item::combattype::none, 0, 0, 10, 0, 10);
	items[14] = new item("Cheese", "takes the form of your favourite cheese. yum!", item::itemtype::consumable, item::equipment::none, item::combattype::none, 0, 0, 20, 0, 15);
}
item* itemDatabase::getitem(
    int index) const
{
    if (index < 0 ||
        index >= 15)
    {
        return nullptr;
    }

    return items[index];
}

int itemDatabase::getItemCount() const
{
    return 15;
}