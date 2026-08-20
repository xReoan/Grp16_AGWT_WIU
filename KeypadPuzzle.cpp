#include "KeypadPuzzle.h"

#include <iostream>

KeypadPuzzle::KeypadPuzzle(
    int startX,
    int startY)
    : Puzzle(
        startX,
        startY,
        8,
        1)
{
    enteredCode = "";

    // Temporary Room 1 code.
    //
    // Later this can be the code
    // revealed after defeating the boss.
    correctCode = "9473";

    wrongCode = false;
}

KeypadPuzzle::~KeypadPuzzle()
{
}

// Draws the keypad screen.
void KeypadPuzzle::draw()
{
    std::cout
        << "+----------------------------------+"
        << std::endl;

    std::cout
        << "|              KEYPAD              |"
        << std::endl;

    std::cout
        << "|                                  |"
        << std::endl;

    std::cout
        << "|             ";

    // Display four code positions.
    for (std::size_t i = 0; i < 4; i++)
    {
        if (i < enteredCode.length())
        {
            std::cout
                << enteredCode[i]
                << " ";
        }
        else
        {
            std::cout
                << "_ ";
        }
    }

    std::cout
        << "             |"
        << std::endl;

    std::cout
        << "|                                  |"
        << std::endl;

    std::cout
        << "|           [1] [2] [3]            |"
        << std::endl;

    std::cout
        << "|           [4] [5] [6]            |"
        << std::endl;

    std::cout
        << "|           [7] [8] [9]            |"
        << std::endl;

    std::cout
        << "|               [0]                |"
        << std::endl;

    std::cout
        << "|                                  |"
        << std::endl;

    // Display puzzle result.
    if (getSolved() == true)
    {
        std::cout
            << "|          ACCESS GRANTED          |"
            << std::endl;
    }
    else if (wrongCode == true)
    {
        std::cout
            << "|          INCORRECT CODE          |"
            << std::endl;
    }
    else
    {
        std::cout
            << "|                                  |"
            << std::endl;
    }

    std::cout
        << "|                                  |"
        << std::endl;

    std::cout
        << "|  0-9       Enter Number          |"
        << std::endl;

    std::cout
        << "|  BACKSPACE Delete Number         |"
        << std::endl;

    std::cout
        << "|  ENTER     Confirm               |"
        << std::endl;

    std::cout
        << "|  Q         Back                  |"
        << std::endl;

    std::cout
        << "+----------------------------------+"
        << std::endl;
}

// Handles keypad controls.
void KeypadPuzzle::handleInput(
    char input)
{
    // --------------------------
    // NUMBER KEYS
    // --------------------------

    if (input >= '0' &&
        input <= '9')
    {
        // Maximum of four digits.
        if (enteredCode.length() < 4)
        {
            enteredCode =
                enteredCode + input;
        }

        // Remove incorrect message
        // once player begins typing again.
        wrongCode = false;
    }

    // --------------------------
    // BACKSPACE
    // --------------------------

    else if (input == 8)
    {
        if (enteredCode.length() > 0)
        {
            enteredCode.pop_back();
        }

        wrongCode = false;
    }

    // --------------------------
    // ENTER
    // --------------------------

    else if (input == 13)
    {
        // Only check once four digits
        // have been entered.
        if (enteredCode.length() == 4)
        {
            if (checkSolution() == true)
            {
                setSolved(true);

                wrongCode = false;
            }
            else
            {
                wrongCode = true;
            }
        }
    }

    // --------------------------
    // Q = LEAVE PUZZLE
    // --------------------------

    else if (input == 'Q' ||
        input == 'q')
    {
        setExitRequested(true);
    }
}

// Checks solution.
bool KeypadPuzzle::checkSolution()
{
    if (enteredCode == correctCode)
    {
        return true;
    }

    return false;
}

// Clears player's input.
void KeypadPuzzle::clearEnteredCode()
{
    enteredCode = "";

    wrongCode = false;
}

std::string KeypadPuzzle::getEnteredCode()
{
    return enteredCode;
}
