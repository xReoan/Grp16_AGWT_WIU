#pragma once
#include <string>
class item
{
public:
	enum class itemtype {
		weapon,
		armor,
		consumable
	};
	enum class combattype {
		melee,
		projectile,
		flexible,
		none
	};
	enum class passive {
		none,
		dot_on_hit,
		lower_pdef_on_attack,
		skip_enemy_first_turn,
		absorb_projectile_heal
	};
	item(std::string name, std::string description, itemtype itemcategory, combattype combatcategory, int attackvalue, int defensevalue, int healvalue, int duration, int price);
	std::string getname();
	std::string getdescription();
	itemtype getitemcategory();
	combattype getcombatcategory();
	passive getpassiveeffect();
	int getattackvalue();
	int getdefensevalue();
	int gethealvalue();
	int getduration();
	int getprice();
private:
	std::string itemname;
	std::string itemdescription;
	itemtype itemcategory;
	combattype combatcategory;
	passive passiveeffect;
	int attackvalue;
	int defensevalue;
	int healvalue;
	int duration;
	int price;
};

