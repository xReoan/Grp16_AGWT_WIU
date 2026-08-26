#pragma once
#include "Puzzle.h"

class TricksterPuzzle : public Puzzle 
{
private:
    int ballPosition;
    int selectedCup;
    bool wrongChoice;
    bool shuffled;

    //make random shuffle
    int firstCup[3];
    int secondCup[3];


public:
    TricksterPuzzle(int startX, int startY);
    ~TricksterPuzzle();

    void draw();
    bool checkSolution();
    void handleInput(char input);

    void shuffleCups(int firstCup, int secondCup);
    void showShuffle();
};