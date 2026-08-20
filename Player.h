#pragma once
#include "Entity.h"
#include "item.h"
#include "inv.h"
#include "Room.h"
class Player : public Entity
{
private:
    inv inventory;
    int money;
    item* equippedweapon;
    item* equippedarmor;
    // Player's current position inside the room.
    int x;
    int y;

    // W = Up
    // A = Left
    // S = Down
    // D = Right
    char facingDirection;
public:
    // Constructor.
    Player();

    int getmoney();
    void addmoney(int amount);
    bool spendmoney(int amount);
    item* getweapon();
    item* getarmor();
    void unequipweapon();
    void unequiparmor();
    void equipweapon(item* weapon);
    void equiparmor(item* armor);

    // Moves the player if the new position
    // is walkable.
    void move(char direction, Room* room);

    // Returns player to the starting position
    // when entering a new room.
    void resetPosition();

    int getX();
    int getY();

    char getFacingDirection();
};
