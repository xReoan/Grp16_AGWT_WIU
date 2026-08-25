#include "BattleManager.h"
#include <iostream>
#include <conio.h>
BattleManager::BattleManager(Player* player, Enemy* enemy, CardDatabase* database) {
	currentenemy = enemy;
	currentplayer = player;
	this->database = database;

	for (int i = 0; i < 20; i++) {
		timedstats[i].stat = nullptr;
		timedstats[i].amount = 0;
		timedstats[i].turns = 0;
		timedstats[i].active = false;
	}

	playermeleeattackbonus = 0;
	playerprojectileattackbonus = 0;
	playermeleedefensebonus = 0;
	playerprojectiledefensebonus = 0;
	playershield = 0;
	enemymeleeattackbonus = 0;
	enemyprojectileattackbonus = 0;
	enemymeleedefensebonus = 0;
	enemyprojectiledefensebonus = 0;
	enemyshield = 0;

	playerdamagemultiplier = 1.0f;
	enemydamagemultiplier = 1.0f;

	playernegateattacktrap = 0;
	playernegatedefensetrap= 0;
	enemynegateattacktrap = 0;

	playerignoredefense = false;
	enemyignoredefense = false;
	enemyignoreshield = false;
	meleecountertrap = false;
	playermirrortrap = false;
	playerhalfmelee = false;
	playerhalfdamage = false;

	playercannotattack = false;
	enemycannotattack = false;

	playerillusioned = false;
	enemyreflectdamagemultiplier = 1.0f;
	enemyreflectdamageturns = 0;

	playertaunted = false;

	enemyreflectdamage = false;
	playerreflectprojectile = false;
	enemyreflectprojectile = 0;

	playerprojectiletomelee = false;

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
	while (currentplayer->isalive() && currentenemy->isalive()) {
		if (playerskip == false) {
			PlayerTurn();
		}
		else {
			playerskip = false;
			selectedcount = 0;
			for (int i = 0; i < 3; i++) {
				selectedcards[i] = nullptr;
			}
		}
		if (enemyskip == false) {
			EnemyTurn();
		}
		else {
			enemyskip = false;
			enemyselectedcount = 0;
			for (int i = 0; i < 3; i++) {
				enemyselectedcards[i] = nullptr;
			}
		}
		resolveturn();
		discardplayedcards();
		checksurvivorphase();
		updateeffects();
	}
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

	if (meleecountertrap == true) {
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

	for (int i = 0; i < trapcount; i++) {
		std::cout << "[??? Trap] ";
	}

	if (enemyreflectprojectile > 0) {
		std::cout << "[Magic Ring: " << enemyreflectprojectile << " turns] ";
	}

	std::cout << std::endl;
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
		std::cout << "W/S: Up/Down  A/D: Deselect/Select  I: Card information  Q: Skip Turn  Enter: Confirm Cards" << std::endl;
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
			Card* card = currentplayer->getdeck()->getcardfromhand(cursor);
			if (playercannotattack == true && card->gettype() == Card::cardtype::attack) {
				selected[cursor] = false;
			}
			else if (playertaunted == true && card->gettype() != Card::cardtype::attack) {
				selected[cursor] = false;
			}
			else if (selectedcount < 3 && selected[cursor] == false) {
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
		else if (input == 'q' || input == 'Q') {
			char choice;
			std::cout << "Are you sure you want to skip your turn? (Y/N)" << std::endl;
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') {
				selecting = false;
				selectedcount = 0;
			}
			if (choice == 'n' || choice == 'N') {
				selecting = true;
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
	int availablecards = 0;

	for (int i = 0; i < currentenemy->getdeck()->gethandcount(); i++) {
		Card* card = currentenemy->getdeck()->getcardfromhand(i);
		if (enemycannotattack == false || card->gettype() != Card::cardtype::attack) {
			availablecards++;
		}
	}
	if (cardstoplay > availablecards) {
		cardstoplay = availablecards;
	}

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

		if (enemycannotattack == true && preferred == Card::cardtype::attack) {
			preferred = Card::cardtype::hybrid;
		}

		int index = findcardtype(preferred, enemyselected);

		if (index == -1) {
			for (int i = 0; i < currentenemy->getdeck()->gethandcount(); i++) {
				Card* card = currentenemy->getdeck()->getcardfromhand(i);
				if (enemyselected[i] == false && index == -1 && !(enemycannotattack == true && card->gettype() == Card::cardtype::attack)) {
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
	bool hasmetalpiercer = false;
	bool hasattackcard = false;

	for (int i = 0; i < selectedcount; i++) {
		if (selectedcards[i]->getcardname() == "Metal Piercer") {
			hasmetalpiercer = true;
		}

		if (selectedcards[i]->gettype() == Card::cardtype::attack) {
			hasattackcard = true;
		}
	}
	if (hasmetalpiercer == true && hasattackcard == true) {
		playerignoredefense = true;
	}
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

	playerignoredefense = false;
	enemyignoredefense = false;
	enemyignoreshield = false;
}

void BattleManager::playcard(Card* card, who user) {
	if (user == who::player) {
		displaymessage("You used " + card->getcardname() + "!");
	}
	else {
		displaymessage(currentenemy->getname() + " used " + card->getcardname() + "!");
	}
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
			int hits = card->gethits();
			if (hits <= 0) {
				hits = 1;
			}
			int oldhp = currentenemy->gethp();
			bool fullreflect = false;
			for (int i = 0; i < hits; i++) {
				if (isProjectile && enemyreflectprojectile > 0) {
					int chance = rand() % 100;

					if (chance < 25) {
						damageplayer(finaldamage);
					}
					else {
						damageenemy(finaldamage);
					}
				}
				else if (enemyreflectdamage == true) {
					int reflecteddamage = finaldamage * enemyreflectdamagemultiplier;
					damageplayer(reflecteddamage);

					if (enemyreflectdamagemultiplier >= 1.0f) {
						fullreflect = true;
					}
					else {
						damageenemy(finaldamage);
					}
				}
				else {
					damageenemy(finaldamage);
				}
			}

			if (fullreflect == true) {
				enemyreflectdamage = false;
				enemyreflectdamageturns = 0;
			}

			playerlastdamage = oldhp - currentenemy->gethp();

			if (playerillusioned == true && playerlastdamage >= 7) {
				playerillusioned = false;
				enemymeleedefensebonus += 5;
				enemyprojectiledefensebonus += 5;
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
			int hits = card->gethits();
			if (hits <= 0) {
				hits = 1;
			}
			int oldhp = currentplayer->gethp();

			for (int i = 0; i < hits; i++) {
				if (isProjectile) {
					if (playerprojectiletomelee == true) {
						defense = currentplayer->getMeleeDefense() + playermeleedefensebonus;
						playerprojectiletomelee = false;
					}
					else {
						defense = currentplayer->getProjectileDefense() + playerprojectiledefensebonus;
					}
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
				if (playerhalfmelee == true && isProjectile == false) {
					finaldamage *= 0.5f;
					playerhalfmelee = false;
				}
				if (playerhalfdamage == true) {
					finaldamage *= 0.5f;
					playerhalfdamage = false;
				}
				if (isProjectile && playerreflectprojectile == true) {
					damageenemy(finaldamage);
					playerreflectprojectile = false;
				}
				else {
					damageplayer(finaldamage);
				}
				if (card->getcardname() == "Nodevība" && playerillusioned == true) {
					playerillusioned = false;
					enemymeleedefensebonus += 5;
					enemyprojectiledefensebonus += 5;
				}
			}
		}
	}

	if (effect == Card::effecttype::damage_multiplier) {
		if (user == who::player) {
			if (playerdonation == true) {
				enemydamagemultiplier *= card->getmultiplier();
				enemydamagemultiplierturns = card->getduration();
			}
			else {
				playerdamagemultiplier *= card->getmultiplier();
				playerdamagemultiplierturns = card->getduration();
			}
		}
		else {
			enemydamagemultiplier *= card->getmultiplier();
			enemydamagemultiplierturns = card->getduration();
		}
	}

	if (effect == Card::effecttype::kinetic_damage) {
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
		if (card->getcardname() == "Metal Piercer") {
			bool hasattackcard = false;
			for (int i = 0; i < selectedcount; i++) {
				if (selectedcards[i] != card &&
					selectedcards[i]->gettype() == Card::cardtype::attack) {
					hasattackcard = true;
				}
			}
			if (hasattackcard == false) {
				addtimedstat(&enemymeleedefensebonus, -card->getvalue(), card->getduration());
			}
		}
		else {
			if (user == who::player) {
				if (card->getcombatcategory() == item::combattype::melee) {
					addtimedstat(&enemymeleedefensebonus, -card->getvalue(), card->getduration());
				}
				else if (card->getcombatcategory() == item::combattype::projectile) {
					addtimedstat(&enemyprojectiledefensebonus, -card->getvalue(), card->getduration());
				}
				else if (card->getcombatcategory() == item::combattype::flexible) {
					if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::melee) {
						addtimedstat(&enemymeleedefensebonus, -card->getvalue(), card->getduration());
					}
					else if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::projectile) {
						addtimedstat(&enemyprojectiledefensebonus, -card->getvalue(), card->getduration());
					}
				}
			}
			else {
				if (card->getcombatcategory() == item::combattype::melee) {
					addtimedstat(&playermeleedefensebonus, -card->getvalue(), card->getduration());
				}
				else if (card->getcombatcategory() == item::combattype::projectile) {
					addtimedstat(&playerprojectiledefensebonus, -card->getvalue(), card->getduration());
				}
			}
		}
	}

	if (effect == Card::effecttype::lower_own_defense) {
		if (playerdonation == true) {
			addtimedstat(&enemymeleedefensebonus, -card->getvalue(), card->getduration());
			addtimedstat(&enemyprojectiledefensebonus, -card->getvalue(), card->getduration());
		}
		else {
			addtimedstat(&playermeleedefensebonus, -card->getvalue(), card->getduration());
			addtimedstat(&playerprojectiledefensebonus, -card->getvalue(), card->getduration());
		}
	}
	
	if (effect == Card::effecttype::increase_defense) {
		if (user == who::player) {
			if (card->getcombatcategory() == item::combattype::melee) {
				if (playerdonation == true) {
					addtimedstat(&enemymeleedefensebonus, card->getvalue(), card->getduration());
				}
				else {
					addtimedstat(&playermeleedefensebonus, card->getvalue(), card->getduration());
				}
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				if (playerdonation == true) {
					addtimedstat(&enemyprojectiledefensebonus, card->getvalue(), card->getduration());
				}
				else {
					addtimedstat(&playerprojectiledefensebonus, card->getvalue(), card->getduration());
				}
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentplayer->getequippedadvancedarmor() == nullptr) {
					if (currentplayer->getequippedbasicarmor() == nullptr) {
						if (playerdonation == true) {
							addtimedstat(&enemymeleedefensebonus, card->getvalue(), card->getduration());
							addtimedstat(&enemyprojectiledefensebonus, card->getvalue(), card->getduration());
						}
						else {
							addtimedstat(&playermeleedefensebonus, card->getvalue(), card->getduration());
							addtimedstat(&playerprojectiledefensebonus, card->getvalue(), card->getduration());
						}
					}
					else {
						if (currentplayer->getequippedbasicarmor()->getcombatcategory() == item::combattype::melee) {
							if (playerdonation == true) {
								addtimedstat(&enemymeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
							}
							else {
								addtimedstat(&playermeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
							}
						}
						else if (currentplayer->getequippedbasicarmor()->getcombatcategory() == item::combattype::projectile) {
							if (playerdonation == true) {
								addtimedstat(&enemyprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
							}
							else {
								addtimedstat(&playerprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
							}
						}
						else if (currentplayer->getequippedbasicarmor()->getcombatcategory() == item::combattype::none) {
							if (playerdonation == true) {
								addtimedstat(&enemymeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
								addtimedstat(&enemyprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
							}
							else {
								addtimedstat(&playermeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
								addtimedstat(&playerprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
							}
						}
					}
				}
				else {
					if (currentplayer->getequippedadvancedarmor()->getcombatcategory() == item::combattype::melee) {
						if (playerdonation == true) {
							addtimedstat(&enemymeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
						}
						else {
							addtimedstat(&playermeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
						}
					}
					else if (currentplayer->getequippedadvancedarmor()->getcombatcategory() == item::combattype::projectile) {
						if (playerdonation == true) {
							addtimedstat(&enemyprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
						}
						else {
							addtimedstat(&playerprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
						}
					}
					else if (currentplayer->getequippedadvancedarmor()->getcombatcategory() == item::combattype::none) {
						if (playerdonation == true) {
							addtimedstat(&enemymeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
							addtimedstat(&enemyprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
						}
						else {
							addtimedstat(&playermeleedefensebonus, (currentplayer->getMeleeDefense() / 2) + card->getvalue(), card->getduration());
							addtimedstat(&playerprojectiledefensebonus, (currentplayer->getProjectileDefense() / 2) + card->getvalue(), card->getduration());
						}
					}
				}
			}
		}
		else {
			if (card->getcombatcategory() == item::combattype::melee) {
				addtimedstat(&enemymeleedefensebonus, card->getvalue(), card->getduration());
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				addtimedstat(&enemyprojectiledefensebonus, card->getvalue(), card->getduration());
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				addtimedstat(&enemymeleedefensebonus, card->getvalue(), card->getduration());
				addtimedstat(&enemyprojectiledefensebonus, card->getvalue(), card->getduration());
			}
		}
	}

	if (effect == Card::effecttype::increase_attack) {
		if (card->getcombatcategory() == item::combattype::melee) {
			addtimedstat(&enemymeleeattackbonus, card->getvalue(), card->getduration());
		}
		else if (card->getcombatcategory() == item::combattype::projectile) {
			addtimedstat(&enemyprojectileattackbonus, card->getvalue(), card->getduration());
		}
		else if (card->getcombatcategory() == item::combattype::flexible) {
			addtimedstat(&enemymeleeattackbonus, card->getvalue(), card->getduration());
			addtimedstat(&enemyprojectileattackbonus, card->getvalue(), card->getduration());
		}
	}

	if (effect == Card::effecttype::half_damage_next_turn) {
		if (card->gettype() == Card::cardtype::hybrid) {
			playerhalfmelee = true;
		}
		else if (card->gettype() == Card::cardtype::defense) {
			playerhalfdamage = true;
		}
	}

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
		playernegatedefensetrap = card->getvalue();
	}

	if (effect == Card::effecttype::ignore_defense) {
		if (card->getcardname() == "Metal Piercer") {
			bool hasattackcard = false;
			for (int i = 0; i < selectedcount; i++) {
				if (selectedcards[i] != card && selectedcards[i]->gettype() == Card::cardtype::attack) {
					hasattackcard = true;
				}
			}
			if (hasattackcard == true) {
				playerignoredefense = true;
			}
		}
		else {
			if (user == who::player) {
				playerignoredefense = true;
			}
			else {
				enemyignoredefense = true;
			}
		}
	}

	if (effect == Card::effecttype::ignore_shield) {
		enemyignoreshield = true;
	}

	if (effect == Card::effecttype::skip_next_turn) {
		playerskip = true;
	}

	if (effect == Card::effecttype::skip_enemy_next_turn) {
		enemyskip = true;
	}

	if (effect == Card::effecttype::lifesteal) {
		int healing = playerlastdamage * card->getmultiplier();
		currentplayer->sethp(currentplayer->gethp() + healing);
		if (currentplayer->gethp() > currentplayer->getmaxhp()) {
			currentplayer->sethp(currentplayer->getmaxhp());
		}
	}

	if (effect == Card::effecttype::phalanxing) {
		playerphalanxdamage = 0;
		playerphalanxturns = card->getduration();
		playerphalanxing = true;
		playerphalanxbonus = card->getvalue();
		playerphalanxboosted = false;
		if (playerdonation == true) {
			phalanxdonated = true;
			enemymeleeattackbonus += card->getvalue();
			enemymeleedefensebonus += card->getvalue();
		}
		else {
			phalanxdonated = false;
			playermeleeattackbonus += card->getvalue();
			playermeleedefensebonus += card->getvalue();
		}
	}

	if (effect == Card::effecttype::melee_trigger_trap) {
		meleecountertrap = true;
	}

	if (effect == Card::effecttype::trap_counter) {
		playermirrortrap = true;
	}

	if (effect == Card::effecttype::prepare_upclose) {
		playerupclose = true;
		playerupcloseturns = card->getduration();
		playerupclosedamage = (currentplayer->getProjectileAttack() + playerprojectileattackbonus) * card->getmultiplier();
	}

	if (effect == Card::effecttype::poison_tip) {
		if (user == who::player) {
			bool hasattackcard = false;

			for (int i = 0; i < selectedcount; i++) {
				if (selectedcards[i] != card &&
					selectedcards[i]->gettype() == Card::cardtype::attack) {
					hasattackcard = true;
				}
			}

			if (hasattackcard == true) {
				enemypoisonturns = card->getduration();
				enemypoisonjustapplied = true;
			}
		}
		else {
			playerpoisonturns = card->getduration();
			playerpoisonjustapplied = true;
		}
	}

	if (effect == Card::effecttype::cannot_attack) {
		if (user == who::player) {
			playercannotattack = true;
			playercannotattackturns = card->getduration();
		}
		else {
			enemycannotattack = true;
			enemycannotattackturns = card->getduration();
		}
	}

	if (effect == Card::effecttype::defense_from_hp_lost) {
		int hplost = currentplayer->getmaxhp() - currentplayer->gethp();
		int defensegain = hplost * card->getmultiplier();
		if (currentplayer->getequippedadvancedarmor() != nullptr) {
			if (currentplayer->getequippedadvancedarmor()->getcombatcategory() == item::combattype::melee) {
				if (playerdonation == true) {
					addtimedstat(&enemymeleedefensebonus, defensegain, card->getduration());
				}
				else {
					addtimedstat(&playermeleedefensebonus, defensegain, card->getduration());
				}
			}
			else if (currentplayer->getequippedadvancedarmor()->getcombatcategory() == item::combattype::projectile) {
				if (playerdonation == true) {
					addtimedstat(&enemyprojectiledefensebonus, defensegain, card->getduration());
				}
				else {
					addtimedstat(&playerprojectiledefensebonus, defensegain, card->getduration());
				}
			}
			else if (currentplayer->getequippedadvancedarmor()->getcombatcategory() == item::combattype::none) {
				if (playerdonation == true) {
					addtimedstat(&enemymeleedefensebonus, defensegain, card->getduration());
					addtimedstat(&enemyprojectiledefensebonus, defensegain, card->getduration());
				}
				else {
					addtimedstat(&playermeleedefensebonus, defensegain, card->getduration());
					addtimedstat(&playerprojectiledefensebonus, defensegain, card->getduration());
				}
			}
		}
		else if (currentplayer->getequippedbasicarmor() != nullptr) {
			if (currentplayer->getequippedbasicarmor()->getcombatcategory() == item::combattype::melee) {
				if (playerdonation == true) {
					addtimedstat(&enemymeleedefensebonus, defensegain, card->getduration());
				}
				else {
					addtimedstat(&playermeleedefensebonus, defensegain, card->getduration());
				}
			}
			else if (currentplayer->getequippedbasicarmor()->getcombatcategory() == item::combattype::projectile) {
				if (playerdonation == true) {
					addtimedstat(&enemyprojectiledefensebonus, defensegain, card->getduration());
				}
				else {
					addtimedstat(&playerprojectiledefensebonus, defensegain, card->getduration());
				}
			}
			else if (currentplayer->getequippedbasicarmor()->getcombatcategory() == item::combattype::none) {
				if (playerdonation == true) {
					addtimedstat(&enemymeleedefensebonus, defensegain, card->getduration());
					addtimedstat(&enemyprojectiledefensebonus, defensegain, card->getduration());
				}
				else {
					addtimedstat(&playermeleedefensebonus, defensegain, card->getduration());
					addtimedstat(&playerprojectiledefensebonus, defensegain, card->getduration());
				}
			}
		}
		else {
			if (playerdonation == true) {
				addtimedstat(&enemymeleedefensebonus, defensegain, card->getduration());
				addtimedstat(&enemyprojectiledefensebonus, defensegain, card->getduration());
			}
			else {
				addtimedstat(&playermeleedefensebonus, defensegain, card->getduration());
				addtimedstat(&playerprojectiledefensebonus, defensegain, card->getduration());
			}
		}
	}

	if (effect == Card::effecttype::shield) {
		if (user == who::player) {
			playershield += 20;
		}
		else {
			enemyshield += 20;
		}
	}

	if (effect == Card::effecttype::projectile_to_melee) {
		playerprojectiletomelee = true;
	}

	if (effect == Card::effecttype::reflect_projectile) {
		playerreflectprojectile = true;
	}

	if (effect == Card::effecttype::chance_reflect_projectile) {
		enemyreflectprojectile = card->getduration();
	}

	if (effect == Card::effecttype::reflect_damage) {
		enemyreflectdamage = true;
		enemyreflectdamagemultiplier = card->getmultiplier();
		enemyreflectdamageturns = card->getduration();
	}

	if (effect == Card::effecttype::hypnotism) {
		playercannotattack = true;
		playerhypnotismturns = card->getduration();
		playerhypnotismjustapplied = true;
		int attack = 0;
		if (currentenemy->getMeleeAttack() >= currentenemy->getProjectileAttack()) {
			attack = currentenemy->getMeleeAttack() + enemymeleeattackbonus;
		}
		else {
			attack = currentenemy->getProjectileAttack() + enemyprojectileattackbonus;
		}
		playerhypnotismdamage = attack * card->getmultiplier();
	}

	if (effect == Card::effecttype::illusioned) {
		if (playerillusioned == false) {
			playerillusioned = true;
			enemymeleedefensebonus -= 5;
			enemyprojectiledefensebonus -= 5;
		}
	}

	if (effect == Card::effecttype::taunted) {
		playertaunted = true;
		playertauntedturns = card->getduration();
	}

	if (effect == Card::effecttype::heal_hp) {
		if (user == who::player) {
			currentplayer->sethp(currentplayer->gethp() + card->getvalue());
			if (currentplayer->gethp() > currentplayer->getmaxhp()) {
				currentplayer->sethp(currentplayer->getmaxhp());
			}
		}
		else {
			currentenemy->sethp(currentenemy->gethp() + card->getvalue());
			if (currentenemy->gethp() > currentenemy->getmaxhp()) {
				currentenemy->sethp(currentenemy->getmaxhp());
			}
		}
	}

	if (effect == Card::effecttype::donation) {
		playerdonation = true;
		playerdonationturns = card->getduration();
	}
}

void BattleManager::updateeffects() {
	// player poison
	if (playerpoisonturns > 0) {
		if (playerpoisonjustapplied == true) {
			playerpoisonjustapplied = false;
		}
		else {
			damageplayer(5);
			playerpoisonturns--;
		}
	}

	// enemy poison
	if (enemypoisonturns > 0) {
		if (enemypoisonjustapplied == true) {
			enemypoisonjustapplied = false;
		}
		else {
			damageenemy(5);
			enemypoisonturns--;
		}
	}

	// hypnotism
	if (playerhypnotismturns > 0) {
		if (playerhypnotismjustapplied == true) {
			playerhypnotismjustapplied = false;
		}
		else {
			damageplayer(playerhypnotismdamage);
			playerhypnotismturns--;
			if (playerhypnotismturns == 0) {
				playercannotattack = false;
			}
		}
	}

	// Charge!!!
	if (playerupclose == true) {
		if (playerupcloseturns > 0) {
			playerupcloseturns--;
		}
		else {
			damageenemy(playerupclosedamage);
			playerupclose = false;
		}
	}

	// Phalanxing
	if (playerphalanxing == true) {
		if (playerphalanxturns > 0) {
			playerphalanxturns--;
		}
		else {
			if (playerphalanxboosted == false) {
				if (playerphalanxdamage >= 10) {
					if (phalanxdonated == true) {
						enemymeleeattackbonus += playerphalanxbonus;
						enemymeleedefensebonus += playerphalanxbonus;
					}
					else {
						playermeleeattackbonus += playerphalanxbonus;
						playermeleedefensebonus += playerphalanxbonus;
					}

					playerphalanxboosted = true;
					playerphalanxturns = 1;
				}

				else {
					if (phalanxdonated == true) {
						enemymeleeattackbonus -= playerphalanxbonus;
						enemymeleedefensebonus -= playerphalanxbonus;
					}
					else {
						playermeleeattackbonus -= playerphalanxbonus;
						playermeleedefensebonus -= playerphalanxbonus;
					}
					playerphalanxing = false;
				}
			}
			else {
				if (phalanxdonated == true) {
					enemymeleeattackbonus -= playerphalanxbonus * 2;
					enemymeleedefensebonus -= playerphalanxbonus * 2;
				}
				else {
					playermeleeattackbonus -= playerphalanxbonus * 2;
					playermeleedefensebonus -= playerphalanxbonus * 2;
				}
				playerphalanxing = false;
				playerphalanxboosted = false;
			}
			playerphalanxdamage = 0;
		}
	}
	
	//donation
	if (playerdonation == true) {
		if (playerdonationturns > 0) {
			playerdonationturns--;
		}
		else {
			playerdonation = false;
		}
	}

	//reflect_damage
	if (enemyreflectdamage == true && enemyreflectdamagemultiplier < 1.0f) {
		if (enemyreflectdamageturns > 0) {
			enemyreflectdamageturns--;
		}

		if (enemyreflectdamageturns == 0) {
			enemyreflectdamage = false;
			enemyreflectdamagemultiplier = 0.0f;
		}
	}

	// Magic Ring duration
	if (enemyreflectprojectile > 0) {
		enemyreflectprojectile--;
	}

	// taunted
	if (playertaunted == true) {
		if (playertauntedturns > 0) {
			playertauntedturns--;
		}
		else {
			playertaunted = false;
		}
	}

	// player cannot attack
	if (playercannotattack == true && playerhypnotismturns == 0) {
		if (playercannotattackturns > 0) {
			playercannotattackturns--;
		}
		else {
			playercannotattack = false;
		}
	}

	// enemy cannot attack
	if (enemycannotattack == true) {
		if (enemycannotattackturns > 0) {
			enemycannotattackturns--;
		}
		else {
			enemycannotattack = false;
		}
	}

	for (int i = 0; i < 20; i++) {
		if (timedstats[i].active == true) {
			if (timedstats[i].turns > 0) {
				timedstats[i].turns--;
			}
			else {
				*timedstats[i].stat -= timedstats[i].amount;
				timedstats[i].stat = nullptr;
				timedstats[i].amount = 0;
				timedstats[i].turns = 0;
				timedstats[i].active = false;
			}
		}
	}

	if (playerdamagemultiplierturns > 0) {
		playerdamagemultiplierturns--;
		if (playerdamagemultiplierturns == 0) {
			playerdamagemultiplier = 1.0f;
		}
	}
	if (enemydamagemultiplierturns > 0) {
		enemydamagemultiplierturns--;
		if (enemydamagemultiplierturns == 0) {
			enemydamagemultiplier = 1.0f;
		}
	}
}

void BattleManager::discardplayedcards() {
	for (int i = currentplayer->getdeck()->gethandcount() - 1; i >= 0; i--) {
		if (selected[i] == true) {
			currentplayer->getdeck()->discardcard(i);
		}
	}

	for (int i = currentenemy->getdeck()->gethandcount() - 1; i >= 0; i--) {
		if (enemyselected[i] == true) {
			currentenemy->getdeck()->discardcard(i);
		}
	}
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
		int rawdamage = currentplayer->getMeleeAttack() / 2;
		int defense = currentenemy->getMeleeDefense() + enemymeleedefensebonus;
		int finaldamage = calculateDamage(rawdamage, defense);

		damageenemy(finaldamage);
		trapaffected = true;
	}
	meleecountertrap = false;

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

void BattleManager::damageplayer(int damage) {
	if (playershield > 0 && enemyignoreshield == false) {
		playershield -= damage;
		if (playershield < 0) {
			playershield = 0;
		}
	}
	else {
		currentplayer->takeDamage(damage);
		if (playerphalanxing == true) {
			playerphalanxdamage += damage;
		}
	}
}

void BattleManager::damageenemy(int damage) {
	if (enemyshield > 0) {
		enemyshield -= damage;
		if (enemyshield < 0) {
			enemyshield = 0;
		}
	}
	else {
		currentenemy->takeDamage(damage);
		if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::SURVIVOR && currentenemy->gethp() <= 100 && currentenemy->getsurvivorphase2() == false) {
			currentenemy->sethp(100);
		}
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

void BattleManager::addtimedstat(int* stat, int amount, int duration) {
	*stat += amount;
	if (duration > 0) {
		for (int i = 0; i < 20; i++) {
			if (timedstats[i].active == false) {
				timedstats[i].stat = stat;
				timedstats[i].amount = amount;
				timedstats[i].turns = duration;
				timedstats[i].active = true;
				return;
			}
		}
	}
}

void BattleManager::displaymessage(std::string message) {
	std::cout << message << std::endl;
}