#include "Player.h"

Player::Player()
{
    resetPosition();
}

// Reset player to the bottom centre
// of the current room.
void Player::resetPosition()
{
    x = 25;
    y = 17;

    facingDirection = 'W';
}

void Player::move(char direction, Room* room)
{
    int newX = x;
    int newY = y;

    // UP
    if (direction == 'W' ||
        direction == 'w')
    {
        facingDirection = 'W';

        newY--;
    }

    // DOWN
    else if (direction == 'S' ||
        direction == 's')
    {
        facingDirection = 'S';

        newY++;
    }

    // LEFT
    else if (direction == 'A' ||
        direction == 'a')
    {
        facingDirection = 'A';

        newX--;
    }

    // RIGHT
    else if (direction == 'D' ||
        direction == 'd')
    {
        facingDirection = 'D';

        newX++;
    }

    // Only move if Room says
    // the position is walkable.
    if (room->isWalkable(
        newX,
        newY) == true)
    {
        x = newX;
        y = newY;
    }
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

char Player::getFacingDirection()
{
    return facingDirection;
}