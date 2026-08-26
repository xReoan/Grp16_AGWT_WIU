#include "TricksterPuzzle.h"
#include <iostream>

//  [1]   [2]   [3]
//   -     -     -
//  / \   / \   / \
// /___\ /___\ /___\

// A/D - Select Cup
// E - Choose


//ANSWER TEST IS CUP 2

TricksterPuzzle::TricksterPuzzle(int startX, int startY) : Puzzle(startX, startY, 21, 5){
    ballPosition = 2; //ball placed at cup 2
    selectedCup = 1;
    wrongChoice = false;
    shuffled = false;
}

TricksterPuzzle::~TricksterPuzzle(){}

void TricksterPuzzle::draw(){
    //EXAMPLE
    if (shuffled == false){
        showShuffle();
        shuffled = true;
    }

    std::cout << "+----------------------------------------------------------+" << std::endl;
    std::cout << "|                    TRICKSTER'S GAME                      |" << std::endl;
    std::cout << "|                                                          |" << std::endl;

    std::cout << "|              The ball starts under Cup 2.                |" << std::endl;
    std::cout << "|                                                          |" << std::endl;
    for (int i = 0; i < 3; i++){
        std::cout << "|              Cup " << firstCup[i] << " <--> Cup " << secondCup[i] << std::endl;
    }
    std::cout << "|                                                          |" << std::endl;
    std::cout << "|          CUP 1          CUP 2          CUP 3             |" << std::endl;
    std::cout << "|                                                          |" << std::endl;

    std::cout << "|           ___            ___            ___              |" << std::endl;
    std::cout << "|          /   \\          /   \\          /   \\             |" << std::endl;
    std::cout << "|         /     \\        /     \\        /     \\            |" << std::endl;
    std::cout << "|        /_______\\      /_______\\      /_______\\           |" << std::endl;
    std::cout << "|                                                          |" << std::endl;

    // Selected cup
    if (selectedCup == 1)
    {
        std::cout << "|           ^^^                                            |" << std::endl;
        std::cout << "|         SELECTED                                         |" << std::endl;
    }
    else if (selectedCup == 2)
    {
        std::cout << "|                          ^^^                             |" << std::endl;
        std::cout << "|                        SELECTED                          |" << std::endl;
    }
    else
    {
        std::cout << "|                                         ^^^              |" << std::endl;
        std::cout << "|                                       SELECTED           |" << std::endl;
    }

    std::cout << "|                                                          |" << std::endl;

    // Result
    if (getSolved() == true)
    {
        std::cout << "|                       YOU FOUND IT!                      |" << std::endl;
    }
    else if (wrongChoice == true)
    {
        std::cout << "|                        WRONG CUP!                        |" << std::endl;
    }
    else
    {
        std::cout << "|                    Where is the ball?                    |" << std::endl;
    }

    std::cout << "|                                                          |" << std::endl;
    std::cout << "|              A/D Select      E Confirm                   |" << std::endl;
    std::cout << "|              Q Back                                      |" << std::endl;
    std::cout << "+----------------------------------------------------------+" << std::endl;
}

bool TricksterPuzzle::checkSolution()
{
    if (selectedCup == ballPosition)
    {
        return true;
    }

    return false;
}

void TricksterPuzzle::handleInput(char input) {
    //A = move left
    if (input == 'A' || input == 'a'){
        selectedCup--;
        if (selectedCup < 1){
            selectedCup = 3;  //wraps back to cup3
        }

        wrongChoice = false;
    }

    //D = move right
    else if (input == 'D' || input == 'd'){
        selectedCup++;
        if (selectedCup > 3){
            selectedCup = 1;   //wraps back to cup1
        }

        wrongChoice = false;
    }

    //E = confirm
    else if (input == 'E' || input == 'e') {
        //if correct
        if (checkSolution() == true) {
            setSolved(true);
            wrongChoice = false;
        }
        //wrong
        else {
            wrongChoice = true;
        }
    }
}

//track the ball
void TricksterPuzzle::shuffleCups(int firstCup, int secondCup) {
    if (ballPosition == firstCup) {
        ballPosition = secondCup;
    }
    
    else if (ballPosition == secondCup)
    {
        ballPosition = firstCup;
    }
}

//shuffle cup
void TricksterPuzzle::showShuffle()
{
    for (int i = 0; i < 3; i++) {
        firstCup[i] = rand() % 3 + 1;
        secondCup[i] = rand() % 3 + 1;

        while (secondCup[i] == firstCup[i])
        {
            secondCup[i] = rand() % 3 + 1;
        }

        shuffleCups(firstCup[i], secondCup[i]);
    }
}

