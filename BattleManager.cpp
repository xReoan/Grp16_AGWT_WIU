#include "BattleManager.h"
#include <iostream>
BattleManager::BattleManager(Player* player, Enemy* enemy) {
	currentenemy = enemy;
	currentplayer = player;

	playermeleeattackbonus = 0;
	playerprojectileattackbonus = 0;
	playermeleedefensebonus = 0;
	playerprojectileattackbonus = 0;
	playershield = 0;
	turn = 0;

	enemymeleeattackbonus = 0;
	enemyprojectileattackbonus = 0;
	enemymeleedefensebonus = 0;
	enemyprojectiledefensebonus = 0;
	enemyshield = 0;

	playerskip = false;
	enemyskip = false;
}

void BattleManager::StartBattle() {
	while (currentplayer->isalive() && currentenemy->isalive()) {
		PlayerTurn();
		if (!currentenemy->isalive()) {
			std::cout << "Enemy defeated!" << std::endl;
		}
		else if (!currentplayer->isalive()) {
			std::cout << "Player defeated!" << std::endl;
		}
		else {
			EnemyTurn();
			if (!currentplayer->isalive()) {
				std::cout << "Player defeated!" << std::endl;
			}
			else if (!currentenemy->isalive()) {
				std::cout << "Enemy defeated!" << std::endl;
			}
		}
	}
}

void BattleManager::PlayerTurn() {

}

void BattleManager::EnemyTurn() {

}

void BattleManager::playcard(Card* card, who user) {
	for (int i = 0; i < 3; i++) {
		Card::effecttype effect = card->getcardeffect(i);
		if (effect != Card::effecttype::none) {
			applyeffect(card, effect, user);
		}
	}
}

void BattleManager::applyeffect(Card* card, Card::effecttype effect, who user) {
	//strike and ferire
	if (effect == Card::effecttype::deal_damage) {
		if (user == who::player) {
			int damagedealt = 0;
			int rawdamage = 0;
			bool isProjectile = false;
			if (card->getcombatcategory() == item::combattype::melee) {
				damagedealt = currentplayer->getMeleeAttack();
				rawdamage = (damagedealt + playermeleeattackbonus) * card->getmultiplier();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				damagedealt = currentplayer->getProjectileAttack();
				isProjectile = true;
				rawdamage = (damagedealt + playerprojectileattackbonus) * card->getmultiplier();
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentplayer->getweapon()->getcombatcategory() == item::combattype::melee) {
					damagedealt = currentplayer->getMeleeAttack();
					rawdamage = (damagedealt + playermeleeattackbonus) * card->getmultiplier();
				}
				else if (currentplayer->getweapon()->getcombatcategory() == item::combattype::projectile) {
					damagedealt = currentplayer->getProjectileAttack();
					isProjectile = true;
					rawdamage = (damagedealt + playerprojectileattackbonus) * card->getmultiplier();
				}
			}
			int defense = 0;
			if (isProjectile) {
				defense = currentenemy->getProjectileDefense() + enemyprojectiledefensebonus;
			}
			else {
				defense = currentenemy->getMeleeDefense() + enemymeleedefensebonus;
			}
			int finaldamage = calculateDamage(rawdamage, defense);
			currentenemy->takeDamage(finaldamage);
		}
		else {
			int damagedealt = 0;
			int rawdamage = 0;
			bool isProjectile = false;
			if (card->getcombatcategory() == item::combattype::melee) {
				damagedealt = currentenemy->getMeleeAttack();
				rawdamage = (damagedealt + enemymeleeattackbonus) * card->getmultiplier();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				damagedealt = currentenemy->getProjectileAttack();
				isProjectile = true;
				rawdamage = (damagedealt + enemyprojectileattackbonus) * card->getmultiplier();
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentenemy->getMeleeAttack() >= currentenemy->getProjectileAttack()) {
					damagedealt = currentenemy->getMeleeAttack();
					rawdamage = (damagedealt + enemymeleeattackbonus) * card->getmultiplier();
				}
				else {
					damagedealt = currentenemy->getProjectileAttack();
					isProjectile = true;
					rawdamage = (damagedealt + enemyprojectileattackbonus) * card->getmultiplier();
				}
			}
			int defense = 0;
			if (isProjectile) {
				defense = currentplayer->getProjectileDefense() + playerprojectiledefensebonus;
			}
			else {
				defense = currentplayer->getMeleeDefense() + playermeleedefensebonus;
			}
			int finaldamage = calculateDamage(rawdamage, defense);
			currentplayer->takeDamage(finaldamage);
		}
	}

	//damage muliplier here

	if (effect == Card::effecttype::kinetic_damage) {
		int damagedealt = 0;
		damagedealt = (currentenemy->getProjectileAttack() / 2) + (currentplayer->getMeleeAttack() / 2);
		bool isProjectile = true;
		int ene = (damagedealt + enemyprojectileattackbonus) / 2;
		int pla = (damagedealt + playerprojectileattackbonus) / 2;
		int rawdamage = (ene + pla) * card->getmultiplier();
		int defense = currentplayer->getProjectileDefense() + playerprojectiledefensebonus;
		int finaldamage = calculateDamage(rawdamage, defense);
		currentplayer->takeDamage(finaldamage);
	}

	if (effect == Card::effecttype::finaltest_damage) {
		bool isProjectile = false;
		int finaldamage = currentplayer->gethp() - 1;
		currentplayer->takeDamage(finaldamage);
	}
	
	if (effect == Card::effecttype::lower_defense) {
		if (user == who::player) {
			if (card->getcombatcategory() == item::combattype::melee) {
				enemymeleedefensebonus -= card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				enemyprojectiledefensebonus -= card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentplayer->getweapon()->getcombatcategory() == item::combattype::melee) {
					enemymeleedefensebonus -= card->getvalue();
				}
				else if (currentplayer->getweapon()->getcombatcategory() == item::combattype::projectile) {
					enemyprojectiledefensebonus -= card->getvalue();
				}
			}
		}
		else {
			if (card->getcombatcategory() == item::combattype::melee) {
				playermeleedefensebonus -= card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				playerprojectiledefensebonus -= card->getvalue();
			}
		}
	}

	if (effect == Card::effecttype::lower_own_defense) {
		playermeleedefensebonus -= card->getvalue();
		playerprojectiledefensebonus -= card->getvalue();
	}
	
	if (effect == Card::effecttype::increase_defense) {
		if (user == who::player) {
			if (card->getcombatcategory() == item::combattype::melee) {
				playermeleedefensebonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				playerprojectiledefensebonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentplayer->getarmor() == nullptr) {
					playermeleedefensebonus += card->getvalue();
					playerprojectiledefensebonus += card->getvalue();
				}
				else {
					if (currentplayer->getarmor()->getcombatcategory() == item::combattype::melee) {
						playermeleedefensebonus += (currentplayer->getMeleeDefense() / 2) + card->getvalue();
					}
					else if (currentplayer->getarmor()->getcombatcategory() == item::combattype::projectile) {
						playerprojectiledefensebonus += (currentplayer->getProjectileDefense() / 2) + card->getvalue();
					}
					else if (currentplayer->getarmor()->getcombatcategory() == item::combattype::none) {
						playermeleedefensebonus += (currentplayer->getMeleeDefense() / 2) + card->getvalue();
						playerprojectiledefensebonus += (currentplayer->getProjectileDefense() / 2) + card->getvalue();
					}
				}
			}
		}
		else {
			if (card->getcombatcategory() == item::combattype::melee) {
				enemymeleedefensebonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				enemyprojectiledefensebonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				enemymeleedefensebonus += card->getvalue();
				enemyprojectiledefensebonus += card->getvalue();
			}
		}
	}

	if (effect == Card::effecttype::increase_attack) {
		if (user == who::player) {
			if (card->getcombatcategory() == item::combattype::melee) {
				playermeleeattackbonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				playerprojectileattackbonus += card->getvalue();
			}
		}
		else {
			if (card->getcombatcategory() == item::combattype::melee) {
				enemymeleeattackbonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				enemyprojectileattackbonus += card->getvalue();
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				enemymeleeattackbonus += card->getvalue();
				enemyprojectileattackbonus += card->getvalue();
			}
		}
	}

	//	half_damage_next_turn here

	if (effect == Card::effecttype::hp_based_damage) {
		int finaldamage = currentplayer->gethp() * card->getmultiplier();
		bool isProjectile = false;
		currentplayer->takeDamage(finaldamage);
	}

	//	hp_scaled_damage here

}

int BattleManager::calculateDamage(int rawdamage, int defense) {
	int finaldamage = rawdamage / (1 + defense / 10.0f);
	return finaldamage;
}

//	deal_damage,
//	damage_multiplier,
//	kinetic_damage,
//	finaltest_damage,
//	lower_defense,
//	lower_own_defense,
//	increase_defense,
//	increase_attack,
//	half_damage_next_turn,
//	hp_based_damage,
//	hp_scaled_damage,
//	negate_attack_card,
//	negate_defense_card,
//	ignore_defense,
//	ignore_shield,
//	skip_next_turn,
//	forced_skip,
//	lifesteal,
//	multishot_combo,
//	phalanxing,
//	melee_trigger_trap,
//	trap_counter,
//	prepare_upclose,
//	poison_tip,
//	skip_immunity,
//	cannot_attack,
//	defense_from_hp_lost,
//	shield,
//	projectile_to_melee,
//	reflect_projectile,
//	chance_reflect_projectile,
//	reflect_damage,
//	hypnotism,
//	illusioned,
//	taunted,
//	none