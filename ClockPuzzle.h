#pragma once

#include "Puzzle.h"

// Determines which hand the player
// is currently controlling.
enum ClockHand
{
    HOUR_HAND,
    MINUTE_HAND
};

class ClockPuzzle : public Puzzle
{
private:
    // Current time shown by the clock.
    int hour;
    int minute;

    // Correct Room 2 solution.
    int correctHour;
    int correctMinute;

    // Currently selected hand.
    ClockHand selectedHand;

    // Displays message after wrong answer.
    bool wrongTime;

    // Draws one clock hand onto
    // the clock face.
    void drawHand(
        char clockFace[][47],
        int clockNumber,
        int length);

    // Returns which character should
    // represent the direction of the hand.
    char getHandCharacter(
        int changeX,
        int changeY);

public:
    ClockPuzzle(
        int startX,
        int startY);

    ~ClockPuzzle() override;

    // Draws the entire Grandfather Clock UI.
    void draw() override;

    // Controls:
    //
    // A/D = Rotate
    // W/S = Change Hand
    // E   = Confirm
    // Q   = Leave
    void handleInput(
        char input) override;

    // Checks whether the clock
    // is showing the correct time.
    bool checkSolution() override;
};