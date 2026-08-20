#pragma once

#include "Puzzle.h"
#include <string>

class KeypadPuzzle : public Puzzle
{
private:
    // What the player has currently typed.
    std::string enteredCode;

    // Correct Room 1 code.
    std::string correctCode;

    // Used to display an incorrect message.
    bool wrongCode;

public:
    KeypadPuzzle(
        int startX,
        int startY);

    ~KeypadPuzzle() override;

    // Draws keypad screen.
    void draw() override;

    // Handles number keys,
    // Backspace, Enter and Q.
    void handleInput(char input) override;

    // Checks entered code.
    bool checkSolution() override;

    // Clears entered code.
    void clearEnteredCode();

    // Getter.
    std::string getEnteredCode();
};