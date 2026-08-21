#pragma once

#include "Puzzle.h"

class SurvivorPuzzle : public Puzzle {
	
private:
	int stage;
	int selectedChoice;
	bool wrongChoice;

public:
	SurvivorPuzzle(int startX, int startY);
	~SurvivorPuzzle();

	bool checkSolution();
	void draw();
	void handleInput(char input);
};