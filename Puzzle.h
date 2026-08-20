#pragma once

#include "Interactable.h"

// Abstract parent class for all puzzles.
//
// Examples:
// KeypadPuzzle
// ClockPuzzle
// SymbolPuzzle
class Puzzle : public Interactable
{
private:
    bool unlocked;
    bool solved;

    // True when the player wants
    // to leave the puzzle.
    bool exitRequested;

public:
    Puzzle(
        int startX,
        int startY,
        int puzzleWidth,
        int puzzleHeight);

    ~Puzzle() override;

    // Getters.
    bool getUnlocked();
    bool getSolved();
    bool getExitRequested();

    // Setters.
    void setUnlocked(bool value);
    void setSolved(bool value);
    void setExitRequested(bool value);

    // If locked:
    // returns LOCKED.
    //
    // If unlocked:
    // returns OPEN_PUZZLE.
    InteractionResult interact() override;

    // Every puzzle must draw
    // its own UI.
    virtual void draw() = 0;

    // Every puzzle handles
    // its own controls.
    virtual void handleInput(char input) = 0;

    // Every puzzle has a different solution.
    virtual bool checkSolution() = 0;
};