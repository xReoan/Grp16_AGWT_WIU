#include "Enemy.h"

Enemy::Enemy() : Entity(0, 0, 0, 0, 0){
    enemytype = NONE;
    meleeattack = 0;
    projectileattack = 0;
}

Enemy::Enemy(ENEMY_TYPE type, int hp, int enemyMeleeAttack, int enemyProjectileAttack, int enemyMeleeDefense, int enemyProjectileDefense)
    : Entity(hp, enemyMeleeAttack, enemyProjectileAttack, enemyMeleeDefense, enemyProjectileDefense)
{
    enemytype = type;
	meleeattack = enemyMeleeAttack;
}

Enemy::~Enemy(){}

Enemy::ENEMY_TYPE Enemy::getEnemyType() const{
    return enemytype;
}

int Enemy::getMeleeAttack() const{
    return meleeattack;
}

int Enemy::getProjectileAttack() const {
    return projectileattack;
}

void Enemy::setEnemyType(ENEMY_TYPE type){
    enemytype = type;
}

void Enemy::setMeleeAttack(int enemyMeleeAttack){
    meleeattack = enemyMeleeAttack;
}

void Enemy::setProjectileAttack(int enemyProjectileAttack) {
    projectileattack = enemyProjectileAttack;
}
