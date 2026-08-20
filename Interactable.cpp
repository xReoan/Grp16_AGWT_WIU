#include "Interactable.h"

// Creates an interactable object with
// a position and interaction size.
Interactable::Interactable(
    int startX,
    int startY,
    int objectWidth,
    int objectHeight)
{
    x = startX;
    y = startY;

    width = objectWidth;
    height = objectHeight;
}

// Virtual destructor.
Interactable::~Interactable()
{
}

// Returns x-coordinate.
int Interactable::getX()
{
    return x;
}

// Returns y-coordinate.
int Interactable::getY()
{
    return y;
}

// Returns interaction width.
int Interactable::getWidth()
{
    return width;
}

// Returns interaction height.
int Interactable::getHeight()
{
    return height;
}

// Checks whether a coordinate is inside
// this object's interaction area.
bool Interactable::containsPosition(
    int checkX,
    int checkY)
{
    if (checkX >= x &&
        checkX < x + width &&
        checkY >= y &&
        checkY < y + height)
    {
        return true;
    }

    return false;
}