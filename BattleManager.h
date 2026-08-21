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
	void StartBattle();
	void PlayerTurn();
	void EnemyTurn();

	void playcard(Card* card, who user);
	void applyeffect(Card* card, Card::effecttype effect, who user);
	
	int calculateDamage(int rawdamage, int defense);

private:
	Player* currentplayer;
	Enemy* currentenemy;
	Card* selectedcards[3]; 
	int selectedcardcount = 0;
	int playermeleeattackbonus = 0;
	int playerprojectileattackbonus = 0;
	int playermeleedefensebonus = 0;
	int playerprojectiledefensebonus = 0;
	int playershield = 0;
	int turn = 0;

	int enemymeleeattackbonus = 0;
	int enemymeleedefensebonus = 0;
	int enemyprojectileattackbonus = 0;
	int enemyprojectiledefensebonus = 0;
	int enemyshield = 0;

	bool playerskip = false;
	bool enemyskip = false;
};

