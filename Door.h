#pragma once

#include "Interactable.h"

class Door : public Interactable
{
private:
    // Determines whether the player
    // is allowed to open this door.
    bool unlocked;

public:
    // Constructor.
    Door(int startX, int startY);

    // Destructor.
    ~Door() override;

    // Getter.
    bool getUnlocked();

    // Setter.
    void setUnlocked(bool value);

    // Door's version of interact().
    InteractionResult interact() override;
};