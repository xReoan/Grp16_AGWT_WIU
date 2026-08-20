#pragma once
#include <string>
#include "Entity.h"

class Enemy : public Entity
{
public:
	enum ENEMY_TYPE
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
	int attack;

public:
	Enemy();
	Enemy(ENEMY_TYPE type, int hp, int enemyAttack, int enemyMeleeDefense, int enemyProjectileDefense);
	~Enemy();


	// getters
    ENEMY_TYPE getEnemyType() const;
    int getAttack() const;

    // setters
    void setEnemyType(ENEMY_TYPE type);
    void setAttack(int enemyAttack);
};

