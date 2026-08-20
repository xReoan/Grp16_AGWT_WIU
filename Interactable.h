#pragma once

// Tells Game what should happen
// after interacting with an object.
enum InteractionResult
{
    NO_ACTION,
    OPEN_MAP,
    OPEN_PUZZLE,
    OPEN_DOOR,
    LOCKED
};

// Abstract parent class for anything
// the player can interact with.
class Interactable
{
private:
    int x;
    int y;

    int width;
    int height;

public:
    Interactable(
        int startX,
        int startY,
        int objectWidth,
        int objectHeight);

    virtual ~Interactable();

    int getX();
    int getY();

    int getWidth();
    int getHeight();

    // Checks whether a coordinate is
    // inside this object's area.
    bool containsPosition(
        int checkX,
        int checkY);

    // Pure virtual interaction function.
    virtual InteractionResult interact() = 0;
};