#include "BattleManager.h"
#include <iostream>
#include <conio.h>
BattleManager::BattleManager(Player* player, Enemy* enemy, CardDatabase* database, bool tutorial) {
	battleCheatActivated = false;
	currentenemy = enemy;
	currentplayer = player;
	this->database = database;
	tutorialmode = tutorial;

	for (int i = 0; i < 20; i++) {
		timedstats[i].stat = nullptr;
		timedstats[i].amount = 0;
		timedstats[i].turns = 0;
		timedstats[i].active = false;
	}
	tutorialstep = 0;
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
	playernegatedefensetrap = 0;
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

	for (int i = 0; i < 5; i++) {
		trapmessages[i] = "";
	}
	trapmessagecount = 0;

	combomessagecount = 0;
	for (int i = 0; i < 5; i++) {
		combomessages[i] = "";
	}

	synergymessagecount = 0;
	for (int i = 0; i < 5; i++) {
		synergymessages[i] = "";
	}

	playerillusioned = false;
	enemyreflectdamagemultiplier = 1.0f;
	enemyreflectdamageturns = 0;

	playerhalfmeleeturns = 0;
	playerbandageturns = 0;
	playerbandageheal = 0;
	playertaunted = false;

	enemyreflectdamage = false;
	playerreflectprojectile = false;
	enemyreflectprojectile = 0;

	enemydetermination = false;
	enemygrievance = false;
	playerprojectiletomelee = false;

	playerskip = false;
	enemyskip = false;

	selectedcount = 0;
	enemyselectedcount = 0;
	playerlastdamage = 0;

	playerdamagemultiplierturns = 0;
	enemydamagemultiplierturns = 0;

	playerupclose = false;
	playerupcloseturns = 0;
	playerupclosedamage = 0;

	playerhypnotismturns = 0;
	playerhypnotismdamage = 0;

	playerpoisonturns = 0;
	enemypoisonturns = 0;

	playerphalanxbonus = 0;
	playerphalanxing = false;
	playerphalanxturns = 0;
	playerphalanxdamage = 0;
	phalanxdonated = false;
	playerphalanxboosted = false;

	playerdonation = false;
	playerdonationturns = 0;

	playerpoisonjustapplied = false;
	enemypoisonjustapplied = false;
	playerhypnotismjustapplied = false;

	playertauntedturns = 0;
	playercannotattackturns = 0;
	enemycannotattackturns = 0;
	survivorfinaltestused = false;
	metalpiercerpaired = false;
	for (int i = 0; i < 12; i++) {
		selected[i] = false;
		enemyselected[i] = false;
	}

	sworddotturns = 0;
	sworddotdamage = 0;
	shotgundeflowered = 0;
	jellyprojectilesabsorbed = 0;
	jellyturncounter = 0;
}

void BattleManager::StartBattle()
{
	// Reset the cheat whenever a new
	// battle begins.
	battleCheatActivated = false;
	currentplayer->builddeck(database);
	currentenemy->builddeck(database);
	for (int i = 0; i < 4; i++) {
		currentplayer->getdeck()->drawcard();
	}

	for (int i = 0; i < 4; i++) {
		currentenemy->getdeck()->drawcard();
	}

	if (currentplayer->getequippedadvancedarmor() != nullptr && currentplayer->getequippedadvancedarmor()->getname() == "ooooo shiny armor") {
		enemyskip = true;
		synergymessages[synergymessagecount] = "Your Shiny Armor dazzled " + currentenemy->getname() + "Their first turn was skipped!";
		synergymessagecount++;
	}

	while (currentplayer->isalive() && currentenemy->isalive()) {
		// ============================
		// PLAYER TURN
		// ============================

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
		// P was pressed during PlayerTurn.
		if (battleCheatActivated == true) {
			// Directly set HP to zero instead of
			// using damageenemy(). This also skips
			// special enemy phases.
			currentenemy->sethp(0);
			system("cls");
			std::cout << "============================================" << std::endl;
			std::cout << "          BATTLE SKIP ACTIVATED" << std::endl;
			std::cout << "============================================" << std::endl;

			std::cout << std::endl;
			std::cout << currentenemy->getname() << " was defeated." << std::endl;
			std::cout << std::endl;
			std::cout << "Press any key to continue." << std::endl;
			_getch();
			// Return to the code that originally
			// started the battle.
			return;
		}

		// ============================
		// ENEMY TURN
		// ============================

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
		displaybattle(who::player, true);
		hpbeforeturn = currentplayer->gethp();
		enemyhpbeforeturn = currentenemy->gethp();
		resolveturn();
		inspectplayedcards();
		trapmessagecount = 0;
		combomessagecount = 0;
		synergymessagecount = 0;
		if (tutorialmode == true && tutorialstep == 2 && currentplayer->gethp() < hpbeforeturn) {
			system("cls");
			std::cout << "Ouch. That one hurt, didn't it?\n\n";
			std::cout << "Enemy attacks are reduced by your corresponding defense.\n";
			std::cout << "Melee attacks use melee defense, while projectile attacks use projectile defense. You... currently have none. Try visiting our local shops!\n\n";
			std::cout << "Some cards can also protect you or weaken the enemy.\n\n";
			std::cout << "Press any key to continue. Don't keep them waiting.";
			_getch();
			tutorialstep++;
		}

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
	const int battlewidth = 44;
	std::string title = "vs. " + currentenemy->getname();
	int padding = (battlewidth - title.length()) / 2;
	for (int i = 0; i < padding; i++) {
		std::cout << " ";
	}
	std::cout << title << std::endl;
	std::cout << "============================================" << std::endl;

	std::cout << currentenemy->getname() << " HP: " << enemyhp;
	if (enemyshield > 0) {
		std::cout << "(+" << enemyshield << ")";
	}
	std::cout << "/" << currentenemy->getmaxhp();
	std::cout << ", ATK (melee): ?";
	if (enemymeleeattackbonus > 0) {
		std::cout << "(+" << enemymeleeattackbonus << ")";
	}
	std::cout << ", ATK (projectile): ?";
	if (enemyprojectileattackbonus > 0) {
		std::cout << "(+" << enemyprojectileattackbonus << ")";
	}
	std::cout << ", DEF (melee): ?";
	if (enemymeleedefensebonus > 0) {
		std::cout << "(+" << enemymeleedefensebonus << ")";
	}
	std::cout << ", DEF (projectile): ?";
	if (enemyprojectiledefensebonus > 0) {
		std::cout << "(+" << enemyprojectiledefensebonus << ")";
	}
	std::cout << std::endl;
	displayenemyeffects();

	std::cout << std::endl;

	if (showboard == true) {
		displayboard();
	}

	std::cout << std::endl;

	std::cout << "Your HP: " << currentplayer->gethp();
	if (playershield > 0) {
		std::cout << "(+" << playershield << ")";
	}
	std::cout << "/100";
	if (currentplayer->getProjectileAttack() == 0) {
		std::cout << ", ATK (melee): " << currentplayer->getMeleeAttack();
		if (playermeleeattackbonus > 0) {
			std::cout << "(+" << playermeleeattackbonus << ")";
		}
	}
	else if (currentplayer->getMeleeAttack() == 0) {
		std::cout << ", ATK (projectile): " << currentplayer->getProjectileAttack();
		if (playerprojectileattackbonus > 0) {
			std::cout << "(+" << playerprojectileattackbonus << ")";
		}
	}
	else {
		std::cout << ", ATK (melee): " << currentplayer->getMeleeAttack();
		if (playermeleeattackbonus > 0) {
			std::cout << "(+" << playermeleeattackbonus << ")";
		}
		std::cout << ", ATK (projectile): " << currentplayer->getProjectileAttack();
		if (playerprojectileattackbonus > 0) {
			std::cout << "(+" << playerprojectileattackbonus << ")";
		}
	}
	std::cout << ", DEF (melee): " << currentplayer->getMeleeDefense();
	if (playermeleedefensebonus > 0) {
		std::cout << "(+" << playermeleedefensebonus << ")";
	}
	std::cout << ", DEF (projectile): " << currentplayer->getProjectileDefense();
	if (playerprojectiledefensebonus > 0) {
		std::cout << "(+" << playerprojectiledefensebonus << ")";
	}
	std::cout << std::endl;
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
		std::cout << "[Double Whammy] ";
	}

	if (playerreflectprojectile == true) {
		std::cout << "[Jello Trampoline] ";
	}

	if (playerpoisonturns > 0) {
		std::cout << "[Poisoned: " << playerpoisonturns << " turns] ";
	}

	if (playerhypnotismturns > 0) {
		std::cout << "[Hypnotised: " << playerhypnotismturns << " turns] ";
	}
	else if (playercannotattack == true) {
		std::cout << "[Muted: " << playercannotattackturns << " turns] ";
	}

	if (playertaunted == true) {
		std::cout << "[Taunted: " << playertauntedturns << " turns] ";
	}

	if (playerupclose == true) {
		std::cout << "[Charge: " << playerupcloseturns << " turns] ";
	}

	if (playerphalanxing == true) {
		if (playerphalanxboosted == false) {
			std::cout << "[Phalanxing: " << playerphalanxturns << " turns] ";
		}
		else {
			std::cout << "[Phalanx Boosted: " << playerphalanxturns << " turns] ";
		}
	}

	if (playerprojectiletomelee == true) {
		std::cout << "[Projectile to Melee] ";
	}

	if (playerhalfmelee == true) {
		std::cout << "[Half Melee Damage] ";
	}

	if (playerhalfdamage == true) {
		std::cout << "[Half Damage] ";
	}

	if (playerbandageturns > 0) {
		std::cout << "[Bandage: " << playerbandageturns << " turns] ";
	}

	std::cout << std::endl;
}

void BattleManager::displayenemyeffects() {
	std::cout << currentenemy->getname() << "'s effects: ";

	bool haseffects = false;

	int trapcount = 0;

	if (enemynegateattacktrap > 0) {
		trapcount++;
	}

	if (playernegateattacktrap > 0) {
		trapcount++;
	}

	if (playernegatedefensetrap > 0) {
		trapcount++;
	}

	if (meleecountertrap == true) {
		trapcount++;
	}

	if (playermirrortrap == true) {
		trapcount++;
	}

	if (playerdonation == true) {
		trapcount++;
	}

	for (int i = 0; i < trapcount; i++) {
		std::cout << "[??? Trap] ";
		haseffects = true;
	}

	if (enemyreflectprojectile > 0) {
		std::cout << "[Magic Ring: " << enemyreflectprojectile << " turns] ";
		haseffects = true;
	}

	if (enemyreflectdamage == true) {
		std::cout << "[Reflect Damage] ";
		haseffects = true;
	}

	if (enemypoisonturns > 0) {
		std::cout << "[Poisoned: " << enemypoisonturns << " turns] ";
		haseffects = true;
	}

	if (enemycannotattack == true) {
		std::cout << "[Cannot Attack] ";
		haseffects = true;
	}

	if (sworddotturns > 0) {
		std::cout << "[Sword Wound: " << sworddotturns << " turns]";
		haseffects = true;
	}
	std::cout << std::endl;
}

void BattleManager::displaycards(Card* cards[], int count, bool hideenemytraps = false) {
	const int width = 20;

	for (int i = 0; i < count; i++) {
		std::cout << "+";
		for (int a = 0; a < width + 2; a++) {
			std::cout << "-";
		}
		std::cout << "+  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < count; i++) {
		std::string name = cards[i]->getcardname();

		if (hideenemytraps == true && cards[i]->gettype() == Card::cardtype::trap) {
			name = "???";
		}

		if (name == "Nodevība" && playerillusioned == false) {
			name = "Ferīre";
		}

		std::cout << "| " << name;

		for (int a = displaylength(name); a < width; a++) {
			std::cout << " ";
		}

		std::cout << " |  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < count; i++) {
		std::cout << "+";
		for (int a = 0; a < width + 2; a++) {
			std::cout << "-";
		}
		std::cout << "+  ";
	}
	std::cout << std::endl;
}

void BattleManager::displayboard() {
	std::cout << currentenemy->getname() << std::endl;

	if (enemyselectedcount > 0) {
		displaycards(enemyselectedcards, enemyselectedcount, true);
	}
	else {
		std::cout << "(no cards selected)" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::cout << "YOU" << std::endl;

	if (selectedcount > 0) {
		displaycards(selectedcards, selectedcount, false);
	}
	else {
		std::cout << "(no cards selected)" << std::endl;
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
	if (tutorialmode == true && tutorialstep == 0) {
		system("cls");
		displaybattle(who::player, false);
		std::cout << "Your hand:\n\n";
		for (int i = 0; i < currentplayer->getdeck()->gethandcount(); i++) {
			Card* card = currentplayer->getdeck()->getcardfromhand(i);
			std::cout << i + 1 << ": " << card->getcardname() << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << R"(43: "These are the cards in your hand. Neat, right?)" << std::endl;
		std::cin.get();
		std::cout << R"(15: "Not really.")" << std::endl;
		std::cin.get();
		std::cout << R"(43: "Ugh. Fine. If you really want more available cards, weapons and items may be just the thing for you!")" << std::endl;
		std::cin.get();
		std::cout << R"(15: "...Are you just trying to promote your business?")" << std::endl;
		std::cin.get();
		std::cout << R"(43: "Support local businesses!!!!!")" << std::endl;
		std::cout << std::endl;
		std::cin.get();
		std::cout << "Use W/S to move between cards in your hand.\n";
		std::cout << "Press I to inspect the highlighted card.\n\n";
		std::cin.get();
		std::cout << "Press any key to continue. Don't keep them waiting.";
		_getch();
		tutorialstep++;
	}
	showenemyaction();
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
		std::cout << "W/S: Up/Down  A/D: Deselect/Select  I: Card information  E: Open Inventory  Q: Skip Turn  Enter: Confirm Cards" << std::endl;
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
				if (tutorialmode == true && tutorialstep == 1) {
					system("cls");
					std::cout << "You may play up to 3 cards each turn.\n";
					std::cout << "Press D to select a card.\n";
					std::cout << "Press A to deselect it.\n\n";
					std::cout << "Press any key to continue. Don't keep them waiting.";
					_getch();
					tutorialstep++;
				}
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
		else if (input == 'e' || input == 'E') {
			inv inventory;
			system("cls");

			inventory.OpenInv(true);
			int choice;

			std::cout << std::endl;
			std::cout << "Choose an item (1-16, 0 to cancel): ";
			std::cin >> choice;

			if (choice != 0) {
				choice--;
				if (choice >= 0 && choice < 16) {
					if (inventory.checkingType(choice) == 2) {
						item* useditem = inventory.geteatInv(choice);
						if (useditem != nullptr) {
							if (useditem->getname() == "Bandage") {
								playerbandageturns = useditem->getduration();
								playerbandageheal = useditem->gethealvalue();
							}
							else {
								int oldhp = currentplayer->gethp();
								currentplayer->sethp(currentplayer->gethp() + useditem->gethealvalue());
								if (currentplayer->gethp() > currentplayer->getmaxhp()) {
									currentplayer->sethp(currentplayer->getmaxhp());
								}
								int healed = currentplayer->gethp() - oldhp;
								std::cout << "recovered " << healed << " HP!" << std::endl;
							}
						}

						std::cout << "Press any key to continue...";
						_getch();
					}
					else {
						std::cout << "now's not the time to use that...!" << std::endl;
						_getch();
					}
				}
			}
		}

		// =====================================
		// P = SKIP BATTLE CHEAT
		// =====================================

		else if (input == 'p' ||
			input == 'P')
		{
			battleCheatActivated = true;

			// Exit the card-selection loop.
			selecting = false;

			selectedcount = 0;

			for (int i = 0; i < 3; i++)
			{
				selectedcards[i] =
					nullptr;
			}
		}

		else if (input == 13) {
			if (selectedcount > 0) {
				selecting = false;
			}
		}
	}
}

void BattleManager::EnemyTurn() {
	if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::SURVIVOR) {
		if (survivorfinaltestused == true) {
			enemyselectedcount = 0;
			for (int i = 0; i < 3; i++) {
				enemyselectedcards[i] = nullptr;
			}
			return;
		}
		if (currentenemy->gethp() < 5) {
			enemyselectedcount = 1;
			enemyselectedcards[0] = database->getcard(47);
			enemyselectedcards[1] = nullptr;
			enemyselectedcards[2] = nullptr;
			survivorfinaltestused = true;
			return;
		}
	}
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
	checktraps(selectedcards, selectedcount, playernegated, who::enemy);
	checktraps(enemyselectedcards, enemyselectedcount, enemynegated, who::player);
	std::string attacknames = "";
	for (int i = 0; i < selectedcount; i++) {
		if (!playernegated[i] && selectedcards[i]->gettype() == Card::cardtype::attack) {
			if (attacknames != "") {
				attacknames += " + ";
			}
			attacknames += selectedcards[i]->getcardname();
		}
	}
	std::string enemyattacknames = "";
	for (int i = 0; i < enemyselectedcount; i++) {
		if (!enemynegated[i] && enemyselectedcards[i]->gettype() == Card::cardtype::attack) {
			if (enemyattacknames != "") {
				enemyattacknames += " + ";
			}
			enemyattacknames += enemyselectedcards[i]->getcardname();
		}
	}
	bool hasenemyattack = false;
	for (int i = 0; i < enemyselectedcount; i++) {
		if (!enemynegated[i] &&
			enemyselectedcards[i]->gettype() == Card::cardtype::attack) {
			hasenemyattack = true;
		}
	}
	metalpiercerpaired = false;
	for (int i = 0; i < selectedcount; i++) {
		if (!playernegated[i] && selectedcards[i]->getcardname() == "Metal Piercer") {
			hasmetalpiercer = true;
		}
		if (!playernegated[i] && selectedcards[i]->gettype() == Card::cardtype::attack) {
			hasattackcard = true;
		}
	}
	if (hasmetalpiercer && hasattackcard) {
		metalpiercerpaired = true;
		playerignoredefense = true;
		combomessages[combomessagecount] = "COMBO! Metal Piercer + " + attacknames + ": Defense ignored!";
		combomessagecount++;
	}

	bool hasnonnegatedattack = false;
	for (int i = 0; i < selectedcount; i++) {
		if (!playernegated[i] &&
			selectedcards[i]->gettype() ==
			Card::cardtype::attack) {
			hasnonnegatedattack = true;
		}
	}
	for (int i = 0; i < selectedcount; i++) {
		if (!playernegated[i] && selectedcards[i]->getcardname() == "Poison-Tipped Bullets" && hasnonnegatedattack == true) {
			enemypoisonturns = selectedcards[i]->getduration();
			enemypoisonjustapplied = true;
			if (hasnonnegatedattack == true) {
				combomessages[combomessagecount] = "COMBO! Poison-Tipped Bullets + " + attacknames + ": Poison inflicted!";
				combomessagecount++;
			}
		}
	}
	for (int i = 0; i < selectedcount; i++) {
		if (!playernegated[i] && selectedcards[i]->getcardname() == "Chemical Boost") {
			playerdamagemultiplier *= selectedcards[i]->getmultiplier();
			playerdamagemultiplierturns = selectedcards[i]->getduration();
			if (hasnonnegatedattack == true) {
				combomessages[combomessagecount] = "COMBO! Chemical Boost + " + attacknames + ": Damage increased!";
				combomessagecount++;
			}
		}
	}
	for (int i = 0; i < enemyselectedcount; i++) {
		if (!enemynegated[i] && enemyselectedcards[i]->getcardname() == "Enhance") {
			enemydamagemultiplier *= enemyselectedcards[i]->getmultiplier();
			enemydamagemultiplierturns = enemyselectedcards[i]->getduration();
			if (hasenemyattack == true) {
				combomessages[combomessagecount] = "ENEMY COMBO! Enhance + " + enemyattacknames + ": Damage increased!";
				combomessagecount++;
			}
		}
	}
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
	for (int i = 0; i < 3; i++) {
		Card::effecttype effect = card->getcardeffect(i);

		if (effect != Card::effecttype::none) {
			applyeffect(card, effect, user);
		}
	}

	if (user == who::enemy) {
		if (haseffect(card, Card::effecttype::ignore_defense)) {
			enemyignoredefense = false;
		}

		if (haseffect(card, Card::effecttype::ignore_shield)) {
			enemyignoreshield = false;
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
			int magicringreflections = 0;
			for (int i = 0; i < hits; i++) {
				if (isProjectile && enemyreflectprojectile > 0) {
					int chance = rand() % 100;

					if (chance < 25) {
						damageplayer(finaldamage);
						magicringreflections++;
					}
					else {
						damageenemy(finaldamage);
					}
				}
				else if (enemyreflectdamage == true) {
					int reflecteddamage = finaldamage * enemyreflectdamagemultiplier;
					damageplayer(reflecteddamage);
					trapmessages[trapmessagecount] = "REFLECTED! " + std::to_string(reflecteddamage) + " damage was reflected back at you!";
					trapmessagecount++;
					if (enemyreflectdamagemultiplier < 1.0f) {
						damageenemy(finaldamage);
					}
				}
				else {
					damageenemy(finaldamage);
				}
			}
			playerlastdamage = oldhp - currentenemy->gethp();

			if (isProjectile == false && currentplayer->getequippedadvancedweapon() != nullptr && currentplayer->getequippedadvancedweapon()->getname() == "Sword") {
				sworddotdamage = 1;
				sworddotturns = 3;
			}

			if (isProjectile == true && currentplayer->getequippedadvancedweapon() != nullptr && currentplayer->getequippedadvancedweapon()->getname() == "Shotgun" && shotgundeflowered < 5) {
				enemyprojectiledefensebonus -= 1;
				shotgundeflowered++;
			}

			if (magicringreflections == 1) {
				trapmessages[trapmessagecount] = "REFLECTED! Magic Ring reflected 1 hit of " + card->getcardname() + "!";
			}
			else {
				trapmessages[trapmessagecount] = "REFLECTED! Magic Ring reflected " + std::to_string(magicringreflections) + " hits of " + card->getcardname() + "!";
			}

			if (playerillusioned == true && playerlastdamage >= 7) {
				playerillusioned = false;
				enemymeleedefensebonus += 5;
				enemyprojectiledefensebonus += 5;
			}
		}
		else {
			int damagedealt = 0;
			int rawdamage = 0;
			float multiplier = card->getmultiplier();
			if (card->getcardname() == "Nodevība" &&
				playerillusioned == false) {

				multiplier = 1.0f;
			}
			bool isProjectile = false;
			if (card->getcombatcategory() == item::combattype::melee) {
				damagedealt = currentenemy->getMeleeAttack();
				rawdamage = (damagedealt + enemymeleeattackbonus) * multiplier * enemydamagemultiplier;
			}
			else if (card->getcombatcategory() == item::combattype::projectile) {
				damagedealt = currentenemy->getProjectileAttack();
				isProjectile = true;
				rawdamage = (damagedealt + enemyprojectileattackbonus) * multiplier * enemydamagemultiplier;
			}
			else if (card->getcombatcategory() == item::combattype::flexible) {
				if (currentenemy->getMeleeAttack() >= currentenemy->getProjectileAttack()) {
					damagedealt = currentenemy->getMeleeAttack();
					rawdamage = (damagedealt + enemymeleeattackbonus) * multiplier * enemydamagemultiplier;
				}
				else {
					damagedealt = currentenemy->getProjectileAttack();
					isProjectile = true;
					rawdamage = (damagedealt + enemyprojectileattackbonus) * multiplier * enemydamagemultiplier;
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
				}
				if (playerhalfdamage == true) {
					finaldamage *= 0.5f;
					playerhalfdamage = false;
				}
				if (isProjectile && playerreflectprojectile == true) {
					damageenemy(finaldamage);
					trapmessages[trapmessagecount] = "REFLECTED! Jello Trampoline reflected " + card->getcardname() + "!";
					trapmessagecount++;
					playerreflectprojectile = false;
				}
				else {
					damageplayer(finaldamage);
					if (isProjectile == true && currentplayer->getequippedadvancedarmor() != nullptr && currentplayer->getequippedadvancedarmor()->getname() == "leftover jelly") {
						jellyprojectilesabsorbed++;
					}
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
			if (card->getcardname() != "Chemical Boost") {
				if (playerdonation == true) {
					enemydamagemultiplier *= card->getmultiplier();
					enemydamagemultiplierturns = card->getduration();
				}
				else {
					playerdamagemultiplier *= card->getmultiplier();
					playerdamagemultiplierturns = card->getduration();
				}
			}
		}
		else {
			if (card->getcardname() != "Enhance") {
				enemydamagemultiplier *= card->getmultiplier();
				enemydamagemultiplierturns = card->getduration();
			}
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
		if (currentenemy->gethp() < 5) {
			currentplayer->sethp(1);
			enemymeleedefensebonus = 0 - currentenemy->getMeleeDefense();
			enemyprojectiledefensebonus = 0 - currentenemy->getProjectileDefense();
		}
	}

	if (effect == Card::effecttype::lower_defense) {
		if (card->getcardname() == "Metal Piercer") {
			if (metalpiercerpaired == false) {
				addtimedstat(&enemymeleedefensebonus, -card->getvalue(), card->getduration());
			}
		}
		else {
			int amount = card->getvalue();
			if (user == who::player) {
				if (card->getcombatcategory() == item::combattype::melee) {
					addtimedstat(&enemymeleedefensebonus, -amount, card->getduration());
				}
				else if (card->getcombatcategory() == item::combattype::projectile) {
					addtimedstat(&enemyprojectiledefensebonus, -amount, card->getduration());
				}
				else if (card->getcombatcategory() == item::combattype::flexible) {
					if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::melee) {
						addtimedstat(&enemymeleedefensebonus, -amount, card->getduration());
					}
					else if (currentplayer->getequippedbasicweapon()->getcombatcategory() == item::combattype::projectile) {
						addtimedstat(&enemyprojectiledefensebonus, -amount, card->getduration());
					}
				}
			}
			else {
				if (card->getcardname() == "Radial Slash") {
					amount *= card->gethits();
				}
				if (card->getcombatcategory() == item::combattype::melee) {
					addtimedstat(&playermeleedefensebonus, -amount, card->getduration());
				}
				else if (card->getcombatcategory() == item::combattype::projectile) {
					addtimedstat(&playerprojectiledefensebonus, -amount, card->getduration());
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
		if (card->getcardname() != "Grievance") {
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
	}

	if (effect == Card::effecttype::increase_attack) {
		if (card->getcardname() != "Grievance") {
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
	}

	if (effect == Card::effecttype::half_damage_next_turn) {
		if (card->gettype() == Card::cardtype::hybrid) {
			playerhalfmelee = true;
			playerhalfmeleeturns = card->getduration() + 1;
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
			rawdamage = currentenemy->getMeleeAttack() * 0.5f;
		}
		else if (playercurrenthp <= currentplayer->getmaxhp() / 2) {
			rawdamage = currentenemy->getMeleeAttack();
		}
		else {
			rawdamage = currentenemy->getMeleeAttack() * 2;
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
			if (card->getcardname() == "Determination") {
				enemydetermination = true;
			}
		}
	}

	if (effect == Card::effecttype::negate_defense_card) {
		playernegatedefensetrap = card->getvalue();
	}

	if (effect == Card::effecttype::ignore_defense) {
		if (card->getcardname() == "Metal Piercer") {
			if (metalpiercerpaired == true) {
				playerignoredefense = true;
			}
		}
		else if (card->getcardname() == "Nodevība") {
			if (playerillusioned == true) {
				enemyignoredefense = true;
				synergymessages[synergymessagecount] = "SYNERGY! Ilūzija + Nodevība: Defense ignored, attack increased!";
				synergymessagecount++;
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
		if (card->getcardname() != "Poison-Tipped Bullets") {
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
	}

	if (effect == Card::effecttype::cannot_attack) {
		if (user == who::player) {
			playercannotattack = true;
			playercannotattackturns = card->getduration();
		}
		else {
			enemycannotattack = true;
			enemycannotattackturns = card->getduration();
			if (card->getcardname() == "Grievance") {
				enemygrievance = true;
			}
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
		playercannotattackturns = 1;
		playerhypnotismturns = card->getduration();
		playerhypnotismjustapplied = true;
		int attack = currentenemy->getProjectileAttack() + enemyprojectileattackbonus;
		int rawdamage = attack * card->getmultiplier();
		int defense = currentplayer->getProjectileDefense() + playerprojectiledefensebonus;
		playerhypnotismdamage = calculateDamage(rawdamage, defense);
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
		int healamount = card->getvalue();
		if (card->getcardname() == "Suit Up") {
			healamount = 2;
		}
		if (user == who::player) {
			currentplayer->sethp(currentplayer->gethp() + healamount);
			if (currentplayer->gethp() > currentplayer->getmaxhp()) {
				currentplayer->sethp(currentplayer->getmaxhp());
			}
		}
		else {
			currentenemy->sethp(currentenemy->gethp() + healamount);
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
						synergymessages[synergymessagecount] = "SYNERGY! Phalanx Empowered! You endured enough damage to strengthen the formation!";
						synergymessagecount++;
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
	if (enemyreflectdamage == true) {
		if (enemyreflectdamageturns > 0) {
			enemyreflectdamageturns--;
		}

		if (enemyreflectdamageturns == 0) {
			enemyreflectdamage = false;
			enemyreflectdamagemultiplier = 1.0f;
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
	if (playercannotattack == true) {
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
			if (enemygrievance == true) {
				addtimedstat(&enemymeleeattackbonus, 2, 0);
				addtimedstat(&enemymeleedefensebonus, 2, 0);
				enemygrievance = false;
			}
		}
	}

	//half melee
	if (playerhalfmelee == true) {
		if (playerhalfmeleeturns > 0) {
			playerhalfmeleeturns--;
		}

		if (playerhalfmeleeturns == 0) {
			playerhalfmelee = false;
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

	if (playerbandageturns > 0) {
		currentplayer->sethp(currentplayer->gethp() + playerbandageheal);
		if (currentplayer->gethp() > currentplayer->getmaxhp()) {
			currentplayer->sethp(currentplayer->getmaxhp());
		}
		playerbandageturns--;
	}

	if (sworddotturns > 0) {
		damageenemy(sworddotdamage);
		sworddotturns--;
		synergymessages[synergymessagecount] = "Sword's wound dealt 1 damage!";
		synergymessagecount++;
	}

	if (currentplayer->getequippedadvancedarmor() != nullptr && currentplayer->getequippedadvancedarmor()->getname() == "leftover jelly") {
		jellyturncounter++;
		if (jellyturncounter >= 2) {
			if (jellyprojectilesabsorbed > 0) {
				int oldhp = currentplayer->gethp();
				currentplayer->sethp(currentplayer->gethp() + jellyprojectilesabsorbed);
				if (currentplayer->gethp() > currentplayer->getmaxhp()) {
					currentplayer->sethp(currentplayer->getmaxhp());
				}
			}
			jellyprojectilesabsorbed = 0;
			jellyturncounter = 0;
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
				if (defender == who::enemy) {
					if (enemydetermination == true) {
						trapmessages[trapmessagecount] = "NEGATED! " + attackercard[index]->getcardname() + " was stopped by Determination!";
						trapmessagecount++;
					}
				}
				else {
					trapmessages[trapmessagecount] = "NEGATED! " + attackercard[index]->getcardname() + " was stopped by Stay Alert!";;
					trapmessagecount++;
				}
			}
		}
		if (defender == who::enemy &&
			enemydetermination == true &&
			trapaffected == true) {

			addtimedstat(&enemymeleedefensebonus, 2, 0);

			addtimedstat(&enemyprojectiledefensebonus, 2, 0);
		}
	}
	else {
		enemynegateattacktrap = 0;
		enemydetermination = false;
	}

	if (defensecount >= 2 && defensenegationcount > 0) {
		for (int i = 0; i < defensenegationcount; i++) {
			int index = findrandomcardtype(attackercard, attackercount, Card::cardtype::defense, negated);
			if (index != -1) {
				negated[index] = true;
				trapaffected = true;
				trapmessages[trapmessagecount] = "NEGATED! " + attackercard[index]->getcardname() + " was stopped by Watch!";;
				trapmessagecount++;
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

	if (defender == who::player && meleecountertrap == true)
	{
		bool meleedamage = false;
		for (int i = 0; i < attackercount; i++) {
			if (negated[i] == false && haseffect(attackercard[i], Card::effecttype::deal_damage)) {
				if (attackercard[i]->getcombatcategory() == item::combattype::melee) {
					meleedamage = true;
				}
				else if (attackercard[i]->getcombatcategory() == item::combattype::flexible) {
					if (currentenemy->getMeleeAttack() >= currentenemy->getProjectileAttack()) {
						meleedamage = true;
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
			trapmessages[trapmessagecount] = "Rat trap triggered! " + currentenemy->getname() + " took " + std::to_string(finaldamage) + " damage!";
			trapmessagecount++;
		}
		meleecountertrap = false;
	}

	if (defender == who::player) {
		if (trapaffected == true && playermirrortrap == true) {
			enemyskip = true;
			if (trapmessagecount < 5) {
				trapmessages[trapmessagecount] = "Double Whammy trap triggered! " + currentenemy->getname() + "'s next turn will be skipped!";
				trapmessagecount++;
			}
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
	if (defense < 0) {
		defense = 0;
	}
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
	int cap = 20;
	if (stat == &playermeleeattackbonus || stat == &playerprojectileattackbonus || stat == &enemymeleeattackbonus || stat == &enemyprojectileattackbonus) {
		cap = 15;
	}

	int newamount = amount;
	if (*stat + amount > cap) {
		newamount = cap - *stat;
	}
	else if (*stat + amount < -cap) {
		newamount = -cap - *stat;
	}
	if (newamount == 0) {
		return;
	}

	*stat += newamount;
	if (duration > 0) {
		for (int i = 0; i < 20; i++) {
			if (timedstats[i].active == false) {
				timedstats[i].stat = stat;
				timedstats[i].amount = newamount;
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

void BattleManager::inspectplayedcards() {
	bool inspecting = true;

	while (inspecting) {
		displayresolution();
		std::cout << "1-" << selectedcount << ": Inspect your cards" << std::endl;
		if (enemyselectedcount > 0) {
			std::cout << "4-" << 3 + enemyselectedcount
				<< ": Inspect enemy cards\n" << std::endl;
		}

		std::cout << "Enter: Continue" << std::endl;

		char input = _getch();

		if (input == 13) {
			inspecting = false;
		}
		else if (input >= '1' && input <= '3') {
			int index = input - '1';

			if (index < selectedcount) {
				system("cls");
				Card* card = enemyselectedcards[index];
				if (card->getcardname() == "Nodevība" && playerillusioned == false) {
					std::cout << "Ferīre" << std::endl;
					std::cout << std::endl;
					std::cout << "They deal damage." << std::endl;
				}
				else {
					std::cout << selectedcards[index]->getcardname() << std::endl;
					std::cout << std::endl;
					std::cout << selectedcards[index]->getcarddescription() << std::endl;
				}
				std::cout << std::endl;
				std::cout << "Press any key to return...";
				_getch();
			}
		}
		else if (input >= '4' && input <= '6') {
			int index = input - '4';

			if (index < enemyselectedcount) {
				system("cls");
				Card* card = enemyselectedcards[index];

				if (card->gettype() == Card::cardtype::trap) {
					std::cout << "???" << std::endl;
					std::cout << std::endl;
					std::cout << "You can't tell what this trap does yet." << std::endl;
				}
				else if (card->getcardname() == "Nodevība" &&
					playerillusioned == false) {
					std::cout << "Ferīre" << std::endl;
					std::cout << std::endl;
					std::cout << "They deal damage." << std::endl;
				}

				std::cout << enemyselectedcards[index]->getcardname() << std::endl;
				std::cout << std::endl;
				std::cout << enemyselectedcards[index]->getcarddescription() << std::endl;

				std::cout << std::endl;
				std::cout << "Press any key to return...";
				_getch();
			}
		}
	}
	trapmessagecount = 0;
}

int BattleManager::displaylength(std::string text) {
	int length = 0;

	for (int i = 0; i < text.length(); i++) {
		unsigned char c = text[i];

		if ((c & 0xC0) != 0x80) {
			length++;
		}
	}

	return length;
}

void BattleManager::displayresolution() {
	displaybattle(who::player, true);

	std::cout << std::endl;

	for (int i = 0; i < selectedcount; i++) {
		std::cout << "You used " << selectedcards[i]->getcardname() << "!\n" << std::endl;
	}

	for (int i = 0; i < enemyselectedcount; i++) {
		if (enemyselectedcards[i]->gettype() == Card::cardtype::trap) {
			std::cout << currentenemy->getname() << " used a trap card!\n" << std::endl;
		}
		else {
			std::string name = enemyselectedcards[i]->getcardname();
			if (name == "Nodevība" && playerillusioned == false) {
				name = "Ferīre";
			}
			std::cout << currentenemy->getname() << " used " << name << "!\n" << std::endl;
		}
	}
	for (int i = 0; i < trapmessagecount; i++) {
		std::cout << trapmessages[i] << "\n" << std::endl;
	}
	for (int i = 0; i < combomessagecount; i++) {
		std::cout << combomessages[i] << "\n" << std::endl;
	}
	for (int i = 0; i < synergymessagecount; i++) {
		std::cout << synergymessages[i] << "\n" << std::endl;
	}
	int playerdamagetaken = hpbeforeturn - currentplayer->gethp();
	int enemydamagetaken = enemyhpbeforeturn - currentenemy->gethp();
	if (playerdamagetaken > 0) {
		std::cout << "You took " << playerdamagetaken << " damage!\n";
	}
	if (enemydamagetaken > 0) {
		std::cout << currentenemy->getname() << " took " << enemydamagetaken << " damage!\n";
	}
}

void BattleManager::showenemyaction() {
	int choice = rand() % 3;

	if (currentenemy->getEnemyType() == Enemy::ENEMY_TYPE::GUNMAN) {
		if (choice == 0) std::cout << "Gunman takes aim.\n";
		else if (choice == 1) std::cout << "Gunman steadies their weapon.\n";
		else std::cout << "Gunman lines up a shot.\n";
		if (choice == 0) std::cout << "Gunman shifts into cover.\n";
		else if (choice == 1) std::cout << "Gunman adjusts their stance.\n";
		else std::cout << "Gunman keeps their guard up.\n";
	}

	// Grim / Trickster / Survivor
}