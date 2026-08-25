#pragma once
#include "Puzzle.h"

class TricksterPuzzle : public Puzzle 
{
private:
    int ballPosition;
    int selectedCup;
    bool wrongChoice;
    bool shuffled;


public:
    TricksterPuzzle(int startX, int startY);
    ~TricksterPuzzle();

    void draw();
    bool checkSolution();
    void handleInput(char input);

    void shuffleCups(int firsCup, int secondCup);
    void showShuffle();
};