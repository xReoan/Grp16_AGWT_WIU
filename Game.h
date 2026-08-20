#pragma once

#include "Room.h"
#include "Player.h"
#include "RunMap.h"
#include "Interactable.h"
#include "Puzzle.h"

enum GameState
{
    ROOM_STATE,
    MAP_STATE,

    CARD_BATTLE_STATE,
    SHOP_STATE,
    BACKPACK_STATE,

    PUZZLE_STATE
};

class Game
{
private:
    Room room;
    Player player;
    Map map;

    GameState currentState;

    Puzzle* activePuzzle;

    bool screenNeedsClear;
    bool running;

    // Console.
    char readKey();
    void moveCursorToTop();
    void clearScreen();

    // General.
    void draw();
    void handleInput(char input);

    // State controls.
    void handleRoomInput(char input);
    void handleMapInput(char input);
    void handleCardBattleInput(char input);
    void handleShopInput(char input);
    void handleBackpackInput(char input);
    void handlePuzzleInput(char input);

    // Returns Interactable directly
    // in front of player.
    Interactable* getPlayerInteractable();

    // Activates F / S / B node.
    void activateCurrentMapNode();

    // NEW:
    // Handles Room 1 -> Room 2 etc.
    void goToNextRoom();

public:
    Game();

    void run();
};
