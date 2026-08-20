#include "ClockPuzzle.h"

#include <iostream>

ClockPuzzle::ClockPuzzle(
    int startX,
    int startY)
    : Puzzle(
        startX,
        startY,
        21,
        5)
{
    // Starting time.
    hour = 12;
    minute = 0;

    // Correct Room 2 solution.
    correctHour = 10;
    correctMinute = 15;

    // Start by controlling hour hand.
    selectedHand = HOUR_HAND;

    wrongTime = false;

    // Unlike Room 1's keypad,
    // the Grandfather Clock is usable
    // immediately.
    setUnlocked(true);
}

ClockPuzzle::~ClockPuzzle()
{
}

// Determines which character should
// be used for a hand depending on direction.
char ClockPuzzle::getHandCharacter(
    int changeX,
    int changeY)
{
    // Vertical.
    if (changeX == 0)
    {
        return '|';
    }

    // Horizontal.
    if (changeY == 0)
    {
        return '-';
    }

    // Down-right or up-left.
    if ((changeX > 0 && changeY > 0) ||
        (changeX < 0 && changeY < 0))
    {
        return '\\';
    }

    // Up-right or down-left.
    return '/';
}

// Draws one hand onto the clock face.
//
// clockNumber represents a position:
// 12, 1, 2, 3 ... 11
void ClockPuzzle::drawHand(
    char clockFace[][47],
    int clockNumber,
    int length)
{
    // Centre of clock face.
    int centreX = 22;
    int centreY = 5;

    int changeX = 0;
    int changeY = 0;

    // Determine direction based on
    // clock position.

    if (clockNumber == 12)
    {
        changeX = 0;
        changeY = -1;
    }

    else if (clockNumber == 1)
    {
        changeX = 1;
        changeY = -1;
    }

    else if (clockNumber == 2)
    {
        changeX = 2;
        changeY = -1;
    }

    else if (clockNumber == 3)
    {
        changeX = 2;
        changeY = 0;
    }

    else if (clockNumber == 4)
    {
        changeX = 2;
        changeY = 1;
    }

    else if (clockNumber == 5)
    {
        changeX = 1;
        changeY = 1;
    }

    else if (clockNumber == 6)
    {
        changeX = 0;
        changeY = 1;
    }

    else if (clockNumber == 7)
    {
        changeX = -1;
        changeY = 1;
    }

    else if (clockNumber == 8)
    {
        changeX = -2;
        changeY = 1;
    }

    else if (clockNumber == 9)
    {
        changeX = -2;
        changeY = 0;
    }

    else if (clockNumber == 10)
    {
        changeX = -2;
        changeY = -1;
    }

    else if (clockNumber == 11)
    {
        changeX = -1;
        changeY = -1;
    }

    char handCharacter =
        getHandCharacter(
            changeX,
            changeY);

    // Draw the hand outward
    // from the centre.
    for (int i = 1;
        i <= length;
        i++)
    {
        int drawX =
            centreX +
            (changeX * i);

        int drawY =
            centreY +
            (changeY * i);

        // Make sure hand stays
        // inside clockFace.
        if (drawX >= 0 &&
            drawX < 46 &&
            drawY >= 0 &&
            drawY < 11)
        {
            clockFace[drawY][drawX]
                = handCharacter;
        }
    }
}

// Draws the full Grandfather Clock.
void ClockPuzzle::draw()
{
    // =====================================
    // CREATE CLOCK FACE
    // =====================================

    // 11 rows.
    // 46 visible characters per row.
    // Extra character for '\0'.
    char clockFace[11][47];

    // Fill clock face with spaces.
    for (int y = 0;
        y < 11;
        y++)
    {
        for (int x = 0;
            x < 46;
            x++)
        {
            clockFace[y][x] = ' ';
        }

        clockFace[y][46] = '\0';
    }

    // =====================================
    // CLOCK NUMBERS
    // =====================================

    // 12
    clockFace[0][21] = '1';
    clockFace[0][22] = '2';

    // 11
    clockFace[1][13] = '1';
    clockFace[1][14] = '1';

    // 1
    clockFace[1][31] = '1';

    // 10
    clockFace[3][8] = '1';
    clockFace[3][9] = '0';

    // 2
    clockFace[3][36] = '2';

    // 9
    clockFace[5][5] = '9';

    // 3
    clockFace[5][40] = '3';

    // 8
    clockFace[7][7] = '8';

    // 4
    clockFace[7][37] = '4';

    // 7
    clockFace[9][13] = '7';

    // 5
    clockFace[9][31] = '5';

    // 6
    clockFace[10][22] = '6';

    // =====================================
    // DRAW HANDS
    // =====================================

    // Hour hand uses the actual hour.
    //
    // Shorter than minute hand.
    drawHand(
        clockFace,
        hour,
        2);

    // Minute values:
    //
    // 00 = 12
    // 05 = 1
    // 10 = 2
    // 15 = 3
    // ...
    //
    // Convert minutes into clock number.
    int minutePosition =
        minute / 5;

    if (minutePosition == 0)
    {
        minutePosition = 12;
    }

    // Minute hand is longer.
    drawHand(
        clockFace,
        minutePosition,
        3);

    // Centre point should always
    // appear above the hands.
    clockFace[5][22] = 'O';

    // =====================================
    // DRAW OUTER UI
    // =====================================

    std::cout
        << "+----------------------------------------------+"
        << std::endl;

    std::cout
        << "|              GRANDFATHER CLOCK               |"
        << std::endl;

    std::cout
        << "|                                              |"
        << std::endl;

    // Draw the eleven rows
    // of the actual clock face.
    for (int y = 0;
        y < 11;
        y++)
    {
        std::cout
            << "|"
            << clockFace[y]
            << "|"
            << std::endl;
    }

    std::cout
        << "|                                              |"
        << std::endl;

    // =====================================
    // SELECTED HAND
    // =====================================

    if (selectedHand ==
        HOUR_HAND)
    {
        std::cout
            << "|  Selected: HOUR HAND                         |"
            << std::endl;
    }
    else
    {
        std::cout
            << "|  Selected: MINUTE HAND                       |"
            << std::endl;
    }

    // =====================================
    // CURRENT TIME
    // =====================================

    std::cout
        << "|  Current Time: ";

    // Hour.
    if (hour < 10)
    {
        std::cout << "0";
    }

    std::cout
        << hour
        << ":";

    // Minute.
    if (minute < 10)
    {
        std::cout << "0";
    }

    std::cout
        << minute;

    // Padding to keep box aligned.
    std::cout
        << "                            |"
        << std::endl;

    std::cout
        << "|                                              |"
        << std::endl;

    // =====================================
    // RESULT MESSAGE
    // =====================================

    if (getSolved() == true)
    {
        std::cout
            << "|               CLOCK CHIMES...                |"
            << std::endl;
    }

    else if (wrongTime == true)
    {
        std::cout
            << "|          NOTHING SEEMS TO HAPPEN             |"
            << std::endl;
    }

    else
    {
        std::cout
            << "|                                              |"
            << std::endl;
    }

    std::cout
        << "|                                              |"
        << std::endl;

    // =====================================
    // CONTROLS
    // =====================================

    std::cout
        << "|  [A/D] Rotate       [W/S] Change Hand        |"
        << std::endl;

    std::cout
        << "|  [E] Confirm        [Q] Leave                |"
        << std::endl;

    std::cout
        << "+----------------------------------------------+"
        << std::endl;
}

// =====================================
// INPUT
// =====================================

void ClockPuzzle::handleInput(
    char input)
{
    // =====================================
    // W / S = CHANGE HAND
    // =====================================

    if (input == 'W' ||
        input == 'w' ||
        input == 'S' ||
        input == 's')
    {
        if (selectedHand ==
            HOUR_HAND)
        {
            selectedHand =
                MINUTE_HAND;
        }
        else
        {
            selectedHand =
                HOUR_HAND;
        }

        wrongTime = false;
    }

    // =====================================
    // A = ROTATE BACKWARDS
    // =====================================

    else if (input == 'A' ||
        input == 'a')
    {
        // Hour hand.
        if (selectedHand ==
            HOUR_HAND)
        {
            hour--;

            if (hour < 1)
            {
                hour = 12;
            }
        }

        // Minute hand.
        else
        {
            minute =
                minute - 5;

            if (minute < 0)
            {
                minute = 55;
            }
        }

        wrongTime = false;
    }

    // =====================================
    // D = ROTATE FORWARDS
    // =====================================

    else if (input == 'D' ||
        input == 'd')
    {
        // Hour hand.
        if (selectedHand ==
            HOUR_HAND)
        {
            hour++;

            if (hour > 12)
            {
                hour = 1;
            }
        }

        // Minute hand.
        else
        {
            minute =
                minute + 5;

            if (minute > 55)
            {
                minute = 0;
            }
        }

        wrongTime = false;
    }

    // =====================================
    // E = CONFIRM
    // =====================================

    else if (input == 'E' ||
        input == 'e')
    {
        if (checkSolution()
            == true)
        {
            setSolved(true);

            wrongTime = false;
        }
        else
        {
            wrongTime = true;
        }
    }

    // =====================================
    // Q = LEAVE
    // =====================================

    else if (input == 'Q' ||
        input == 'q')
    {
        setExitRequested(true);
    }
}

// =====================================
// CHECK SOLUTION
// =====================================

bool ClockPuzzle::checkSolution()
{
    if (hour == correctHour &&
        minute == correctMinute)
    {
        return true;
    }

    return false;
}