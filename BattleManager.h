#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Card.h"
class BattleManager
{
public:
	enum class who {
		player,
		enemy
	};
	BattleManager(Player* player, Enemy* enemy);
	void displaybattle(who turn, bool showboard);
	void displayplayereffects();
	void displayenemyeffects();
	void displaycards(Card* cards[], int count);
	void displayboard(who user);
	//dialogue
	void displaydialogue(std::string speaker, std::string text);
	void battlestartdialogue();
	void battleenddialogue();
	void battleeventdialogue(std::string event);

	void displaymessage(std::string message);
	void StartBattle();
	void PlayerTurn();
	void EnemyTurn();
	void resolveturn();

	void playcard(Card* card, who user);
	void applyeffect(Card* card, Card::effecttype effect, who user);
	
	int calculateDamage(int rawdamage, int defense);
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
	int enemyselectedcount = 0;
	int playermeleeattackbonus = 0;
	int playerprojectileattackbonus = 0;
	int playermeleedefensebonus = 0;
	int playerprojectiledefensebonus = 0;
	int playershield = 0;
	int turn = 0;

	float playerdamagemultiplier = 1.0f;
	float enemydamagemultiplier = 1.0f;
	//stay alert / watch
	int playernegateattacktrap;
	int playernegatedefensetrap;
	int enemynegateattacktrap;
	int enemynegatedefensetrap;
	//rat trap
	bool playermeleecountertrap;
	bool enemymeleecountertrap;
	//mirror trap
	bool playermirrortrap;

	bool playerignoredefense;
	bool enemyignoredefense;
	bool playerignoreshield;
	bool enemyignoreshield;

	bool playerreflectprojectile;
	int enemyreflectprojectile;

	int enemymeleeattackbonus = 0;
	int enemymeleedefensebonus = 0;
	int enemyprojectileattackbonus = 0;
	int enemyprojectiledefensebonus = 0;
	int enemyshield = 0;

	bool playerskip = false;
	bool enemyskip = false;
};

