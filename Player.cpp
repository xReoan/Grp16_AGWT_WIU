#include "player.h"
#include <iostream>
Player::Player() : Entity(100, 100, 100) {
    money = 0;
    equippedweapon = nullptr;
    equippedarmor = nullptr;
    resetPosition();
}

int Player::getmoney() {
    return money;
}

item* Player::getweapon() {
    return equippedweapon;
}

item* Player::getarmor() {
    return equippedarmor;
}

void Player::equipweapon(item* weapon) {
    if (weapon != nullptr && weapon->getitemcategory() == item::itemtype::weapon) {
        equippedweapon = weapon;
    }
}

void Player::equiparmor(item* armor) {
    if (armor != nullptr && armor->getitemcategory() == item::itemtype::armor) {
        equippedarmor = armor;
    }
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
