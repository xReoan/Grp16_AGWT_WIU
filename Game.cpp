#include "Game.h"
#include "InspectableObject.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

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

    selectedBackpackItem = 0;
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

// 
// =====================================
// GENERATE BACKPACK REWARDS
// =====================================

void Game::generateBackpackItems()
{
    int itemCount =
        backpackDatabase.getItemCount();

    for (int i = 0; i < 3; i++)
    {
        bool duplicateItem;

        do
        {
            backpackItemIndices[i] =
                std::rand() % itemCount;

            duplicateItem = false;

            // Check the previously generated choices.
            for (int j = 0; j < i; j++)
            {
                if (backpackItemIndices[i] ==
                    backpackItemIndices[j])
                {
                    duplicateItem = true;
                }
            }

        } while (duplicateItem == true);
    }
}

// =====================================
// GET BACKPACK REWARD NAME
// =====================================

std::string Game::getBackpackItemName(
    int choiceIndex) const
{
    // Choice 3 is not a database item.
    if (choiceIndex == 3)
    {
        return "5 Coins";
    }

    if (choiceIndex < 0 ||
        choiceIndex >= 3)
    {
        return "Unknown";
    }

    int databaseIndex =
        backpackItemIndices[choiceIndex];

    item* selectedItem =
        backpackDatabase.getitem(
            databaseIndex);

    if (selectedItem == nullptr)
    {
        return "Unknown";
    }

    return selectedItem->getname();
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

        shopkeeper.ShopMenu();
        
        std::cout
            << "Q - Leave Shop"
            << std::endl;
    }

    // Abandoned Backpack Event

    else if (
        currentState ==
        BACKPACK_STATE)
    {
        // A larger width is needed because
        // database item names may be longer.
        const int backpackWidth = 72;

        auto drawBackpackLine =
            [backpackWidth](
                const std::string& text)
            {
                std::cout
                    << "| "
                    << std::left
                    << std::setw(backpackWidth)
                    << text
                    << " |"
                    << std::endl;
            };

        std::cout
            << "+"
            << std::string(
                backpackWidth + 2,
                '-')
            << "+"
            << std::endl;

        drawBackpackLine(
            "A weathered backpack lies abandoned.");

        drawBackpackLine("");

        drawBackpackLine(
            "                         CHOOSE ONE");

        drawBackpackLine("");

        std::ostringstream itemLine;

        // Choices 0 to 2 are random items.
        // Choice 3 is always 5 Coins.
        for (int i = 0; i < 4; i++)
        {
            if (i ==
                selectedBackpackItem)
            {
                itemLine
                    << ">["
                    << getBackpackItemName(i)
                    << "]<";
            }
            else
            {
                itemLine
                    << "["
                    << getBackpackItemName(i)
                    << "]";
            }

            if (i < 3)
            {
                itemLine << "  ";
            }
        }

        drawBackpackLine(
            itemLine.str());

        drawBackpackLine("");

        drawBackpackLine(
            "A/D Select                         E Take");

        std::cout
            << "+"
            << std::string(
                backpackWidth + 2,
                '-')
            << "+"
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

            //prints out armor and weapon epuipped status
            if (player.getequippedbasicweapon() == nullptr) {
                std::cout << "You have no basic weapon" << std::endl;
            }
            else {
                std::cout<<"You have basic weapon "<<(player.getequippedbasicweapon())->getname() << " equipped" << std::endl;
            }

            if (player.getequippedadvancedweapon() == nullptr) {
                std::cout << "You have no advanced weapon" << std::endl;
            }
            else {
                std::cout << "You have advanced weapon " << (player.getequippedadvancedweapon())->getname() << " equipped" << std::endl;
            }

            if (player.getequippedbasicarmor() == nullptr) {
                std::cout << "You have no basic armor" << std::endl;
            }
            else {
                std::cout << "You have basic armor " << (player.getequippedbasicarmor())->getname() << " equipped" << std::endl;
            }

            if (player.getequippedadvancedarmor() == nullptr) {
                std::cout << "You have no advanced armor" << std::endl;
            }
            else {
                std::cout << "You have advanced armor " << (player.getequippedadvancedarmor())->getname() << " equipped" << std::endl;
            }

            std::cout << std::endl;

            std::cout
                << "Selected Slot: ";
                if (selectedInventorySlot + 1 < 10) {
                    std::cout << selectedInventorySlot + 1<< " ";
                }
                else {
                    std::cout << selectedInventorySlot + 1;
                }
                std::cout<< std::endl;

            std::cout << std::endl;

            std::cout
                << "W / S - Select Slot"
                << std::endl;

            std::cout
                << "E     - Use Item"
                << std::endl;

            std::cout
                << "R     - Unequip weapon/armor"
                << std::endl;

            std::cout
                << "I     - Inspect"
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

           // ========================
           // INSPECTABLE OBJECT
           // ========================

            else if (
                result ==
                SHOW_DIALOGUE)
                {
                    InspectableObject* inspectedObject =
                        dynamic_cast<InspectableObject*>(
                            object);

                    if (inspectedObject !=
                        nullptr)
                    {
                        clearScreen();

                        std::cout
                            << "================ "
                            << inspectedObject->getName()
                            << " ================"
                            << std::endl;

                        std::cout << std::endl;

                        std::cout
                            << inspectedObject->getDialogue()
                            << std::endl;

                        std::cout << std::endl;

                        std::cout
                            << "Press any key to continue."
                            << std::endl;

                        readKey();

                        screenNeedsClear =
                            true;
                    }
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

    if (node ==
        nullptr)
    {
        return;
    }

    NodeType type =
        node->getType();

    if (type ==
        FIGHT)
    {
        currentState =
            CARD_BATTLE_STATE;
    }

    else if (type ==
        SHOP)
    {
        currentState =
            SHOP_STATE;
    }

    else if (type ==
        BACKPACK)
    {
        // Generate the choices only once
        // when entering this event.
        generateBackpackItems();

        // Begin with the first reward selected.
        selectedBackpackItem =
            0;

        currentState =
            BACKPACK_STATE;

        screenNeedsClear =
            true;
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
            //lock puzzle 3 and 4
            if (room.getRoomNumber() == 3 || room.getRoomNumber() == 4) {
                room.setPuzzleUnlocked(true);
            }
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
    // =====================================
    // A = PREVIOUS REWARD
    // =====================================

    if (input == 'A' ||
        input == 'a')
    {
        selectedBackpackItem--;

        if (selectedBackpackItem < 0)
        {
            selectedBackpackItem = 3;
        }
    }

    // =====================================
    // D = NEXT REWARD
    // =====================================

    else if (input == 'D' ||
        input == 'd')
    {
        selectedBackpackItem++;

        if (selectedBackpackItem > 3)
        {
            selectedBackpackItem = 0;
        }
    }

    // =====================================
    // E = TAKE SELECTED REWARD
    // =====================================

    else if (input == 'E' ||
        input == 'e')
    {
        clearScreen();

        // Choice 3 is always 5 Coins.
        if (selectedBackpackItem == 3)
        {
            std::cout
                << "You find a small pouch containing "
                << "5 coins."
                << std::endl;

            std::cout << std::endl;

            shopkeeper.AddCoins(5);
        }
        else
        {
            int databaseIndex =
                backpackItemIndices[
                    selectedBackpackItem];

            item* selectedItem =
                backpackDatabase.getitem(
                    databaseIndex);

            if (selectedItem != nullptr)
            {
                std::cout
                    << "You take the "
                    << selectedItem->getname()
                    << "."
                    << std::endl;

                std::cout << std::endl;

                // Store the actual database index
                // inside the player's inventory.
                inventory.ReceivedInv(
                    databaseIndex);

                std::cout
                    << "The item was placed "
                    << "in your inventory."
                    << std::endl;
            }
            else
            {
                std::cout
                    << "The selected item could "
                    << "not be found."
                    << std::endl;
            }
        }

        std::cout << std::endl;

        std::cout
            << "Press any key to continue."
            << std::endl;

        readKey();

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

        switch (inventory.checkingType(selectedInventorySlot)) {
        case 0:
            player.equiparmor(inventory.getarmorInv(selectedInventorySlot));
            std::cout << "Equipped armor " << inventory.getarmorInv(selectedInventorySlot)->getname() << std::endl;
            break;
        case 1:
            player.equipweapon(inventory.getweaponInv(selectedInventorySlot));
            std::cout << "Equipped weapon " << inventory.getweaponInv(selectedInventorySlot)->getname() << std::endl;
            break;
        default:
            std::cout << "nothing happened" << std::endl;
        }

        std::cout << std::endl;

        std::cout
            << "Press any key to continue."
            << std::endl;

        readKey();

        screenNeedsClear =
            true;
    }

    // Unequipping
    else if (input == 'R' ||
        input == 'r') 
    {
        switch (inventory.checkingType(selectedInventorySlot)) {
        case 0:
            player.unequiparmor(inventory.getarmorInv(selectedInventorySlot));
            break;
        case 1:
            player.unequipweapon(inventory.getweaponInv(selectedInventorySlot));
            break;
        default:
            std::cout << "nothing happened" << std::endl;
        }
    }

    else if (input == 'I' ||
        input == 'i') {
        inventory.inspecting(selectedInventorySlot);

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
            << "This feels... weird. It feels like the room is spinning"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to enter Room 3."
            << std::endl;

        readKey();
    }
    
    // ============================
    // ROOM 3 -> ROOM 4
    // ============================

    else if (currentRoomNumber == 3)
    {
        room.loadRoom(4);

        player.resetPosition();

        map.generateMap();

        activePuzzle = nullptr;

        currentState = ROOM_STATE;

        clearScreen();

        std::cout
            << "Watch out!"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "There's a bunch of traps"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to enter Room 4."
            << std::endl;

        readKey();
    }
    // ============================
  // ROOM 4 -> ROOM 5
  // ============================

    else if (currentRoomNumber == 4)
    {
        room.loadRoom(5);

        player.resetPosition();

        map.generateMap();

        activePuzzle = nullptr;

        currentState = ROOM_STATE;

        clearScreen();

        std::cout
            << "You walk in..."
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "There's someone waiting for you"
            << std::endl;

        std::cout << std::endl;

        std::cout
            << "Press any key to enter Room 5."
            << std::endl;

        readKey();
        }
    // ============================
    // ENDING
    // ============================
    else if (currentRoomNumber == 5)
    {
        clearScreen();

        std::cout
            << "Room 5 complete!"
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
