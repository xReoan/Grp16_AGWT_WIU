#include "Puzzle.h"

Puzzle::Puzzle(
    int startX,
    int startY,
    int puzzleWidth,
    int puzzleHeight)
    : Interactable(
        startX,
        startY,
        puzzleWidth,
        puzzleHeight)
{
    unlocked = false;
    solved = false;
    exitRequested = false;
}

Puzzle::~Puzzle()
{
}

bool Puzzle::getUnlocked()
{
    return unlocked;
}

bool Puzzle::getSolved()
{
    return solved;
}

bool Puzzle::getExitRequested()
{
    return exitRequested;
}

void Puzzle::setUnlocked(bool value)
{
    unlocked = value;
}

void Puzzle::setSolved(bool value)
{
    solved = value;
}

void Puzzle::setExitRequested(bool value)
{
    exitRequested = value;
}

InteractionResult Puzzle::interact()
{
    if (unlocked == false)
    {
        return LOCKED;
    }

    return OPEN_PUZZLE;
}