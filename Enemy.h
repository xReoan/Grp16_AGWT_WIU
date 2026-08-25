#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "CardDeck.h"
#include "CardDatabase.h"

class Enemy : public Entity
{
public:
	enum class ENEMY_TYPE
	{
		NONE,
		TUTORIAL,
		GUNMAN,
		GRIM,
		TRICKSTER,
		SURVIVOR,
		HENCHMEN,
		GAME_MASTER,
	};

private:
	ENEMY_TYPE enemytype;
	Entity* entity;
	CardDeck deck;
	int meleeattack;
	int projectileattack;
	int gunmanquantities[5] = { 3, 2, 2, 1, 2 };
	int grimquantities[3] = { 1, 1, 2 };
	int tricksterquantities[5] = { 1, 1, 2, 1, 2 };
	int survivorquantities[4] = { 2, 2, 2, 1 };
	int enemyquantities[2] = { 2, 1 };
	int bbbquantities[2] = { 4, 2 };
	bool issurvivorphase2 = false;
	std::string name;

public:
	Enemy();
	Enemy(std::string name, ENEMY_TYPE type, int hp, int enemyMeleeAttack, int enemyProjectileAttack, int enemyMeleeDefense, int enemyProjectileDefense);
	~Enemy();

	// getters
    ENEMY_TYPE getEnemyType() const;
	int getMeleeAttack() const;
	int getProjectileAttack() const;
	std::string getname() const;

    // setters
    void setEnemyType(ENEMY_TYPE type);
    void setMeleeAttack(int enemyMeleeAttack);
	void setProjectileAttack(int enemyProjectileAttack);

	CardDeck* getdeck();
	void builddeck(CardDatabase* database);
	bool getsurvivorphase2();
	void setsurvivorphase2(bool survivorphase2);
	int displayhp();
};

