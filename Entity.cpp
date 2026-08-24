#include "Entity.h"

Entity::Entity(int hp, int meleeAtk, int projectileAtk, int meleeDef, int projectileDef)
{
    this->hp = hp;
    this->meleeAttack = meleeAtk;
    this->projectileAttack = projectileAtk;
    this->meleeDefense = meleeDef;
    this->projectileDefense = projectileDef;

    maxhp = hp;
}

//getter
int Entity::gethp()
{
    return hp;
}

int Entity::getmaxhp()
{
    return maxhp;
}

int Entity::getMeleeAttack()
{
    return meleeAttack;
}

int Entity::getProjectileAttack()
{
    return projectileAttack;
}

int Entity::getMeleeDefense()
{
    return meleeDefense;
}

int Entity::getProjectileDefense()
{
    return projectileDefense;
}

//bool
bool Entity::isalive()
{
    return hp > 0;
}

void Entity::takeDamage(int damage)
{
    if (damage < 0){
        damage = 0; // Prevent negative damage
    }

    hp -= damage;
    if (hp < 0){
        hp = 0; // Prevent negative health
    }
}

//setter
void Entity::setMeleeAttack(int meleeAtk)
{
    meleeAttack = meleeAtk;
}

void Entity::setProjectileAttack(int projectileAtk)
{
    projectileAttack = projectileAtk;
}

void Entity::setMeleeDefense(int meleeDef)
{
    meleeDefense = meleeDef;
}

void Entity::setProjectileDefense(int projectileDef)
{
    projectileDefense = projectileDef;
}
