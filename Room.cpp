#include "Room.h"

#include <iostream>

// =====================================
// CONSTRUCTOR
// =====================================

Room::Room(int number)
{
    roomNumber = number;

    interactableCount = 0;

    cardTable = nullptr;
    puzzle = nullptr;
    exitDoor = nullptr;

    for (int i = 0; i < 10; i++)
    {
        interactables[i] = nullptr;
    }

    createRoomObjects();

    createRoom();
}

// =====================================
// DESTRUCTOR
// =====================================

Room::~Room()
{
    clearInteractables();
}

// =====================================
// DELETE CURRENT ROOM OBJECTS
// =====================================

void Room::clearInteractables()
{
    for (int i = 0;
        i < interactableCount;
        i++)
    {
        if (interactables[i] != nullptr)
        {
            delete interactables[i];

            interactables[i] = nullptr;
        }
    }

    interactableCount = 0;

    // These pointers were pointing at objects
    // that were just deleted above.
    cardTable = nullptr;
    puzzle = nullptr;
    exitDoor = nullptr;

    for (int i = 0; i < 10; i++)
    {
        interactables[i] = nullptr;
    }
}

// =====================================
// LOAD NEW ROOM
// =====================================

void Room::loadRoom(int number)
{
    // Delete objects belonging
    // to the old room.
    clearInteractables();

    // Change room number.
    roomNumber = number;

    // Create objects belonging
    // to the new room.
    createRoomObjects();

    // Rebuild the UI.
    createRoom();
}

// =====================================
// ADD INTERACTABLE
// =====================================

void Room::addInteractable(
    Interactable* object)
{
    if (object != nullptr &&
        interactableCount < 10)
    {
        interactables[interactableCount]
            = object;

        interactableCount++;
    }
}

// =====================================
// CREATE ROOM OBJECTS
// =====================================

void Room::createRoomObjects()
{
    // =====================================
    // ROOM 1
    // =====================================

    if (roomNumber == 1)
    {
        // CARD TABLE
        cardTable =
            new CardTable(
                16,
                7,
                18,
                5);

        addInteractable(cardTable);

        // KEYPAD
        puzzle =
            new KeypadPuzzle(
                39,
                2);

        // The final Room 1 fight reveals the code
        // and unlocks access to the keypad.
        puzzle->setUnlocked(true);

        addInteractable(puzzle);

        // EXIT DOOR
        exitDoor =
            new Door(
                39,
                4);

        // CABINET
        addInteractable(
            new InspectableObject(
                6,
                14,
                9,
                1,
                "Cabinet",
                "|--------------------\n"
                "|   SECURITY ACCESS  \n"
                "|                    \n"
                "|       CODE: 9 4    \n"
                "|                    \n"
                "|--------------------\n"
                "Part of the code is missing"));

        // CHAIR
        addInteractable(
            new InspectableObject(
                35,
                14,
                7,
                1,
                "Chair",
                "Resting"));

        exitDoor->setUnlocked(false);

        addInteractable(exitDoor);
    }

    // =====================================
    // ROOM 2
    // =====================================

    else if (roomNumber == 2)
    {
        // GRANDFATHER CLOCK
        puzzle =
            new ClockPuzzle(
                3,
                2);

        // ClockPuzzle itself starts unlocked.
        addInteractable(puzzle);

        // EXIT DOOR
        exitDoor =
            new Door(
                39,
                2);

        exitDoor->setUnlocked(false);

        addInteractable(exitDoor);

        // BOOKSHELF
        addInteractable(
            new InspectableObject(
                5,
                15,
                11,
                1,
                "Bookshelf",
                "Placeholder: Most of the books "
                "are too damaged to read."));

        // BROKEN LAMP
        addInteractable(
            new InspectableObject(
                34,
                15,
                13,
                1,
                "Broken Lamp",
                "Placeholder: The lamp no longer works. "
                "Its bulb has turned completely black."));

        // CARD TABLE
        cardTable =
            new CardTable(
                15,
                8,
                20,
                5);

        addInteractable(cardTable);
    }
// =====================================
// ROOM 3
// =====================================
    else if (roomNumber == 3)
    {
        // TRICKSTER CUP PUZZLE
        puzzle =
            new TricksterPuzzle(
                3,
                2);

        puzzle->setUnlocked(false);

        addInteractable(puzzle);

        // EXIT DOOR
        exitDoor =
            new Door(
                39,
                2);

        exitDoor->setUnlocked(false);

        addInteractable(exitDoor);

        // CARD TABLE
        cardTable =
            new CardTable(
                15,
                8,
                20,
                5);

        addInteractable(cardTable);
    }

    // =====================================
    // ROOM 4
    // =====================================
    else if (roomNumber == 4)
    {
        // TRICKSTER CUP PUZZLE
        puzzle =
            new SurvivorPuzzle(
                3,
                2);

        puzzle->setUnlocked(false);

        addInteractable(puzzle);

        // EXIT DOOR
        exitDoor =
            new Door(
                39,
                2);

        exitDoor->setUnlocked(false);

        addInteractable(exitDoor);

        // CARD TABLE
        cardTable =
            new CardTable(
                15,
                8,
                20,
                5);

        addInteractable(cardTable);
    }

// =====================================
// ROOM 4
// =====================================

    else if (roomNumber == 5)
    {
        // ROTATING SYMBOL SAFE
        puzzle =
            new SymbolPuzzle(
                3,
                2);

        addInteractable(puzzle);

        // EXIT DOOR
        exitDoor =
            new Door(
                39,
                2);

        exitDoor->setUnlocked(false);

        addInteractable(exitDoor);

        // CARD TABLE
        cardTable =
            new CardTable(
                15,
                8,
                20,
                5);

        addInteractable(cardTable);

        addInteractable(
            new InspectableObject(
                6,
                14,
                9,
                1,
                "Cabinet",
                "You found a note\n"
                "|-------------------------------------|\n"
                "|  The beast watches beneath the moon.|\n"
                "|-------------------------------------|\n"
                "What does it mean?"));
    }
}


// =====================================
// CLEAR UI
// =====================================

void Room::clearRoom()
{
    for (int y = 0;
        y < HEIGHT;
        y++)
    {
        for (int x = 0;
            x < WIDTH;
            x++)
        {
            roomLayout[y][x] = ' ';
        }
    }
}

// =====================================
// WALLS
// =====================================

void Room::drawWalls()
{
    // Top and bottom.
    for (int x = 0;
        x < WIDTH;
        x++)
    {
        roomLayout[0][x] = '-';

        roomLayout[HEIGHT - 1][x]
            = '-';
    }

    // Left and right.
    for (int y = 0;
        y < HEIGHT;
        y++)
    {
        roomLayout[y][0] = '|';

        roomLayout[y][WIDTH - 1]
            = '|';
    }

    // Corners.
    roomLayout[0][0] = '+';

    roomLayout[0][WIDTH - 1]
        = '+';

    roomLayout[HEIGHT - 1][0]
        = '+';

    roomLayout[HEIGHT - 1][WIDTH - 1]
        = '+';
}

// =====================================
// CARD TABLE
// =====================================

void Room::drawTable()
{
    if (cardTable == nullptr)
    {
        return;
    }

    int startX =
        cardTable->getX();

    int startY =
        cardTable->getY();

    int width =
        cardTable->getWidth();

    int height =
        cardTable->getHeight();

    // Top and bottom.
    for (int x = startX;
        x < startX + width;
        x++)
    {
        roomLayout[startY][x]
            = '-';

        roomLayout[
            startY + height - 1][x]
                = '-';
    }

    // Left and right.
    for (int y = startY;
        y < startY + height;
        y++)
    {
        roomLayout[y][startX]
            = '|';

        roomLayout[y]
            [startX + width - 1]
            = '|';
    }

    // Corners.
    roomLayout[startY][startX]
        = '+';

    roomLayout[startY]
        [startX + width - 1]
        = '+';

    roomLayout[startY + height - 1]
        [startX]
        = '+';

    roomLayout[startY + height - 1]
        [startX + width - 1]
        = '+';

    const char text[] =
        "CARD TABLE";

    int textX =
        startX +
        (width - 10) / 2;

    int textY =
        startY +
        height / 2;

    for (int i = 0;
        text[i] != '\0';
        i++)
    {
        roomLayout[textY]
            [textX + i]
            = text[i];
    }
}

// =====================================
// PUZZLE UI
// =====================================

void Room::drawPuzzle()
{
    if (puzzle == nullptr)
    {
        return;
    }

    // =====================================
    // ROOM 1 - KEYPAD
    // =====================================

    if (roomNumber == 1)
    {
        int startX =
            puzzle->getX();

        int startY =
            puzzle->getY();

        if (puzzle->getUnlocked()
            == false)
        {
            const char text[] =
                "[LOCKED]";

            for (int i = 0;
                text[i] != '\0';
                i++)
            {
                roomLayout[startY]
                    [startX + i]
                    = text[i];
            }
        }
        else
        {
            const char text[] =
                "[KEYPAD]";

            for (int i = 0;
                text[i] != '\0';
                i++)
            {
                roomLayout[startY]
                    [startX + i]
                    = text[i];
            }
        }
    }

    // =====================================
    // ROOM 2 - GRANDFATHER CLOCK 
    // =====================================

    else if (roomNumber == 2)
    {
        int startX =
            puzzle->getX();

        int startY =
            puzzle->getY();

        const char line1[] =
            "+-------------------+";

        const char line2[] =
            "| GRANDFATHER CLOCK |";

        const char line3[] =
            "|         O         |";

        const char line4[] =
            "|         |         |";

        const char line5[] =
            "+-------------------+";

        for (int i = 0;
            line1[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = line1[i];

            roomLayout[startY + 1]
                [startX + i]
                = line2[i];

            roomLayout[startY + 2]
                [startX + i]
                = line3[i];

            roomLayout[startY + 3]
                [startX + i]
                = line4[i];

            roomLayout[startY + 4]
                [startX + i]
                = line5[i];
        }
    }

// =====================================
// ROOM 3 - TRICKSTER
// =====================================
    else if (roomNumber == 3)
    {
        int startX =
            puzzle->getX();

        int startY =
            puzzle->getY();

        const char line1[] =
            "|-------------------|";

        const char line2[] =
            "|  TRICKSTER GAME   |";

        const char line3[] =
            "|  [_]   [_]   [_]  |";

        const char line4[] =
            "|      3 CUPS       |";

        const char line5[] =
            "|-------------------|";

        for (int i = 0; line1[i] != '\0'; i++) {
            roomLayout[startY]
                [startX + i] = line1[i];

            roomLayout[startY + 1]
                [startX + i] = line2[i];

            roomLayout[startY + 2]
                [startX + i] = line3[i];

            roomLayout[startY + 3]
                [startX + i] = line4[i];

            roomLayout[startY + 4]
                [startX + i] = line5[i];
        }
    }
    // =====================================
    // ROOM 4 - SURVIVOR
    // =====================================
    else if (roomNumber == 4)
    {
        int startX =
            puzzle->getX();

        int startY =
            puzzle->getY();

        const char line1[] =
            "+-------------------+";

        const char line2[] =
            "|                   |";

        const char line3[] =
            "| SUBJECT RECORDS   |";

        const char line4[] =
            "|                   |";

        const char line5[] =
            "+-------------------+";

        for (int i = 0; line1[i] != '\0'; i++) {
            roomLayout[startY]
                [startX + i] = line1[i];

            roomLayout[startY + 1]
                [startX + i] = line2[i];

            roomLayout[startY + 2]
                [startX + i] = line3[i];

            roomLayout[startY + 3]
                [startX + i] = line4[i];

            roomLayout[startY + 4]
                [startX + i] = line5[i];
        }
        }
    // =====================================
    // ROOM 5 - PASSCODE
    // =====================================
    else if (roomNumber == 5)
    {
        int startX =
            puzzle->getX();

        int startY =
            puzzle->getY();

        const char line1[] =
            "+-------------------+";

        const char line2[] =
            "|   STRANGE LOCK    |";

        const char line3[] =
            "|   [ ? ? ? ? ]     |";

        const char line4[] =
            "|       SAFE        |";

        const char line5[] =
            "+-------------------+";

        for (int i = 0;
            line1[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = line1[i];

            roomLayout[startY + 1]
                [startX + i]
                = line2[i];

            roomLayout[startY + 2]
                [startX + i]
                = line3[i];

            roomLayout[startY + 3]
                [startX + i]
                = line4[i];

            roomLayout[startY + 4]
                [startX + i]
                = line5[i];
        }
    }
}

// =====================================
// DOOR
// =====================================

void Room::drawDoor()
{
    if (exitDoor == nullptr)
    {
        return;
    }

    int startX =
        exitDoor->getX();

    int startY =
        exitDoor->getY();

    if (exitDoor->getUnlocked()
        == false)
    {
        const char text[] =
            "[LOCKED]";

        for (int i = 0;
            text[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = text[i];
        }
    }
    else
    {
        const char text[] =
            "[ DOOR ]";

        for (int i = 0;
            text[i] != '\0';
            i++)
        {
            roomLayout[startY]
                [startX + i]
                = text[i];
        }
    }
}

// =====================================
// OTHER FURNITURE
// =====================================

void Room::drawFurniture()
{
    // =====================================
    // ROOM 1
    // =====================================

    if (roomNumber == 1)
    {
        const char cabinet[] =
            "[CABINET]";

        const char chair[] =
            "[CHAIR]";

        for (int i = 0;
            cabinet[i] != '\0';
            i++)
        {
            roomLayout[14][6 + i] =
                cabinet[i];
        }

        for (int i = 0;
            chair[i] != '\0';
            i++)
        {
            roomLayout[14][35 + i] =
                chair[i];
        }
    }

    // =====================================
    // ROOM 2
    // =====================================

    else if (roomNumber == 2)
    {
        const char bookshelf[] =
            "[BOOKSHELF]";

        const char brokenLamp[] =
            "[BROKEN LAMP]";

        for (int i = 0;
            bookshelf[i] != '\0';
            i++)
        {
            roomLayout[15][5 + i] =
                bookshelf[i];
        }

        for (int i = 0;
            brokenLamp[i] != '\0';
            i++)
        {
            roomLayout[15][34 + i] =
                brokenLamp[i];
        }
    }

    // =====================================
    // ROOM 3
    // =====================================

    else if (roomNumber == 3)
    {
        const char portrait[] =
            "[PORTRAIT]";

        const char crate[] =
            "[CRATE]";

        for (int i = 0;
            portrait[i] != '\0';
            i++)
        {
            roomLayout[15][5 + i] =
                portrait[i];
        }

        for (int i = 0;
            crate[i] != '\0';
            i++)
        {
            roomLayout[15][37 + i] =
                crate[i];
        }
    }

    else if (roomNumber == 5)
    {
        const char cabinet[] =
            "[CABINET]";

        for (int i = 0;
            cabinet[i] != '\0';
            i++)
        {
            roomLayout[14][6 + i] =
                cabinet[i];
        }
    }
}

// =====================================
// BUILD ROOM
// =====================================

void Room::createRoom()
{
    clearRoom();

    drawWalls();
    drawPuzzle();
    drawDoor();
    drawTable();
    drawFurniture();
}

// =====================================
// DISPLAY ROOM
// =====================================

void Room::drawRoom(
    int playerX,
    int playerY,
    bool playerSeated)
{
    std::cout << std::endl;

    std::cout
        << "================ ROOM "
        << roomNumber
        << " ================"
        << std::endl;

    std::cout << std::endl;

    for (int y = 0;
        y < HEIGHT;
        y++)
    {
        for (int x = 0;
            x < WIDTH;
            x++)
        {
            if (x == playerX &&
                y == playerY &&
                playerSeated == false)
            {
                std::cout << 'P';
            }
            else
            {
                std::cout
                    << roomLayout[y][x];
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout
        << "WASD - Move"
        << std::endl;

    std::cout
        << "E    - Interact"
        << std::endl;

    std::cout << std::endl;
}

// =====================================
// COLLISION
// =====================================

bool Room::isWalkable(
    int x,
    int y)
{
    if (x < 0 ||
        x >= WIDTH ||
        y < 0 ||
        y >= HEIGHT)
    {
        return false;
    }

    // All Interactables block movement.
    for (int i = 0;
        i < interactableCount;
        i++)
    {
        if (interactables[i]
            != nullptr)
        {
            if (interactables[i]->
                containsPosition(
                    x,
                    y))
            {
                return false;
            }
        }
    }

    // Empty spaces are walkable.
    if (roomLayout[y][x] == ' ')
    {
        return true;
    }

    return false;
}

// =====================================
// INTERACTION DETECTION
// =====================================

Interactable* Room::getInteractableAt(
    int x,
    int y)
{
    for (int i = 0;
        i < interactableCount;
        i++)
    {
        if (interactables[i]
            != nullptr)
        {
            if (interactables[i]->
                containsPosition(
                    x,
                    y))
            {
                return interactables[i];
            }
        }
    }

    return nullptr;
}

// =====================================
// GETTERS / SETTERS
// =====================================

int Room::getRoomNumber()
{
    return roomNumber;
}

Puzzle* Room::getPuzzle()
{
    return puzzle;
}

bool Room::getPuzzleUnlocked()
{
    if (puzzle != nullptr)
    {
        return puzzle->getUnlocked();
    }

    return false;
}

void Room::setPuzzleUnlocked(
    bool unlocked)
{
    if (puzzle != nullptr)
    {
        puzzle->setUnlocked(
            unlocked);

        createRoom();
    }
}

Door* Room::getDoor()
{
    return exitDoor;
}

bool Room::getDoorUnlocked()
{
    if (exitDoor != nullptr)
    {
        return exitDoor->getUnlocked();
    }

    return false;
}

void Room::setDoorUnlocked(
    bool unlocked)
{
    if (exitDoor != nullptr)
    {
        exitDoor->setUnlocked(
            unlocked);

        createRoom();
    }
}
