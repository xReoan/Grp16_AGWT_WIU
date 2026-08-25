#pragma once

#include "Room.h"
#include "Player.h"
#include "RunMap.h"
#include "Interactable.h"
#include "BattleManager.h"
#include "CardDatabase.h"
#include "Enemy.h"
#include "Puzzle.h"
#include "inv.h"
#include "revisedshop.h"
#include "itemDatabase.h"
#include <string>

enum GameState
{
    ROOM_STATE,
    MAP_STATE,

    BATTLE_STATE,
    SHOP_STATE,
    BACKPACK_STATE,
    INVENTORY_STATE,

    PUZZLE_STATE
};

class Game
{
private:
    Room room;
    Player player;
    Map map;
    CardDatabase cardDatabase;
    // Backpack UI selection.
    // 0 to 2 are database items.
    // 3 is the fixed coin reward.
    int selectedBackpackItem;

    // Stores the database indexes of the
    // three randomly generated items.
    int backpackItemIndices[3];

    // Used to access the actual database items.
    itemDatabase backpackDatabase;

    // Generates three unique database items
    // whenever a backpack event begins.
    void generateBackpackItems();

    std::string getBackpackItemName(
        int choiceIndex) const;

    // Player's inventory.
    inv inventory;

    revisedshop shopkeeper;

    GameState currentState;

    Puzzle* activePuzzle;

    // Inventory slot currently selected.
    // Uses values from 0 to 15.
    int selectedInventorySlot;
    bool isTutorialBattleDone = false;
    bool screenNeedsClear;
    bool running;

    // Console.
    char readKey();
    void moveCursorToTop();
    void clearScreen();

    // General.
    void draw();
    void handleInput(char input);

    void startBattle();

    // State controls.
    void handleRoomInput(char input);
    void handleMapInput(char input);
    void handleCardBattleInput(char input);
    void handleShopInput(char input);
    void handleBackpackInput(char input);
    void handleInventoryInput(char input);
    void handlePuzzleInput(char input);

    // Returns Interactable directly
    // in front of player.
    Interactable* getPlayerInteractable();

    // Activates F / S / B node.
    void activateCurrentMapNode();

    // Handles Room 1 -> Room 2 etc.
    void goToNextRoom();

public:
    Game();

    void run();
};
