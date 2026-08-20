#pragma once
#include <string>
using namespace std;
class Card
{
public:
	Card();

	enum class cardtype {
		attack,
		defense,
		trap,
		hybrid
	};
	enum class effecttype {
		damage,
		defense,
		halfdamage,
		armorpierce,
		skipturn,
		DoT,
		lifesteal,
		reflect,
		multihit
	};
	string getitemname();
	string getdescription();
	int getvalue();

private:
	string name;
	string description;
	cardtype type;
	effecttype cardeffect;
	float multiplier;
	int value;
};

