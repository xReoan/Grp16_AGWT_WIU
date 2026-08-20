#pragma once

#include "Room.h"

class Player
{
private:
    int x;
    int y;

    // W = Up
    // A = Left
    // S = Down
    // D = Right
    char facingDirection;

public:
    Player();

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