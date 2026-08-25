#include "BattleManager.h"
#include <iostream>
#include <conio.h>
BattleManager::BattleManager(Player* player, Enemy* enemy) {
	currentenemy = enemy;
	currentplayer = player;

	playermeleeattackbonus = 0;
	playerprojectileattackbonus = 0;
	playermeleedefensebonus = 0;
	playerprojectiledefensebonus = 0;
	playershield = 0;
	turn = 0;

	playerdamagemultiplier = 1.0f;
	enemydamagemultiplier = 1.0f;

	playernegateattacktrap = 0;
	playernegatedefensetrap= 0;
	enemynegateattacktrap = 0;
	enemynegatedefensetrap = 0;

	playerignoredefense = false;
	enemyignoredefense = false;
	playerignoreshield = false;
	enemyignoreshield = false;
	playermeleecountertrap = false;
	enemymeleecountertrap = false;
	playermirrortrap = false;

	playerreflectprojectile = false;
	enemyreflectprojectile = 0;

	enemymeleeattackbonus = 0;
	enemyprojectileattackbonus = 0;
	enemymeleedefensebonus = 0;
	enemyprojectiledefensebonus = 0;
	enemyshield = 0;

	playerskip = false;
	enemyskip = false;
}

void BattleManager::StartBattle() {
	currentplayer->builddeck(database);
	currentenemy->builddeck(database);
	for (int i = 0; i < 4; i++) {
		currentplayer->getdeck()->drawcard();
	}
	for (int i = 0; i < 4; i++) {
		currentenemy->getdeck()->drawcard();
	}
	//while (currentplayer->isalive() && currentenemy->isalive()) {
	//	PlayerTurn();
	//	if (!currentenemy->isalive()) {
	//		std::cout << "Enemy defeated!" << std::endl;
	//	}
	//	else if (!currentplayer->isalive()) {
	//		std::cout << "Player defeated!" << std::endl;
	//	}
	//	else {
	//		EnemyTurn();
	//		if (!currentplayer->isalive()) {
	//			std::cout << "Player defeated!" << std::endl;
	//		}
	//		else if (!currentenemy->isalive()) {
	//			std::cout << "Enemy defeated!" << std::endl;
	//		}
	//	}
	//}
}

void BattleManager::displaybattle(who turn, bool showboard) {
	system("cls");

	int enemyhp = currentenemy->gethp();

	if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::SURVIVOR &&
		currentenemy->getsurvivorphase2() == false) {
		enemyhp -= 100;
	}

	std::cout << "============================================" << std::endl;
	std::cout << "                   BATTLE" << std::endl;
	std::cout << "============================================" << std::endl;

	std::cout << "Enemy HP: " << enemyhp << "/100" << std::endl;
	displayenemyeffects();

	std::cout << std::endl;

	if (showboard == true) {
		displayboard(turn);
	}

	std::cout << std::endl;

	std::cout << "Player HP: " << currentplayer->gethp() << "/100" << std::endl;
	displayplayereffects();

	std::cout << "============================================" << std::endl;
}

void BattleManager::displayplayereffects() {
	std::cout << "Your effects: ";

	if (playernegateattacktrap > 0) {
		std::cout << "[Stay Alert!] ";
	}

	if (playernegatedefensetrap > 0) {
		std::cout << "[Watch!] ";
	}

	if (playermeleecountertrap == true) {
		std::cout << "[Rat Trap] ";
	}

	if (playermirrortrap == true) {
		std::cout << "[Mirror Trap] ";
	}

	if (playerreflectprojectile == true) {
		std::cout << "[Jello Trampoline] ";
	}

	std::cout << std::endl;
}

void BattleManager::displayenemyeffects() {
	std::cout << "Enemy effects: ";

	int trapcount = 0;

	if (enemynegateattacktrap > 0) {
		trapcount++;
	}

	if (enemynegatedefensetrap > 0) {
		trapcount++;
	}

	if (enemymeleecountertrap == true) {
		trapcount++;
	}

	for (int i = 0; i < trapcount; i++) {
		std::cout << "[??? Trap] ";
	}

	if (enemyreflectprojectile > 0) {
		std::cout << "[Magic Ring: " << enemyreflectprojectile << " turns] ";
	}

	std::cout << std::endl;
}

void BattleManager::displaymessage(std::string message) {

}

void BattleManager::displaycards(Card* cards[], int count) {
	for (int i = 0; i < count; i++) {
		std::cout << "+------------------+  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < count; i++) {
		std::cout << "| ";

		std::string name = cards[i]->getcardname();
		std::cout << name;

		for (int a = name.length(); a < 16; a++) {
			std::cout << " ";
		}

		std::cout << "|  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < count; i++) {
		std::cout << "+------------------+  ";
	}
	std::cout << std::endl;
}

void BattleManager::displayboard(who user) {
	std::cout << "ENEMY" << std::endl;

	if (user == who::enemy) {
		displaycards(enemyselectedcards, enemyselectedcount);
	}

	std::cout << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::cout << "YOU" << std::endl;

	if (user == who::player) {
		displaycards(selectedcards, selectedcount);
	}
}

int BattleManager::findcardtype(Card::cardtype type, bool selected[]) {
	for (int i = 0; i < currentenemy->getdeck()->gethandcount(); i++) {
		Card* card = currentenemy->getdeck()->getcardfromhand(i);

		if (card->gettype() == type && selected[i] == false) {
			return i;
		}
	}
	return -1;
}

void BattleManager::PlayerTurn() {
	for (int i = 0; i < 2; i++) {
		currentplayer->getdeck()->drawcard();
	}
	selectedcount = 0;
	for (int i = 0; i < 3; i++) {
		selectedcards[i] = nullptr;
	}
	for (int i = 0; i < 12; i++) {
		selected[i] = false;
	}
	int cursor = 0;
	bool selecting = true;
	while (selecting) {
		displaybattle(who::player, false);
		std::cout << std::endl;
		for (int i = 0; i < currentplayer->getdeck()->gethandcount(); i++) {
			Card* card = currentplayer->getdeck()->getcardfromhand(i);
			if (i == cursor) {
				if (selected[cursor] == true) {
					std::cout << "> * " << i + 1 << ": " << card->getcardname() << std::endl;
				}
				else {
					std::cout << ">   " << i + 1 << ": " << card->getcardname() << std::endl;
				}
			}
			else {
				if (selected[i] == true) {
					std::cout << "  * " << i + 1 << ": " << card->getcardname() << std::endl;
				}
				else {
					std::cout << "    " << i + 1 << ": " << card->getcardname() << std::endl;
				}
			}
		}
		std::cout << std::endl;
		std::cout << "Selected: " << selectedcount << "/3" << std::endl;
		std::cout << "W/S: Up/Down  A/D: Deselect/Select  I: Card information  Enter: Confirm Cards" << std::endl;
		char input = _getch();
		if (input == 'w' || input == 'W') {
			if (cursor > 0) {
				cursor--;
			}
		}
		else if (input == 's' || input == 'S') {
			if (cursor < currentplayer->getdeck()->gethandcount() - 1) {
				cursor++;
			}
		}
		else if (input == 'd' || input == 'D') {
			if (selectedcount < 3 && selected[cursor] == false) {
				selected[cursor] = true;
				selectedcards[selectedcount] = currentplayer->getdeck()->getcardfromhand(cursor);
				selectedcount++;
			}
		}
		else if (input == 'a' || input == 'A') {
			if (selected[cursor] == true) {
				Card* cardtoremove = currentplayer->getdeck()->getcardfromhand(cursor);
				for (int i = 0; i < selectedcount; i++) {
					if (selectedcards[i] == cardtoremove) {
						for (int a = i; a < selectedcount - 1; a++) {
							selectedcards[a] = selectedcards[a + 1];
						}
						selectedcards[selectedcount - 1] = nullptr;
					}
				}
				selected[cursor] = false;
				selectedcount--;
			}
		}
		else if (input == 'i' || input == 'I') {
			system("cls");
			Card* card = currentplayer->getdeck()->getcardfromhand(cursor);
			std::cout << card->getcardname() << ": " << std::endl;
			std::cout << card->getcarddescription() << std::endl;
			std::cout << "Press any key to return. Don't keep them waiting." << std::endl;
			_getch();
		}
		else if (input == 13) {
			if (selectedcount > 0) {
				selecting = false;
			}
		}
	}

	displaybattle(who::player, true);

	/*for (int i = 0; i < selectedcount; i++) {
		playcard(selectedcards[i], who::player);
	}

	for (int i = currentplayer->getdeck()->gethandcount() - 1; i >= 0; i--) {
		if (selected[i] == true) {
			currentplayer->getdeck()->discardcard(i);
		}
	}
	checksurvivorphase();*/
}

void BattleManager::EnemyTurn() {
	for (int i = 0; i < 2; i++) {
		currentenemy->getdeck()->drawcard();
	}
	int cardstoplay = (rand() % 3) + 1;
	if (cardstoplay > currentenemy->getdeck()->gethandcount()) {
		cardstoplay = currentenemy->getdeck()->gethandcount();
	}
	enemyselectedcount = 0;
	for (int i = 0; i < 3; i++) {
		enemyselectedcards[i] = nullptr;
	}
	for (int i = 0; i < 12; i++) {
		enemyselected[i] = false;
	}
	while (enemyselectedcount < cardstoplay) {
		Card::cardtype preferred;

		if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::TRICKSTER) {
			int chance = rand() % 100;
			if (chance < 40) {
				preferred = Card::cardtype::attack;

			}
			else if (chance < 70) {
				preferred = Card::cardtype::hybrid;
			}
			else {
				preferred = Card::cardtype::trap;
			}
		}
		else if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::GRIM) {
			if (currentenemy->gethp() <= 30) {
				int chance = rand() % 100;
				if (chance < 60) {
					preferred = Card::cardtype::attack;
				}
				else {
					preferred = Card::cardtype::hybrid;
				}
			}
			else {
				int chance = rand() % 100;
				if (chance < 50) {
					preferred = Card::cardtype::attack;
				}
				else {
					preferred = Card::cardtype::hybrid;
				}
			}
		}
		else if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::GUNMAN) {
			if (currentenemy->gethp() <= 30) {
				int chance = rand() % 100;
				if (chance < 25) {
					preferred = Card::cardtype::attack;
				}
				else if (chance < 50) {
					preferred = Card::cardtype::hybrid;
				}
				else if (chance < 70) {
					preferred = Card::cardtype::defense;
				}
				else {
					preferred = Card::cardtype::trap;
				}
			}
			else {
				int chance = rand() % 100;
				if (chance < 20) {
					preferred = Card::cardtype::attack;
				}
				else if (chance < 40) {
					preferred = Card::cardtype::hybrid;
				}
				else if (chance < 70) {
					preferred = Card::cardtype::defense;
				}
				else {
					preferred = Card::cardtype::trap;
				}
			}
		}
		else if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::SURVIVOR) {
			int chance = rand() % 100;
			if (currentenemy->getsurvivorphase2() == true) {
				if (currentenemy->gethp() <= 40) {
					if (chance < 40) {
						preferred = Card::cardtype::attack;
					}
					else if (chance < 65) {
						preferred = Card::cardtype::hybrid;
					}
					else if (chance < 85) {
						preferred = Card::cardtype::defense;
					}
					else {
						preferred = Card::cardtype::trap;
					}
				}
				else {
					if (chance < 30) {
						preferred = Card::cardtype::attack;
					}
					else if (chance < 60) {
						preferred = Card::cardtype::hybrid;
					}
					else if (chance < 80) {
						preferred = Card::cardtype::defense;
					}
					else {
						preferred = Card::cardtype::trap;
					}
				}
			}
			else {
				if (currentenemy->gethp() <= 130 && currentenemy->gethp() >= 100) {
					if (chance < 20) {
						preferred = Card::cardtype::attack;
					}
					else if (chance < 40) {
						preferred = Card::cardtype::hybrid;
					}
					else if (chance < 80) {
						preferred = Card::cardtype::defense;
					}
					else {
						preferred = Card::cardtype::trap;
					}
				}
				else {
					if (chance < 25) {
						preferred = Card::cardtype::attack;
					}
					else if (chance < 50) {
						preferred = Card::cardtype::hybrid;
					}
					else if (chance < 80) {
						preferred = Card::cardtype::defense;
					}
					else {
						preferred = Card::cardtype::trap;
					}
				}
			}
		}
		else {
			int chance = rand() % 100;
			if (chance < 25) {
				preferred = Card::cardtype::attack;
			}
			else if (chance < 50) {
				preferred = Card::cardtype::hybrid;
			}
			else if (chance < 75) {
				preferred = Card::cardtype::defense;
			}
			else {
				preferred = Card::cardtype::trap;
			}
		}


		int index = findcardtype(preferred, enemyselected);

		if (index == -1) {
			for (int i = 0; i < currentenemy->getdeck()->gethandcount(); i++) {
				if (enemyselected[i] == false && index == -1) {
					index = i;
				}
			}
		}
		if (index != -1) {
			enemyselected[index] = true;
			enemyselectedcards[enemyselectedcount] = currentenemy->getdeck()->getcardfromhand(index);
			enemyselectedcount++;
		}
	}
}

void BattleManager::resolveturn() {
	bool playernegated[3] = { false, false, false };
	bool enemynegated[3] = { false, false, false };
	checktraps(selectedcards, selectedcount, playernegated, who::enemy);
	checktraps(enemyselectedcards, enemyselectedcount, enemynegated, who::player);
	for (int i = 0; i < selectedcount; i++) {
		if (!playernegated[i]) {
			playcard(selectedcards[i], who::player);
		}
	}
	for (int i = 0; i < enemyselectedcount; i++) {
		if (!enemynegated[i]) {
			playcard(enemyselectedcards[i], who::enemy);
		}
	}
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
				rawdamage = (damagedealt + playermeleeattackbonus) * card->getmultiplier() * playerdamagemultiplier;
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				damagedealt = currentplayer->getProjectileAttack();
				isProjectile = true;
				rawdamage = (damagedealt + playerprojectileattackbonus) * card->getmultiplier() * playerdamagemultiplier;
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::melee) {
					damagedealt = currentplayer->getMeleeAttack();
					rawdamage = (damagedealt + playermeleeattackbonus) * card->getmultiplier() * playerdamagemultiplier;
				}
				else if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::projectile) {
					damagedealt = currentplayer->getProjectileAttack();
					isProjectile = true;
					rawdamage = (damagedealt + playerprojectileattackbonus) * card->getmultiplier() * playerdamagemultiplier;
				}
			}
			int defense = 0;
			if (isProjectile) {
				defense = currentenemy->getProjectileDefense() + enemyprojectiledefensebonus;
			}
			else {
				defense = currentenemy->getMeleeDefense() + enemymeleedefensebonus;
			}
			int finaldamage = 0;
			if (playerignoredefense) {
				finaldamage = rawdamage;
			}
			else {
				finaldamage = calculateDamage(rawdamage, defense);
			}
			if (isProjectile && enemyreflectprojectile > 0) {
				int chance = rand() % 100;
				if (chance < 25) {
					currentplayer->takeDamage(finaldamage);
				}
				else {
					damageenemy(finaldamage);
				}
			}
			else {
				damageenemy(finaldamage);
			}
		}
		else {
			int damagedealt = 0;
			int rawdamage = 0;
			bool isProjectile = false;
			if (card->getcombatcategory() == item::combattype::melee) {
				damagedealt = currentenemy->getMeleeAttack();
				rawdamage = (damagedealt + enemymeleeattackbonus) * card->getmultiplier() * enemydamagemultiplier;
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				damagedealt = currentenemy->getProjectileAttack();
				isProjectile = true;
				rawdamage = (damagedealt + enemyprojectileattackbonus) * card->getmultiplier() * enemydamagemultiplier;
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentenemy->getMeleeAttack() >= currentenemy->getProjectileAttack()) {
					damagedealt = currentenemy->getMeleeAttack();
					rawdamage = (damagedealt + enemymeleeattackbonus) * card->getmultiplier() * enemydamagemultiplier;
				}
				else {
					damagedealt = currentenemy->getProjectileAttack();
					isProjectile = true;
					rawdamage = (damagedealt + enemyprojectileattackbonus) * card->getmultiplier() * enemydamagemultiplier;
				}
			}
			int defense = 0;
			if (isProjectile) {
				defense = currentplayer->getProjectileDefense() + playerprojectiledefensebonus;
			}
			else {
				defense = currentplayer->getMeleeDefense() + playermeleedefensebonus;
			}
			int finaldamage = 0;
			if (enemyignoredefense) {
				finaldamage = rawdamage;
			}
			else {
				finaldamage = calculateDamage(rawdamage, defense);
			}
			if (isProjectile && playerreflectprojectile == true) {
				damageenemy(finaldamage);
				playerreflectprojectile = false;
			}
			else {
				currentplayer->takeDamage(finaldamage);
			}
		}
	}

	if (effect == Card::effecttype::damage_multiplier) {
		if (user == who::player) {
			playerdamagemultiplier *= card->getmultiplier();
		}
		else {
			enemydamagemultiplier *= card->getmultiplier();
		}
	}

	if (effect == Card::effecttype::kinetic_damage) {
		int damagedealt = 0;
		int ene = ((currentenemy->getProjectileAttack() + enemyprojectileattackbonus) / 2);
		int rawdamage = (ene + (currentplayer->getMeleeDefense() / 2)) * card->getmultiplier();
		int defense = currentplayer->getProjectileDefense() + playerprojectiledefensebonus;
		int finaldamage = calculateDamage(rawdamage, defense);
		currentplayer->takeDamage(finaldamage);
	}

	if (effect == Card::effecttype::finaltest_damage) {
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
				if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::melee) {
					enemymeleedefensebonus -= card->getvalue();
				}
				else if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::projectile) {
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
			//else if (card->getcombatcategory() == item::combattype::flexible) {
			//	if (currentplayer->getarmor() == nullptr) {
			//		playermeleedefensebonus += card->getvalue();
			//		playerprojectiledefensebonus += card->getvalue();
			//	}
			//	else {
			//		if (currentplayer->
			//			getarmor()->getcombatcategory() == item::combattype::melee) {
			//			playermeleedefensebonus += (currentplayer->getMeleeDefense() / 2) + card->getvalue();
			//		}
			//		else if (currentplayer->getarmor()->getcombatcategory() == item::combattype::projectile) {
			//			playerprojectiledefensebonus += (currentplayer->getProjectileDefense() / 2) + card->getvalue();
			//		}
			//		else if (currentplayer->getarmor()->getcombatcategory() == item::combattype::none) {
			//			playermeleedefensebonus += (currentplayer->getMeleeDefense() / 2) + card->getvalue();
			//			playerprojectiledefensebonus += (currentplayer->getProjectileDefense() / 2) + card->getvalue();
			//		}
			//	}
			//}
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
		currentplayer->takeDamage(finaldamage);
	}

	if (effect == Card::effecttype::hp_scaled_damage) {
		int playercurrenthp = currentplayer->gethp();
		int rawdamage = 0;
		if (playercurrenthp <= currentplayer->getmaxhp() / 4) {
			rawdamage = 5;
		}
		else if (playercurrenthp <= currentplayer->getmaxhp() / 2) {
			rawdamage = 10;
		}
		else {
			rawdamage = 15;
		}
		int defense = currentplayer->getMeleeDefense() + playermeleedefensebonus;
		int finaldamage = calculateDamage(rawdamage, defense);
		currentplayer->takeDamage(finaldamage);
	}

	if (effect == Card::effecttype::negate_attack_card) {
		if (user == who::player) {
			playernegateattacktrap = card->getvalue();
		}
		else {
			enemynegateattacktrap = card->getvalue();
		}
	}

	if (effect == Card::effecttype::negate_defense_card) {
		if (user == who::player) {
			playernegatedefensetrap = card->getvalue();
		}
		else {
			enemynegatedefensetrap = card->getvalue();
		}
	}

	if (effect == Card::effecttype::ignore_defense) {
		if (user == who::player) {
			playerignoredefense = true;
		}
		else {
			enemyignoredefense = true;
		}
	}

	if (effect == Card::effecttype::ignore_shield) {
		if (user == who::player) {
			playerignoreshield = true;
		}
		else {
			enemyignoreshield = true;
		}
	}

	//skip_next_turn,

	//forced_skip,

	//lifesteal,
	//multishot_combo,
	//phalanxing,

	if (effect == Card::effecttype::melee_trigger_trap) {
		if (user == who::player) {
			playermeleecountertrap = true;
		}
		else {
			enemymeleecountertrap = true;
		}
	}

	if (effect == Card::effecttype::trap_counter) {
		playermirrortrap = true;
	}

	//prepare_upclose,
	//poison_tip,
	//skip_immunity,
	//cannot_attack,
	//defense_from_hp_lost,
	//shield,
	//projectile_to_melee,

	if (effect == Card::effecttype::reflect_projectile) {
		playerreflectprojectile = true;
	}

	if (effect == Card::effecttype::chance_reflect_projectile) {
		enemyreflectprojectile = card->getduration();
	}

	//reflect_damage,
	//hypnotism,
	//illusioned,
	//taunted,
	//heal_hp,
	//donation,
}

void BattleManager::checktraps(Card* attackercard[], int attackercount, bool negated[], who defender) {
	bool trapaffected = false;
	int attacknegationcount = 0;
	int defensenegationcount = 0;

	if (defender == who::player) {
		attacknegationcount = playernegateattacktrap;
		defensenegationcount = playernegatedefensetrap;
	}
	else {
		attacknegationcount = enemynegateattacktrap;
		defensenegationcount = enemynegatedefensetrap;
	}

	int attackcount = 0;
	int defensecount = 0;

	for (int i = 0; i < attackercount; i++) {
		if (attackercard[i]->gettype() == Card::cardtype::attack) {
			attackcount++;
		}
		else if (attackercard[i]->gettype() == Card::cardtype::defense) {
			defensecount++;
		}
	}

	if (attackcount >= 2 && attacknegationcount > 0) {
		for (int i = 0; i < attacknegationcount; i++) {
			int index = findrandomcardtype(attackercard, attackercount, Card::cardtype::attack, negated);
			if (index != -1) {
				negated[index] = true;
				trapaffected = true;
			}
		}
	}

	if (defensecount >= 2 && defensenegationcount > 0) {
		for (int i = 0; i < defensenegationcount; i++) {
			int index = findrandomcardtype(attackercard, attackercount, Card::cardtype::defense, negated);
			if (index != -1) {
				negated[index] = true;
				trapaffected = true;
			}
		}
	}

	if (defender == who::player) {
		playernegateattacktrap = 0;
		playernegatedefensetrap = 0;
	}
	else {
		enemynegateattacktrap = 0;
		enemynegatedefensetrap = 0;
	}

	//rat trap
	bool meleedamage = false;

	for (int i = 0; i < attackercount; i++) {
		if (negated[i] == false && haseffect(attackercard[i], Card::effecttype::deal_damage)) {
			if (attackercard[i]->getcombatcategory() == item::combattype::melee) {
				meleedamage = true;
			}
			else if (attackercard[i]->getcombatcategory() == item::combattype::flexible) {
				if (defender == who::enemy) {
					if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::melee) {
						meleedamage = true;
					}
				}
				else {
					if (currentenemy->getMeleeAttack() >= currentenemy->getProjectileAttack()) {
						meleedamage = true;
					}
				}
			}
		}
	}
	if (meleedamage == true) {
		if (defender == who::player && playermeleecountertrap == true) {
			int rawdamage = currentplayer->getMeleeAttack() / 2;
			int defense = currentenemy->getMeleeDefense() + enemymeleedefensebonus;
			int finaldamage = calculateDamage(rawdamage, defense);

			damageenemy(finaldamage);
			trapaffected = true;
		}
		else if (defender == who::enemy && enemymeleecountertrap == true) {
			int rawdamage = currentenemy->getMeleeAttack() / 2;
			int defense = currentplayer->getMeleeDefense() + playermeleedefensebonus;
			int finaldamage = calculateDamage(rawdamage, defense);

			currentplayer->takeDamage(finaldamage);
			trapaffected = true;
		}
	}
	if (defender == who::player) {
		playermeleecountertrap = false;
	}
	else {
		enemymeleecountertrap = false;
	}

	if (defender == who::player) {
		if (trapaffected == true && playermirrortrap == true) {
			enemyskip = true;
		}
		playermirrortrap = false;
	}
}

bool BattleManager::haseffect(Card* card, Card::effecttype effect) {
	for (int i = 0; i < 3; i++) {
		if (card->getcardeffect(i) == effect) {
			return true;
		}
	}

	return false;
}

int BattleManager::findrandomcardtype(Card* cards[], int count, Card::cardtype type, bool negated[]) {
	int available[3];
	int availablecount = 0;
	for (int i = 0; i < count; i++) {
		if (cards[i]->gettype() == type && negated[i] == false) {
			available[availablecount] = i;
			availablecount++;
		}
	}
	if (availablecount > 0) {
		int random = rand() % availablecount;
		return available[random];
	}

	return -1;
}

int BattleManager::calculateDamage(int rawdamage, int defense) {
	int finaldamage = rawdamage / (1 + defense / 10.0f);
	return finaldamage;
}

void BattleManager::damageenemy(int damage) {
	currentenemy->takeDamage(damage);
	if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::SURVIVOR && currentenemy->gethp() <= 100 && currentenemy->getsurvivorphase2() == false) {
			currentenemy->sethp(100);
	}
}

void BattleManager::checksurvivorphase() {
	if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::SURVIVOR && currentenemy->gethp() <= 100 && currentenemy->getsurvivorphase2() == false) {
		std::cout << "Impressive... I underestimated you. Well, then." << std::endl;
		system("pause");
		std::cout << "Let the real fun begin." << std::endl;
		currentenemy->setsurvivorphase2(true);
		currentenemy->sethp(100);
		currentenemy->builddeck(database);
		for (int i = 0; i < 6; i++) {
			currentenemy->getdeck()->drawcard();
		}
	}
}

//deal_damage,
//damage_multiplier,
//kinetic_damage,
//finaltest_damage,
//lower_defense,
//lower_own_defense,
//increase_defense,
//increase_attack,
//half_damage_next_turn,
//hp_based_damage,
//hp_scaled_damage,
//negate_attack_card,
//negate_defense_card,
//ignore_defense,
//ignore_shield,
//skip_next_turn,
//forced_skip,
//lifesteal,
//multishot_combo,
//phalanxing,
//melee_trigger_trap,
//trap_counter,
//prepare_upclose,
//poison_tip,
//skip_immunity,
//cannot_attack,
//defense_from_hp_lost,
//shield,
//projectile_to_melee,
//reflect_projectile,
//chance_reflect_projectile,
//reflect_damage,
//hypnotism,
//illusioned,
//taunted,
//heal_hp,
//donation,
//none