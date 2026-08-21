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
	int meleeattack;
	int projectileattack;

public:
	Enemy();
	Enemy(ENEMY_TYPE type, int hp, int enemyMeleeAttack, int enemyProjectileAttack, int enemyMeleeDefense, int enemyProjectileDefense);
	~Enemy();


	// getters
    ENEMY_TYPE getEnemyType() const;
	int getMeleeAttack() const;
	int getProjectileAttack() const;

    // setters
    void setEnemyType(ENEMY_TYPE type);
    void setMeleeAttack(int enemyMeleeAttack);
	void setProjectileAttack(int enemyProjectileAttack);
};

