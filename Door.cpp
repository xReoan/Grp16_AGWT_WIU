#include "Door.h"

// Creates a door.
//
// Width = 8
// Height = 1
//
// This matches:
//
// [ DOOR ]
Door::Door(int startX, int startY)
    : Interactable(startX, startY, 8, 1)
{
    // Room 1 door begins locked.
    unlocked = false;
}

Door::~Door()
{
}

bool Door::getUnlocked()
{
    return unlocked;
}

void Door::setUnlocked(bool value)
{
    unlocked = value;
}

// Determines what happens when
// the player interacts with the door.
InteractionResult Door::interact()
{
    if (unlocked == false)
    {
        return LOCKED;
    }

    return OPEN_DOOR;
}