#pragma once

#include "Puzzle.h"

#include <string>

class SymbolPuzzle : public Puzzle
{
private:
    static const int RING_COUNT = 4;
    static const int SYMBOL_COUNT = 4;

    // Symbol currently displayed
    // on each of the four rings.
    int currentSymbols[RING_COUNT];

    // Correct combination.
    int correctSymbols[RING_COUNT];

    // Currently selected ring.
    int selectedRing;

    // Displays message after
    // an incorrect attempt.
    bool wrongCombination;

    std::string getSymbolName(
        int symbolIndex) const;

public:
    SymbolPuzzle(
        int startX,
        int startY);

    ~SymbolPuzzle() override;

    void draw() override;

    void handleInput(
        char input) override;

    bool checkSolution() override;
};