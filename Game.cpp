#include "Game.h"

#include <cstdlib>
#include <iostream>
#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// =====================================
// CONSTRUCTOR
// =====================================

// IMPORTANT:
//
// Room no longer has a default constructor.
//
// : room(1)
//
// tells C++:
// "Construct room as Room 1."
Game::Game()
    : room(1)
{
    currentState = ROOM_STATE;

    activePuzzle = nullptr;

    selectedInventorySlot = 0;

    screenNeedsClear = true;
    running = true;

    map.generateMap();
}

// =====================================
// CONSOLE
// =====================================

char Game::readKey()
{
#ifdef _WIN32
    int input = _getch();

    // Arrow and function keys produce a two-byte sequence.
    if (input == 0 || input == 224)
    {
        _getch();
        return '\0';
    }
#else
    termios originalSettings;
    bool terminalConfigured =
        tcgetattr(STDIN_FILENO, &originalSettings) == 0;

    if (terminalConfigured)
    {
        termios rawSettings = originalSettings;
        rawSettings.c_lflag &=
            static_cast<tcflag_t>(~(ICANON | ECHO));

        tcsetattr(
            STDIN_FILENO,
            TCSANOW,
            &rawSettings);
    }

    int input = std::cin.get();

    if (terminalConfigured)
    {
        tcsetattr(
            STDIN_FILENO,
            TCSANOW,
            &originalSettings);
    }

    // Match the values returned by _getch() on Windows.
    if (input == 127)
    {
        input = 8;
    }
    else if (input == '\n')
    {
        input = 13;
    }
#endif

    if (input == EOF)
    {
        return 27;
    }

    return static_cast<char>(input);
}

void Game::moveCursorToTop()
{
#ifdef _WIN32
    HANDLE consoleHandle =
        GetStdHandle(
            STD_OUTPUT_HANDLE);

    COORD cursorPosition;

    cursorPosition.X = 0;
    cursorPosition.Y = 0;

    SetConsoleCursorPosition(
        consoleHandle,
        cursorPosition);
#else
    std::cout << "\x1B[H" << std::flush;
#endif
}

void Game::clearScreen()
{
#ifdef _WIN32
    HANDLE consoleHandle =
        GetStdHandle(
            STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO
        screenInfo;

    GetConsoleScreenBufferInfo(
        consoleHandle,
        &screenInfo);

    DWORD consoleSize =
        screenInfo.dwSize.X *
        screenInfo.dwSize.Y;

    DWORD charactersWritten;

    COORD topLeft;

    topLeft.X = 0;
    topLeft.Y = 0;

    FillConsoleOutputCharacter(
        consoleHandle,
        ' ',
        consoleSize,
        topLeft,
        &charactersWritten);

    FillConsoleOutputAttribute(
        consoleHandle,
        screenInfo.wAttributes,
        consoleSize,
        topLeft,
        &charactersWritten);

    SetConsoleCursorPosition(
        consoleHandle,
        topLeft);
#else
    std::cout << "\x1B[2J\x1B[H" << std::flush;
#endif
}

// =====================================
// MAIN LOOP
// =====================================

void Game::run()
{
    while (running)
    {
        if (screenNeedsClear == true)
        {
            clearScreen();

            screenNeedsClear = false;
        }
        else
        {
            moveCursorToTop();
        }

        draw();

        char input = readKey();

        if (input == 27)
        {
            running = false;
        }
        else
        {
            handleInput(input);
        }
    }
}

// =====================================
// DRAW
// =====================================

void Game::draw()
{
    // ROOM
    if (currentState == ROOM_STATE)
    {
        room.drawRoom(
            player.getX(),
            player.getY(),
            false);
    }

    // MAP
    else if (currentState == MAP_STATE)
    {
        map.drawMap();

        std::cout << std::endl;

        std::cout
            << "A / D - Select Path"
            << std::endl;

        std::cout
            << "E     - Confirm Path"
            << std::endl;

        std::cout
            << "N     - Inventory"
            << std::endl;

        std::cout
            << "Q     - Stand Up"
            << std::endl;
    }

    // CARD BATTLE
    else if (
        currentState ==
        CARD_BATTLE_STATE)
    {
        std::cout
            << "================ CARD BATTLE ================"
            << std::endl;

        std::cout << std::endl;

        if (map.isAtFinalNode()
            == true)
        {
            std::cout
                << "BOSS BATTLE"
                << std::endl;
        }
        else
        {
            std::cout
                << "Enemy Encounter"
                << std::endl;
        }

        std::cout << std::endl;

        std::cout
            << "Card Battle system will go here."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "E - Win Battle (TEST)"
            << std::endl;
    }

    // SHOP
    else if (
        currentState ==
        SHOP_STATE)
    {
        std::cout
            << "================ ITEM SHOP ================"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "A strange merchant waits behind the counter."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Q - Leave Shop"
            << std::endl;
    }

    // BACKPACK
    else if (
        currentState ==
        BACKPACK_STATE)
    {
        std::cout
            << "================ BACKPACK ================"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "You find an abandoned backpack."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "E - Take Item"
            << std::endl;

        std::cout
            << "Q - Leave"
            << std::endl;
    }

    // Inventory
    else if (currentState ==
        INVENTORY_STATE)
        {
            std::cout
                << "================ INVENTORY ================"
                << std::endl;

            std::cout << std::endl;

            inventory.OpenInv();

            std::cout << std::endl;

            std::cout
                << "Selected Slot: "
                << selectedInventorySlot + 1
                << std::endl;

            std::cout << std::endl;

            std::cout
                << "W / S - Select Slot"
                << std::endl;

            std::cout
                << "E     - Use Item"
                << std::endl;

            std::cout
                << "N / Q - Close Inventory"
                << std::endl;
                }

    // PUZZLE
    else if (
        currentState ==
        PUZZLE_STATE)
    {
        if (activePuzzle != nullptr)
        {
            // POLYMORPHISM:
            //
            // Room 1:
            // KeypadPuzzle::draw()
            //
            // Room 2:
            // ClockPuzzle::draw()
            activePuzzle->draw();
        }
    }
}

// =====================================
// HANDLE INPUT
// =====================================

void Game::handleInput(
    char input)
{
    if (currentState ==
        ROOM_STATE)
    {
        handleRoomInput(input);
    }

    else if (currentState ==
        MAP_STATE)
    {
        handleMapInput(input);
    }

    else if (currentState ==
        CARD_BATTLE_STATE)
    {
        handleCardBattleInput(input);
    }

    else if (currentState ==
        SHOP_STATE)
    {
        handleShopInput(input);
    }

    else if (currentState ==
        BACKPACK_STATE)
    {
        handleBackpackInput(input);
    }

    else if (currentState ==
        INVENTORY_STATE)
    {
        handleInventoryInput(input);
    }

    else if (currentState ==
        PUZZLE_STATE)
    {
        handlePuzzleInput(input);
    }
}

// =====================================
// ROOM INPUT
// =====================================

void Game::handleRoomInput(
    char input)
{
    // WASD movement.
    if (input == 'W' ||
        input == 'w' ||
        input == 'A' ||
        input == 'a' ||
        input == 'S' ||
        input == 's' ||
        input == 'D' ||
        input == 'd')
    {
        player.move(
            input,
            &room);
    }

    // E = Interact.
    else if (
        input == 'E' ||
        input == 'e')
    {
        Interactable* object =
            getPlayerInteractable();

        if (object != nullptr)
        {
            InteractionResult result =
                object->interact();

            // ========================
            // CARD TABLE
            // ========================

            if (result == OPEN_MAP)
            {
                std::cout << std::endl;

                std::cout
                    << "Are you sure you want to sit down? [Y/N] ";

                char choice = readKey();

                if (choice == 'Y' ||
                    choice == 'y')
                {
                    currentState =
                        MAP_STATE;
                }

                screenNeedsClear =
                    true;
            }

            // ========================
            // PUZZLE
            // ========================

            else if (
                result ==
                OPEN_PUZZLE)
            {
                // Generic!
                //
                // Room 1 returns KeypadPuzzle.
                // Room 2 returns ClockPuzzle.
                activePuzzle =
                    room.getPuzzle();

                if (activePuzzle != nullptr)
                {
                    activePuzzle->
                        setExitRequested(false);

                    currentState =
                        PUZZLE_STATE;

                    screenNeedsClear =
                        true;
                }
            }

            // ========================
            // OPEN DOOR
            // ========================

            else if (
                result ==
                OPEN_DOOR)
            {
                clearScreen();

                std::cout
                    << "The door opens."
                    << std::endl;

                std::cout << std::endl;

                std::cout
                    << "Room "
                    << room.getRoomNumber()
                    << " complete!"
                    << std::endl;

                std::cout << std::endl;

                std::cout
                    << "Press any key to continue."
                    << std::endl;

                readKey();

                // NEW:
                // Go to the next room.
                goToNextRoom();

                screenNeedsClear =
                    true;
            }

            // ========================
            // LOCKED
            // ========================

            else if (
                result ==
                LOCKED)
            {
                std::cout << std::endl;

                std::cout
                    << "It is currently locked."
                    << std::endl;

                readKey();

                screenNeedsClear =
                    true;
            }
        }
    }
}

// =====================================
// PLAYER INTERACTION POSITION
// =====================================

Interactable*
Game::getPlayerInteractable()
{
    int interactionX =
        player.getX();

    int interactionY =
        player.getY();

    char direction =
        player.getFacingDirection();

    if (direction == 'W')
    {
        interactionY--;
    }

    else if (direction == 'S')
    {
        interactionY++;
    }

    else if (direction == 'A')
    {
        interactionX--;
    }

    else if (direction == 'D')
    {
        interactionX++;
    }

    return room.getInteractableAt(
        interactionX,
        interactionY);
}

// =====================================
// MAP
// =====================================

void Game::handleMapInput(
    char input)
{
    // Select left path.
    if (input == 'A' ||
        input == 'a')
    {
        map.selectLeft();
    }

    // Select right path.
    else if (input == 'D' ||
        input == 'd')
    {
        map.selectRight();
    }

    // Confirm selected path.
    else if (input == 'E' ||
        input == 'e')
    {
        if (map.travelSelected() ==
            true)
        {
            activateCurrentMapNode();

            screenNeedsClear =
                true;
        }
    }

    // Open inventory.
    //
    // This exists only inside MAP_STATE.
    else if (input == 'N' ||
        input == 'n')
    {
        selectedInventorySlot =
            0;

        currentState =
            INVENTORY_STATE;

        screenNeedsClear =
            true;
    }

    // Stand up from the table.
    else if (input == 'Q' ||
        input == 'q')
    {
        std::cout << std::endl;

        std::cout
            << "Are you sure you want to stand up? [Y/N] ";

        char choice =
            readKey();

        if (choice == 'Y' ||
            choice == 'y')
        {
            currentState =
                ROOM_STATE;
        }

        screenNeedsClear =
            true;
    }
}

// =====================================
// ACTIVATE MAP NODE
// =====================================

void Game::activateCurrentMapNode()
{
    MapNode* node =
        map.getCurrentNode();

    if (node == nullptr)
    {
        return;
    }

    NodeType type =
        node->getType();

    if (type == FIGHT)
    {
        currentState =
            CARD_BATTLE_STATE;
    }

    else if (type == SHOP)
    {
        currentState =
            SHOP_STATE;
    }

    else if (type == BACKPACK)
    {
        currentState =
            BACKPACK_STATE;
    }
}

// =====================================
// CARD BATTLE
// =====================================

void Game::handleCardBattleInput(
    char input)
{
    // TEMPORARY:
    // E automatically wins.
    if (input == 'E' ||
        input == 'e')
    {
        if (map.isAtFinalNode()
            == true)
        {
            // ============================
            // ROOM 1 BOSS
            // ============================

            if (room.getRoomNumber() == 1)
            {
                // Unlock Room 1's Keypad.
                //
                // This replaces the OLD:
                //
                // setKeypadUnlocked()
                room.setPuzzleUnlocked(true);
            }

            clearScreen();

            std::cout
                << "================ BOSS DEFEATED ================"
                << std::endl;

            std::cout << std::endl;

            std::cout
                << "The enemy falls."
                << std::endl;

            std::cout << std::endl;

            // Room 1 reveals the Keypad code.
            if (room.getRoomNumber() == 1)
            {
                std::cout
                    << "You remember the code: '9473'"
                    << std::endl;
            }

            // Room 2 Clock is already unlocked,
            // so the boss does not need to unlock it.
            else if (
                room.getRoomNumber() == 2)
            {
                std::cout
                    << "The room falls silent."
                    << std::endl;
            }

            std::cout << std::endl;

            std::cout
                << "Press any key to continue."
                << std::endl;

            readKey();
        }

        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}



// =====================================
// SHOP
// =====================================

void Game::handleShopInput(
    char input)
{
    if (input == 'Q' ||
        input == 'q')
    {
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}

// =====================================
// BACKPACK
// =====================================

void Game::handleBackpackInput(
    char input)
{
    if (input == 'E' ||
        input == 'e')
    {
        // Choose one of the ten items
        // from itemDatabase.
        int itemIndex =
            std::rand() % 10;

        // Store it in the first
        // available inventory slot.
        inventory.RecivedInv(
            itemIndex);

        std::cout << std::endl;

        std::cout
            << "You store the item in your inventory."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to continue."
            << std::endl;

        readKey();

        // Return to the board-game map.
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }

    else if (input == 'Q' ||
        input == 'q')
    {
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}

// INVENTORY

void Game::handleInventoryInput(
    char input)
{
    // Previous inventory slot.
    if (input == 'W' ||
        input == 'w')
    {
        selectedInventorySlot--;

        if (selectedInventorySlot <
            0)
        {
            selectedInventorySlot =
                15;
        }
    }

    // Next inventory slot.
    else if (input == 'S' ||
        input == 's')
    {
        selectedInventorySlot++;

        if (selectedInventorySlot >
            15)
        {
            selectedInventorySlot =
                0;
        }
    }

    // Use selected item.
    else if (input == 'E' ||
        input == 'e')
    {
        std::cout << std::endl;

        inventory.UsedInv(
            selectedInventorySlot);

        std::cout << std::endl;

        std::cout
            << "Press any key to continue."
            << std::endl;

        readKey();

        screenNeedsClear =
            true;
    }

    // Close inventory.
    else if (input == 'N' ||
        input == 'n' ||
        input == 'Q' ||
        input == 'q')
    {
        // Always return to the board-game map,
        // never to the room.
        currentState =
            MAP_STATE;

        screenNeedsClear =
            true;
    }
}

// =====================================
// PUZZLE
// =====================================

void Game::handlePuzzleInput(
    char input)
{
    if (activePuzzle != nullptr)
    {
        // Polymorphism:
        //
        // Keypad handles numbers.
        // Clock handles WASD/E.
        activePuzzle->
            handleInput(input);

        // ============================
        // SOLVED
        // ============================

        if (activePuzzle->
            getSolved() == true)
        {
            // Both Room 1 and Room 2
            // puzzles unlock their exit door.
            room.setDoorUnlocked(true);

            clearScreen();

            activePuzzle->draw();

            std::cout << std::endl;

            std::cout
                << "The exit door has been unlocked."
                << std::endl;

            std::cout << std::endl;

            std::cout
                << "Press any key to continue."
                << std::endl;

            readKey();

            currentState =
                ROOM_STATE;

            activePuzzle =
                nullptr;

            screenNeedsClear =
                true;
        }

        // ============================
        // Q = LEAVE
        // ============================

        else if (
            activePuzzle->
            getExitRequested() == true)
        {
            activePuzzle->
                setExitRequested(false);

            currentState =
                ROOM_STATE;

            activePuzzle =
                nullptr;

            screenNeedsClear =
                true;
        }
    }
}

// =====================================
// ROOM TRANSITION
// =====================================

void Game::goToNextRoom()
{
    int currentRoomNumber =
        room.getRoomNumber();

    // ============================
    // ROOM 1 -> ROOM 2
    // ============================

    if (currentRoomNumber == 1)
    {
        // Turn our existing Room object
        // into Room 2.
        room.loadRoom(2);

        // Reset player to starting point.
        player.resetPosition();

        // Generate a new progression map
        // for Room 2.
        map.generateMap();

        activePuzzle = nullptr;

        currentState =
            ROOM_STATE;

        clearScreen();

        std::cout
            << "You step through the doorway..."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Something feels different here."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to enter Room 2."
            << std::endl;

        readKey();
    }

    // ============================
    // ROOM 2 -> ROOM 3
    // ============================

 // ============================
// ROOM 2 -> ROOM 3
// ============================

    else if (currentRoomNumber == 2)
    {
        // Turn existing Room object
        // into Room 3.
        room.loadRoom(3);

        // Reset player position.
        player.resetPosition();

        // Generate Room 3's map.
        map.generateMap();

        activePuzzle =
            nullptr;

        currentState =
            ROOM_STATE;

        clearScreen();

        std::cout
            << "You step through the doorway..."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "A strange safe waits in the darkness."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to enter Room 3."
            << std::endl;

        readKey();
    }
    
// ============================
// ROOM 3 COMPLETE
// ============================

    else if (currentRoomNumber == 3)
    {
        clearScreen();

        std::cout
            << "Room 3 complete!"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "The final door opens."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "You escaped!"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to finish."
            << std::endl;

        readKey();

        running = false;
    }

}
