#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Card.h"
#include "CardDatabase.h"
#include <string>
class BattleManager
{
public:
	enum class who {
		player,
		enemy
	};

	struct timedstatchange {
		int* stat;
		int amount;
		int turns;
		bool active;
	};

	timedstatchange timedstats[20];
	void addtimedstat(int* stat, int amount, int duration);
	BattleManager(Player* player, Enemy* enemy, CardDatabase* database);
	void displaybattle(who turn, bool showboard);
	void displayplayereffects();
	void displayenemyeffects();
	void displaycards(Card* cards[], int count);
	void displayboard();
	void inspectplayedcards();
	int displaylength(std::string text);

	void displaymessage(std::string message);
	void StartBattle();
	void PlayerTurn();
	void EnemyTurn();
	void resolveturn();

	void playcard(Card* card, who user);
	void applyeffect(Card* card, Card::effecttype effect, who user);
	void updateeffects();
	void discardplayedcards();
	
	int calculateDamage(int rawdamage, int defense);
	void damageplayer(int damage);
	void damageenemy(int damage);
	void checktraps(Card* attackercard[], int attackercount, bool negated[], who defender);
	int findrandomcardtype(Card* cards[], int count, Card::cardtype type, bool negated[]);
	bool haseffect(Card* card, Card::effecttype effect);
	int findcardtype(Card::cardtype type, bool selected[]);
	void checksurvivorphase();

private:
	CardDatabase* database;
	Player* currentplayer;
	Enemy* currentenemy;
	Card* selectedcards[3] = { nullptr, nullptr, nullptr };
	bool selected[12];
	int selectedcount = 0;
	Card* enemyselectedcards[3] = { nullptr, nullptr, nullptr };
	bool enemyselected[12];
	int enemyselectedcount;
	int playermeleeattackbonus;
	int playerprojectileattackbonus;
	int playermeleedefensebonus;
	int playerprojectiledefensebonus;
	int playershield;
	int enemymeleeattackbonus;
	int enemymeleedefensebonus;
	int enemyprojectileattackbonus;
	int enemyprojectiledefensebonus;
	int enemyshield;
	int playerlastdamage;

	float playerdamagemultiplier;
	float enemydamagemultiplier;
	//stay alert / watch
	int playernegateattacktrap;
	int playernegatedefensetrap;
	int enemynegateattacktrap;
	//rat trap
	bool meleecountertrap;
	//mirror trap
	bool playermirrortrap;

	bool playerignoredefense;
	bool enemyignoredefense;

	bool enemyignoreshield;

	bool playerhalfmelee;
	bool playerhalfdamage;

	bool playercannotattack;
	bool enemycannotattack;

	int playerdamagemultiplierturns;
	int enemydamagemultiplierturns;

	bool playerillusioned;

	bool enemyreflectdamage;
	float enemyreflectdamagemultiplier;
	int enemyreflectdamageturns;

	bool playertaunted;

	bool playerupclose;
	int playerupcloseturns;
	int playerupclosedamage;

	bool playerreflectprojectile;
	int enemyreflectprojectile;

	int playerhypnotismturns;
	int playerhypnotismdamage;

	int playerpoisonturns;
	int enemypoisonturns;

	int playerphalanxbonus;
	bool playerphalanxing;
	int playerphalanxturns;
	int playerphalanxdamage;
	bool phalanxdonated;
	bool playerphalanxboosted;

	bool playerdonation;
	int playerdonationturns;

	bool playerprojectiletomelee;

	bool playerskip;
	bool enemyskip;

	bool playerpoisonjustapplied;
	bool enemypoisonjustapplied;
	bool playerhypnotismjustapplied;
	int playertauntedturns;
	int playercannotattackturns;
	int enemycannotattackturns;
};

