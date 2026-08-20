#include "Enemy.h"

Enemy::Enemy() : Entity(0, 0, 0){
    enemytype = NONE;
    attack = 0;
}

Enemy::Enemy(ENEMY_TYPE type, int hp, int enemyAttack, int enemyMeleeDefense, int enemyProjectileDefense)
    : Entity(hp, enemyMeleeDefense, enemyProjectileDefense)
{
    enemytype = type;
	attack = enemyAttack;
}

Enemy::~Enemy(){}

Enemy::ENEMY_TYPE Enemy::getEnemyType() const{
    return enemytype;
}

int Enemy::getAttack() const{
    return attack;
}

void Enemy::setEnemyType(ENEMY_TYPE type){
    enemytype = type;
}

void Enemy::setAttack(int enemyAttack){
    attack = enemyAttack;
}

