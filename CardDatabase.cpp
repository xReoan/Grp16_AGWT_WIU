#include "CardDatabase.h"
CardDatabase::CardDatabase() {
	//Card(std::string name, std::string description, cardtype type, item::combattype combat, effecttype effect1, effecttype effect2, effecttype effect3, int value, float multiplier, int hits, int duration);
	// PLAYER -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//basic set
	cards[0] = new Card("Strike", "Basic attack.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[1] = new Card("Chemical Boost", "Raises attacks paired with this card by 1.5x. Lucky you, it could have been drugs.", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::damage_multiplier, Card::effecttype::none, Card::effecttype::none, 0, 1.5f, 0, 0);
	cards[2] = new Card("Weak Point Strike", "Deals damage and lowers enemy defense by 3.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::deal_damage, Card::effecttype::lower_defense, Card::effecttype::none, 3, 0.5f, 1, 0);
	cards[3] = new Card("Suit Up", "Raises defense.", Card::cardtype::defense, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 0);
	cards[4] = new Card("Brace", "Brace, brace. Next attack deals 0.5x damage.", Card::cardtype::defense, item::combattype::none, Card::effecttype::half_damage_next_turn, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 0, 0);
	cards[5] = new Card("Be Alert!", "Become alert; If enemy uses at least 2 attack cards next turn, negate one of the cards' effects.", Card::cardtype::trap, item::combattype::none, Card::effecttype::negate_attack_card, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);
	cards[6] = new Card("Watch!", "Watch their every move...; If enemy uses at least 2 defense cards next turn, negate one of the cards' effects.", Card::cardtype::trap, item::combattype::none, Card::effecttype::negate_defense_card, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);

	//advanced melee
	cards[7] = new Card("Metal Piercer", "Channel your inner phantom penetration and ignore all defenses when an offensive card is played with this card. (If this card is played alone, lower enemy defense by 5 for 1 turn)", Card::cardtype::hybrid, item::combattype::melee, Card::effecttype::ignore_defense, Card::effecttype::lower_defense, Card::effecttype::none, 5, 1.0f, 0, 1);
	cards[8] = new Card("Heavy Strike", "Deal massive melee damage, but you injure your back as a result, skipping 1 turn. Not affected by skip immunity.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::forced_skip, Card::effecttype::none, 0, 2.0f, 1, 1);
	cards[9] = new Card("Young Vamp Life", "Deal melee damage and regain health based on damage dealt.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::lifesteal, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[10] = new Card("Rat Trap", "Trap that catches anything but rats", Card::cardtype::trap, item::combattype::melee, Card::effecttype::melee_trigger_trap, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 1, 1);
	cards[11] = new Card("Mirror Trap", "Hate traps? This is your chance to get revenge!", Card::cardtype::trap, item::combattype::none, Card::effecttype::trap_counter, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);

	//advanced ranged
	cards[12] = new Card("Multifire", "Fires 5 rounds in quick succession.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 5, 0);
	cards[13] = new Card("Charge!!!", "Charges straight to the enemy like a bull for one turn, reducing your defense by 5, then dealing massive damage the next.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::deal_damage, Card::effecttype::lower_own_defense, Card::effecttype::prepare_upclose, 5, 2.0f, 1, 1);
	cards[14] = new Card("The Big Bang", "If used with Multifire, deals all the damage at once. Else, increase attack by 5 for the next turn", Card::cardtype::hybrid, item::combattype::projectile, Card::effecttype::increase_attack, Card::effecttype::multishot_combo, Card::effecttype::none, 5, 1.0f, 1, 1);
	cards[15] = new Card("Poison-Tipped Bullets", "Do poison tipped bullets actually make a difference?? Pair attack cards with this one to poison the enemy", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::poison_tip, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 3);
	cards[16] = new Card("Rat Trap", "Trap that catches anything but rats.", Card::cardtype::trap, item::combattype::projectile, Card::effecttype::melee_trigger_trap, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 1, 1);

	//defense
	cards[17] = new Card("Bubblewrap Shield", "Nice to pop. But if you do, you probably get hurt more. Gives a one-time 20hp shield", Card::cardtype::defense, item::combattype::none, Card::effecttype::shield, Card::effecttype::none, Card::effecttype::none, 20, 1.0f, 0, 0);
	//advanced mdef
	cards[18] = new Card("Phalanxing", "Phalanxing solo might not be the best move... Increases melee defense and attack. Increases even more if enemy deals 10 damage to you in the next turn", Card::cardtype::hybrid, item::combattype::melee, Card::effecttype::phalanxing, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);
	cards[19] = new Card("From The Trenches", "Being weaker makes you stronger. Or something like that.", Card::cardtype::defense, item::combattype::flexible, Card::effecttype::defense_from_hp_lost, Card::effecttype::none, Card::effecttype::none, 0, 0.5f, 0, 0);
	cards[20] = new Card("Fight Me Like A Man (or woman)", "Converts the next projectile attack into melee.", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::projectile_to_melee, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);

	//advanced pdef
	cards[21] = new Card("Unstoppable", "Can't stop the A-train. Become unstoppable to any obstacles(skips)! (except maybe a banana peel)", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::skip_immunity, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);
	cards[22] = new Card("Mats", "Like the thing from fortnite", Card::cardtype::hybrid, item::combattype::projectile, Card::effecttype::increase_defense, Card::effecttype::cannot_attack, Card::effecttype::none, 10, 1.0f, 0, 1);
	cards[23] = new Card("Jello Trampoline", "Deflects the next incoming projectile attack.", Card::cardtype::trap, item::combattype::projectile, Card::effecttype::reflect_projectile, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1);

	// ENEMY -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	cards[24] = new Card("Ferīre", "They deal damage.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[25] = new Card("Enhance", "They enhance their attacks for a turn.", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::damage_multiplier, Card::effecttype::none, Card::effecttype::none, 0, 1.5f, 0, 1); //only for gunman and grim
	//gunman
	cards[26] = new Card("Death Blossom", "They deal damage, and lower your defense by 2.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::deal_damage, Card::effecttype::lower_defense, Card::effecttype::none, 2, 0.5f, 1, 0);
	cards[27] = new Card("Bullseye", "They fire a bullet that penetrates your defense.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::deal_damage, Card::effecttype::ignore_defense, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[28] = new Card("Reloading...", "They increase their projectile defense by 3.", Card::cardtype::defense, item::combattype::projectile, Card::effecttype::increase_defense, Card::effecttype::none, Card::effecttype::none, 3, 1.0f, 0, 0);
	//grim
	cards[29] = new Card("Radial Slash", "They slash at you twice, reducing your defense by 3 with each hit.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::lower_defense, Card::effecttype::none, 3, 1.0f, 2, 0);
	cards[30] = new Card("	Burn In Despair!", "They despise how healthy you are. Deals 25% of current health as damage.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::hp_based_damage, Card::effecttype::none, Card::effecttype::none, 0, 0.25f, 1, 0);
	cards[31] = new Card("Grievance", "They grieve (maybe for your loss), for a turn, unable to attack. They then raise their attack and defense by 2.", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::increase_attack, Card::effecttype::cannot_attack, 2, 1.0f, 0, 1);
	//trickster
	cards[32] = new Card("Hipnotizēt", "They put you in a trance, making you unable to attack for a turn, while also dealing damage over two turns.", Card::cardtype::attack, item::combattype::flexible, Card::effecttype::hypnotism, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 2);
	cards[33] = new Card("Burvju Gredzens", "They summon a magic ring, giving them a temporary defense boost, and a 25% chance to reflect projectiles.", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::chance_reflect_projectile, Card::effecttype::none, 5, 1.0f, 0, 2);
	cards[34] = new Card("Ilūzija", "You're under an illusion. Is anything real? Is this card real?", Card::cardtype::hybrid, item::combattype::none, Card::effecttype::illusioned, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 1); //gives player the illusioned state (trickster -5 both defense)
	cards[35] = new Card("Ilūzija", "You're under an illusion. Is anything real? Is this card real?", Card::cardtype::trap, item::combattype::none, Card::effecttype::reflect_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1); //reflects all damage next turn
	cards[36] = new Card("Nodevība", "Watch closely... Too late! They deal massive damage while you're illusioned, ignoring your defense. I wonder when that happened...", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::ignore_defense, Card::effecttype::none, 0, 1.5f, 1, 0); //if not illusioned, shows as Ferīre
	//survivor phase 1
	cards[37] = new Card("Kinetic Strike", "They strike you, dealing damage and taunting you.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::taunted, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[38] = new Card("Horixon Valor", "They are fueled by this duel. +3 defense.", Card::cardtype::defense, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::none, Card::effecttype::none, 3, 1.0f, 0, 0);
	cards[39] = new Card("Tharos", "Increases attack by 7 for one turn.", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::increase_attack, Card::effecttype::none, Card::effecttype::none, 7, 1.0f, 0, 1);
	cards[40] = new Card("Unwilling", "Whatever happens, they will never budge. If you use at least 2 attack cards next turn, they negate both cards' effects.", Card::cardtype::trap, item::combattype::none, Card::effecttype::negate_attack_card, Card::effecttype::none, Card::effecttype::none, 2, 1.0f, 0, 1);
	//survivor phase 2
	cards[41] = new Card("Kinetic Blast", "Have a taste of your own medicine. They deal damage equal to half your melee damage and half their own damage.", Card::cardtype::attack, item::combattype::projectile, Card::effecttype::kinetic_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0);
	cards[42] = new Card("Bliss, On The Horizon's Edge", "They are at peace. +5 defense, +20 shield.", Card::cardtype::defense, item::combattype::flexible, Card::effecttype::increase_defense, Card::effecttype::shield, Card::effecttype::none, 5, 1.0f, 0, 0);
	cards[43] = new Card("Tharos: Reprise", "Increases attack by 10 for one turn.", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::increase_attack, Card::effecttype::none, Card::effecttype::none, 10, 1.0f, 0, 1);
	cards[44] = new Card("Determination", "Despite everything, they're still them. If you use at least 2 attack cards next turn, they negate both cards' effects and increase defense by 2.", Card::cardtype::trap, item::combattype::none, Card::effecttype::negate_attack_card, Card::effecttype::increase_defense, Card::effecttype::none, 2, 1.0f, 0, 1);
	cards[45] = new Card("Final Test", "You're about to leave. Aren't you happy?", Card::cardtype::hybrid, item::combattype::flexible, Card::effecttype::finaltest_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 1, 0); //under 5 hp, leave player at 1hp, and drop defense to -100
	//01
	cards[46] = new Card("Fuerza", "Power. Isn't this what you wanted? He deals massive damage, ignoring any shields.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::ignore_shield, Card::effecttype::none, 0, 1.5f, 1, 0);
	cards[47] = new Card("Meteor Hammer", "Feel his wrath.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::deal_damage, Card::effecttype::none, Card::effecttype::none, 0, 2.0f, 1, 0);
	cards[48] = new Card("Retribution", "He will make you pay for your sins. Reflects 25% damage for the next 3 turns.", Card::cardtype::hybrid, item::combattype::melee, Card::effecttype::reflect_damage, Card::effecttype::none, Card::effecttype::none, 0, 0.25f, 0, 3);
	cards[49] = new Card("Feral Fury", "This is what you made. Are you happy? He deals damage based on your current health.", Card::cardtype::attack, item::combattype::melee, Card::effecttype::hp_scaled_damage, Card::effecttype::none, Card::effecttype::none, 0, 1.0f, 0, 1); //at 100 health, 2x damage. At 50, 1x, At 25, 0.5x
}

CardDatabase::~CardDatabase() {
}

Card* CardDatabase::getcard(int index) {
	return cards[index];
}
