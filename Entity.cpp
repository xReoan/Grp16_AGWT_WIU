#include "Entity.h"

Entity::Entity(int hp, int meleeDef, int projectileDef)
{
    this->hp = hp;
    maxhp = hp;

    meleeDefense = meleeDef;
    projectileDefense = projectileDef;
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

void Entity::takeDamage(int damage, bool isProjectile)
{
    if (isProjectile){
        damage -= projectileDefense;
    }
    else{
        damage -= meleeDefense;
    }
    if (damage < 0){
        damage = 0; // Prevent negative damage
    }

    hp -= damage;
    if (hp < 0){
        hp = 0; // Prevent negative health
    }
}

//setter
void Entity::setMeleeDefense(int meleeDef)
{
    meleeDefense = meleeDef;
}

void Entity::setProjectileDefense(int projectileDef)
{
    projectileDefense = projectileDef;
}