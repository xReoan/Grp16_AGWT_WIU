#pragma once

#include "Interactable.h"
#include "CardTable.h"
#include "Puzzle.h"
#include "KeypadPuzzle.h"
#include "ClockPuzzle.h"
#include "Door.h"

class Room
{
private:
    static const int WIDTH = 50;
    static const int HEIGHT = 20;

    char roomLayout[HEIGHT][WIDTH];

    int roomNumber;

    // All objects that can be interacted with.
    Interactable* interactables[10];

    int interactableCount;

    // Important objects belonging to the room.
    CardTable* cardTable;
    Puzzle* puzzle;
    Door* exitDoor;

    // Adds an Interactable to the room.
    void addInteractable(
        Interactable* object);

    // Deletes all interactables belonging
    // to the current room.
    void clearInteractables();

    // Creates objects depending on room number.
    void createRoomObjects();

    // UI drawing.
    void clearRoom();
    void drawWalls();
    void drawTable();
    void drawPuzzle();
    void drawDoor();
    void drawFurniture();

public:
    // Room(1) = Keypad
    // Room(2) = Grandfather Clock
    Room(int number);

    ~Room();

    // Changes this Room object into
    // another room.
    void loadRoom(int number);

    void createRoom();

    void drawRoom(
        int playerX,
        int playerY,
        bool playerSeated);

    // Collision detection.
    bool isWalkable(
        int x,
        int y);

    // Interaction detection.
    Interactable* getInteractableAt(
        int x,
        int y);

    int getRoomNumber();

    // Generic Puzzle functions.
    Puzzle* getPuzzle();

    bool getPuzzleUnlocked();

    void setPuzzleUnlocked(
        bool unlocked);

    // Door functions.
    Door* getDoor();

    bool getDoorUnlocked();

    void setDoorUnlocked(
        bool unlocked);
};