#include "SymbolPuzzle.h"

#include <iomanip>
#include <iostream>
#include <sstream>

// =====================================
// CONSTRUCTOR
// =====================================

SymbolPuzzle::SymbolPuzzle(
    int startX,
    int startY)
    : Puzzle(
        startX,
        startY,
        21,
        5)
{
    // Symbol values:
    //
    // 0 = WOLF
    // 1 = MOON
    // 2 = CROW
    // 3 = EYE

    // Starting combination:
    // MOON, CROW, EYE, WOLF
    currentSymbols[0] = 1;
    currentSymbols[1] = 2;
    currentSymbols[2] = 3;
    currentSymbols[3] = 0;

    // Correct combination:
    // WOLF, MOON, CROW, EYE
    correctSymbols[0] = 0;
    correctSymbols[1] = 1;
    correctSymbols[2] = 2;
    correctSymbols[3] = 3;

    selectedRing = 0;

    wrongCombination = false;

    // The Room 3 safe can be used
    // immediately.
    setUnlocked(true);
}

SymbolPuzzle::~SymbolPuzzle()
{
}

// =====================================
// SYMBOL NAME
// =====================================

std::string SymbolPuzzle::getSymbolName(
    int symbolIndex) const
{
    if (symbolIndex == 0)
    {
        return "WOLF";
    }
    else if (symbolIndex == 1)
    {
        return "MOON";
    }
    else if (symbolIndex == 2)
    {
        return "CROW";
    }
    else
    {
        return "EYE";
    }
}

// =====================================
// DRAW
// =====================================

void SymbolPuzzle::draw()
{
    // Draws one padded line inside
    // the puzzle border.
    auto drawTextLine =
        [](const std::string& text)
        {
            std::cout
                << "| "
                << std::left
                << std::setw(44)
                << text
                << " |"
                << std::endl;
        };

    std::cout
        << "+----------------------------------------------+"
        << std::endl;

    drawTextLine(
        "             STRANGE LOCK");

    drawTextLine("");

    // Draw all four symbol rings.
    for (int i = 0;
        i < RING_COUNT;
        i++)
    {
        std::ostringstream line;

        line
            << "         [ "
            << std::left
            << std::setw(5)
            << getSymbolName(
                currentSymbols[i])
            << " ]";

        // Arrow beside selected ring.
        if (i == selectedRing)
        {
            line << "    <";
        }

        drawTextLine(
            line.str());
    }

    drawTextLine("");

    // Result message.
    if (getSolved() == true)
    {
        drawTextLine(
            "         THE SAFE UNLOCKS");
    }
    else if (wrongCombination == true)
    {
        drawTextLine(
            "       INCORRECT COMBINATION");
    }
    else
    {
        drawTextLine("");
    }

    drawTextLine("");

    drawTextLine(
        "A/D  Change Symbol");

    drawTextLine(
        "W/S  Select Ring");

    drawTextLine(
        "E    Try Combination");

    drawTextLine(
        "Q    Leave");

    std::cout
        << "+----------------------------------------------+"
        << std::endl;
}

// =====================================
// INPUT
// =====================================

void SymbolPuzzle::handleInput(
    char input)
{
    // W = Previous ring.
    if (input == 'W' ||
        input == 'w')
    {
        selectedRing--;

        if (selectedRing < 0)
        {
            selectedRing =
                RING_COUNT - 1;
        }

        wrongCombination = false;
    }

    // S = Next ring.
    else if (input == 'S' ||
        input == 's')
    {
        selectedRing++;

        if (selectedRing >=
            RING_COUNT)
        {
            selectedRing = 0;
        }

        wrongCombination = false;
    }

    // A = Previous symbol.
    else if (input == 'A' ||
        input == 'a')
    {
        currentSymbols[selectedRing]--;

        if (currentSymbols[selectedRing] <
            0)
        {
            currentSymbols[selectedRing] =
                SYMBOL_COUNT - 1;
        }

        wrongCombination = false;
    }

    // D = Next symbol.
    else if (input == 'D' ||
        input == 'd')
    {
        currentSymbols[selectedRing]++;

        if (currentSymbols[selectedRing] >=
            SYMBOL_COUNT)
        {
            currentSymbols[selectedRing] =
                0;
        }

        wrongCombination = false;
    }

    // E = Test combination.
    else if (input == 'E' ||
        input == 'e')
    {
        if (checkSolution() == true)
        {
            setSolved(true);

            wrongCombination = false;
        }
        else
        {
            wrongCombination = true;
        }
    }

    // Q = Leave puzzle.
    else if (input == 'Q' ||
        input == 'q')
    {
        setExitRequested(true);
    }
}

// =====================================
// CHECK SOLUTION
// =====================================

bool SymbolPuzzle::checkSolution()
{
    for (int i = 0;
        i < RING_COUNT;
        i++)
    {
        if (currentSymbols[i] !=
            correctSymbols[i])
        {
            return false;
        }
    }

    return true;
}