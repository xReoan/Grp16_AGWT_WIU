#include "CardDatabase.h"
CardDatabase::CardDatabase() {
	//Card(std::string name, std::string description, cardtype type, item::combattype combat, effecttype effect1, effecttype effect2, effecttype effect3, int value, float multiplier, int hits, int duration);
	//basic set
	cards[0] = new Card("Strike", "Basic attack.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[1] = new Card("Chemical Boost", "Raises attacks paired with this card by 1.5x. Lucky you, it could have been drugs.", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::damage_multiplier, Card::effecttype::none, Card::effecttype::none, 0, 1.5f, 0, 1);
	cards[2] = new Card("Weak Point Strike", "Deals damage and lowers enemy defense by 3.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::deal_damage, Card::effecttype::lower_defense, Card::effecttype::none, 3, 0.5f, 1, 0);
	cards[3] = new Card("Suit up", "Raises defense.", Card::cardtype::defense, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 0);
	cards[4] = new Card("Brace", "Brace, brace. Next attack deals 0.5x damage.", Card::cardtype::defense, item::combattype::none, Card::effecttype::half_damage_next_turn, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 0, 0);
	cards[5] = new Card("Be Alert!", "Become alert; If enemy uses at least 2 attack cards, negate one of the cards' effects.", Card::cardtype::trap, item::combattype::none, Card::effecttype::negate_attack_card, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 0);
	cards[6] = new Card("Watch!", "Watch their every move...; If enemy uses at least 2 defense cards, negate one of the cards' effects.", Card::cardtype::trap, item::combattype::none, Card::effecttype::negate_defense_card, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 0);

	//advanced melee
	cards[6] = new Card("Metal Piercer", "Channel your inner phantom penetration and ignore all defenses when an offensive card is played with this card. (If this card is played alone, lower enemy defense by 5 for 1 turn)", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::ignore_defense, Card::effecttype::lower_defense, Card::effecttype::none, 5, 1.0f, 0, 1);
	cards[7] = new Card("Heavy Strike", "Deal massive melee damage, but takes a toll on your back and thus skipping 1 turn. Not affected by skip immunity.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::skip_next_turn, Card::effecttype::none, 0, 2.0f, 1, 1);
	cards[8] = new Card("Young Vamp Life", "Deal melee damage and regain health based on damage dealt.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[9] = new Card("Rat Trap", "Trap that catches anything but rats", Card::cardtype::trap, item::combattype::melee, Card::effecttype::melee_trap, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 1, 0);
	cards[10] = new Card("Mirror Trap", "Hate traps? This is your chance to get revenge!", Card::cardtype::trap, item::combattype::none, Card::effecttype::trap_counter, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);

	//advanced ranged
	cards[11] = new Card("Multifire", "Fires 5 rounds in quick succesion.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 5, 0);
	cards[12] = new Card("Charge!!!", "Charges straight to the enemy like a bull for one turn, reducing defense and then dealing massive damage the next.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::deal_damage, Card::effecttype::lower_defense, Card::effecttype::prepare_upclose, 0, 2.0f, 1, 1);
	cards[13] = new Card("The Big Bang", "If used with Multifire, deals all the damage at once. Else, increase attack by 10 for the next turn", Card::cardtype::hybrid, item::combattype::projectile, Card::effecttype::increase_attack, Card::effecttype::deal_damage, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[14] = new Card("Poison-Tipped Bullets", "Do poison tipped bullets actually make a difference?? Pair attack cards with this one to poison the enemy", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::poison_tip, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);
	cards[15] = new Card("Rat Trap", "Trap that catches anything but rats.", Card::cardtype::trap, item::combattype::projectile, Card::effecttype::melee_trap, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 1, 0);

	//advanced mdef
	cards[16] = new Card("Bubblewrap Shield", "Nice to pop. But if you do, you probably get hurt more. Gives a one-time 30hp shield", Card::cardtype::defense, item::combattype::none, Card::effecttype::shield, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[17] = new Card("Phalanxing", "Phalanxing solo might not be the best move... Increases defense and attack. Increases even more if enemy deals 10 damage to you in the next turn", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::increase_attack, Card::effecttype::none, 0, 1.0f, 0, 1);
	cards[18] = new Card("Rat Trap", "Trap that catches anything but rats.", Card::cardtype::trap, item::combattype::melee, Card::effecttype::melee_trap, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 1, 0);

}

CardDatabase::~CardDatabase() {
}

Card* CardDatabase::getcard(int index) {
	return cards[index];
}

//	deal_damage,
//	damage_multiplier,
//	lower_defense,
//	increase_defense,
//	half_damage_next_turn,
//	negate_attack_card,
//	negate_defense_card,
//	ignore_defense,
//	skip_next_turn,
//	lifesteal,
//	melee_trap,
//	trap_counter,
//	prepare_upclose,
//	poison_tip,
//	skip_immunity,
//	cannot_attack,
//	defense_from_hp_lost,
//	shield,
//	projectile_to_melee,
//	reflect_projectile,
//	none

