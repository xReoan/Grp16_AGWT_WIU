#pragma once
#include "Entity.h"
#include "item.h"
#include "inv.h"
#include "Room.h"
#include "CardDeck.h"
#include "CardDatabase.h"
class Player : public Entity
{
private:
    inv inventory;
    CardDeck deck;
    int money;
    item* equippedbasicweapon;
    item* equippedadvancedweapon;
    item* equippedbasicarmor;
    item* equippedadvancedarmor;
    int basicquantities[7] = { 6, 2, 2, 4, 2, 2, 2 };

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
    item* getequippedbasicweapon();
    item* getequippedbasicarmor();
    item* getequippedadvancedweapon();
    item* getequippedadvancedarmor();
    CardDeck* getdeck();
    void updateattack();
    void updatedefense();
    void equipweapon(item* weapon);
    void equiparmor(item* armor);
    void unequipweapon(item* weapon);
    void unequiparmor(item* armor);

    void builddeck(CardDatabase* database);
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