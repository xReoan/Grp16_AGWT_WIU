#include "player.h"
#include <iostream>
Player::Player() : Entity(100, 0, 0, 0, 0) {
    money = 0;
    equippedbasicweapon = nullptr;
    equippedbasicarmor = nullptr;
	equippedadvancedweapon = nullptr;
    equippedadvancedarmor = nullptr;
    resetPosition();
}

int Player::getmoney() {
    return money;
}

item* Player::getequippedbasicweapon() {
    return equippedbasicweapon;
}

item* Player::getequippedbasicarmor() {
    return equippedbasicarmor;
}

item* Player::getequippedadvancedweapon() {
    return equippedadvancedweapon;
}

item* Player::getequippedadvancedarmor() {
    return equippedadvancedarmor;
}

void Player::equipweapon(item* weapon) {
    //checks if its a weapon outside of it already so that part was removed
    if (weapon->getequipmenttier() == item::equipment::basic) {
        equippedbasicweapon = weapon;
    }
    else if (weapon->getequipmenttier() == item::equipment::advanced) {
        equippedadvancedweapon = weapon;
    }
    updateattack();
}

void Player::equiparmor(item* armor) {
    //checks if its a armor outside of it already so that part was removed
    if (armor->getequipmenttier() == item::equipment::basic) {
        equippedbasicarmor = armor;
    }
    else if (armor->getequipmenttier() == item::equipment::advanced) {
        equippedadvancedarmor = armor;
    }
    updatedefense();
}

void Player::unequipweapon(item* weapon) {
    if (weapon == equippedbasicweapon) {
        equippedbasicweapon = nullptr;
    }
    else if (weapon = equippedadvancedweapon) {
        equippedadvancedweapon = nullptr;
    }
    updateattack();
}

void Player::unequiparmor(item* armor) {
    if (armor = equippedbasicarmor) {
        equippedbasicarmor = nullptr;
    }
    else if (armor = equippedadvancedarmor) {
        equippedadvancedarmor = nullptr;
    }
    updatedefense();
}

void Player::addmoney(int amount) {
    money += amount;
}

bool Player::spendmoney(int amount) {
    if (money >= amount) {
        money -= amount;
        return true;
    }
    else {
        return false;
    }
}

CardDeck* Player::getdeck() {
    return &deck;
}

void Player::updateattack() {
    int meleeattack = 0;
    int projectileattack = 0;

    if (equippedbasicweapon != nullptr) {
        if (equippedbasicweapon->getcombatcategory() == item::combattype::melee) {
            meleeattack = equippedbasicweapon->getattackvalue();
        }
        else if (equippedbasicweapon->getcombatcategory() == item::combattype::projectile) {
            projectileattack = equippedbasicweapon->getattackvalue();
        }
    }

    if (equippedadvancedweapon != nullptr) {
        if (equippedadvancedweapon->getcombatcategory() == item::combattype::melee) {
            meleeattack = equippedadvancedweapon->getattackvalue();
        }
        else if (equippedadvancedweapon->getcombatcategory() == item::combattype::projectile) {
            projectileattack = equippedadvancedweapon->getattackvalue();
        }
    }
    setMeleeAttack(meleeattack);
    setProjectileAttack(projectileattack);
}

void Player::updatedefense() {
    int meleedefense = 0;
    int projectiledefense = 0;

    if (equippedbasicarmor != nullptr) {
        meleedefense = equippedbasicarmor->getdefensevalue();
        projectiledefense = equippedbasicarmor->getdefensevalue();
    }

    if (equippedadvancedarmor != nullptr) {
        if (equippedadvancedarmor->getcombatcategory() == item::combattype::melee) {
            meleedefense += equippedadvancedarmor->getdefensevalue();
        }
        else if (equippedadvancedarmor->getcombatcategory() == item::combattype::projectile) {
            projectiledefense += equippedadvancedarmor->getdefensevalue();
        }
    }
    setMeleeDefense(meleedefense);
    setProjectileDefense(projectiledefense);
}


void Player::builddeck(CardDatabase* database) {
    for (int i = 0; i < 7; i++) {
        for (int a = 0; a < basicquantities[i]; a++) {
            deck.addcardtodraw(database->getcard(i));
        }
    }

    if (equippedadvancedweapon != nullptr) {
        if (equippedadvancedweapon->getcombatcategory() == item::combattype::melee) {
            for (int i = 7; i < 12; i++) {
                for (int a = 0; a < 2; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
        }
        else if (equippedadvancedweapon->getcombatcategory() == item::combattype::projectile) {
            for (int i = 12; i < 17; i++) {
                for (int a = 0; a < 2; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
        }
    }

    if (equippedadvancedarmor != nullptr) {
        for (int i = 17; i < 19; i++) {
            for (int a = 0; a < 2; a++) {
                deck.addcardtodraw(database->getcard(i));
            }
        }

        if (equippedadvancedarmor->getcombatcategory() == item::combattype::melee) {
            for (int i = 19; i < 22; i++) {
                for (int a = 0; a < 2; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
        }
        else if (equippedadvancedarmor->getcombatcategory() == item::combattype::projectile) {
            for (int i = 22; i < 25; i++) {
                for (int a = 0; a < 2; a++) {
                    deck.addcardtodraw(database->getcard(i));
                }
            }
        }
    }
    deck.shuffle();
}

// Reset player to the bottom centre of the current room.
void Player::resetPosition() {
    x = 25;
    y = 17;

    facingDirection = 'W';
}

// Attempts to move the player one position.
void Player::move(char direction, Room* room) {
    int newX = x;
    int newY = y;

    // UP
    if (direction == 'W' || direction == 'w') {
        facingDirection = 'W';
        newY--;
    }

    // DOWN
    else if (direction == 'S' || direction == 's') {
        facingDirection = 'S';
        newY++;
    }

    // LEFT
    else if (direction == 'A' || direction == 'a') {
        facingDirection = 'A';
        newX--;
    }

    // RIGHT
    else if (direction == 'D' || direction == 'd') {
        facingDirection = 'D';
        newX++;
    }

    // Only move if Room says
    // the position is walkable.
    if (room->isWalkable(newX, newY) == true) {
        x = newX;
        y = newY;
    }
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

char Player::getFacingDirection() {
    return facingDirection;
}

void Player::setStarterEquipment(itemDatabase* database) {
    equippedbasicweapon = database->getitem(0); // assuming Rock is index 0
}
