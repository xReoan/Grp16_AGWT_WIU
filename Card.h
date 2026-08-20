#pragma once
#include <string>
#include "item.h"
class Card
{
public:
	enum class cardtype {
		attack,
		defense,
		trap,
		hybrid
	};
	enum class effecttype {
		deal_damage,
		damage_multiplier,
		lower_defense,
		increase_defense,
		increase_attack,
		half_damage_next_turn,
		negate_attack_card,
		negate_defense_card,
		ignore_defense,
		skip_next_turn,
		lifesteal,
		melee_trap,
		trap_counter,
		prepare_upclose,
		poison_tip,
		skip_immunity,
		cannot_attack,
		defense_from_hp_lost,
		shield,
		projectile_to_melee,
		reflect_projectile,
		none
	};
	Card(std::string name, std::string description, cardtype type, item::combattype combat, effecttype effect1, effecttype effect2, effecttype effect3, int value, float multiplier, int hits, int duration);
	std::string getitemname();
	std::string getdescription();
	cardtype gettype();
	effecttype getcardeffect(int index);
	int getvalue();
	float getmultiplier();
	int gethits();
	int getduration();

private:
	item::combattype combattype;
	std::string name;
	std::string description;
	cardtype type;
	effecttype cardeffect[3]; //Card can have up to 3 effects
	float multiplier;
	int value;
	int hits;
	int duration;
};