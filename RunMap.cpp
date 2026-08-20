#include "RunMap.h"

#include <iostream>

Map::Map()
{
    nodeCount = 0;

    currentNode = nullptr;

    selectedPath = NO_PATH;

    for (int i = 0; i < 7; i++)
    {
        nodes[i] = nullptr;
    }
}

// Deletes all map nodes.
Map::~Map()
{
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i] != nullptr)
        {
            delete nodes[i];

            nodes[i] = nullptr;
        }
    }

    currentNode = nullptr;
}

// Generates Room 1's progression map.
void Map::generateMap()
{
    // A new room generates a fresh map. Delete the previous room's
    // nodes before replacing their pointers.
    for (int i = 0; i < nodeCount; i++)
    {
        delete nodes[i];
        nodes[i] = nullptr;
    }

    nodeCount = 0;
    currentNode = nullptr;
    selectedPath = NO_PATH;

    // Starting node.
    nodes[0] =
        new MapNode(
            FIGHT,
            400,
            500);

    // Second row.
    nodes[1] =
        new MapNode(
            mapRNG.generateNodeType(),
            300,
            400);

    nodes[2] =
        new MapNode(
            mapRNG.generateNodeType(),
            500,
            400);

    // Middle node.
    nodes[3] =
        new MapNode(
            mapRNG.generateNodeType(),
            400,
            300);

    // Fourth row.
    nodes[4] =
        new MapNode(
            mapRNG.generateNodeType(),
            300,
            200);

    nodes[5] =
        new MapNode(
            mapRNG.generateNodeType(),
            500,
            200);

    // Final node is always Fight.
    //
    // Later this will become the Boss.
    nodes[6] =
        new MapNode(
            FIGHT,
            400,
            100);

    nodeCount = 7;

    // --------------------------
    // CONNECT PATHS
    // --------------------------

    // Start splits.
    nodes[0]->setLeftPath(nodes[1]);
    nodes[0]->setRightPath(nodes[2]);

    // Merge.
    nodes[1]->setRightPath(nodes[3]);
    nodes[2]->setLeftPath(nodes[3]);

    // Split again.
    nodes[3]->setLeftPath(nodes[4]);
    nodes[3]->setRightPath(nodes[5]);

    // Merge at final node.
    nodes[4]->setRightPath(nodes[6]);
    nodes[5]->setLeftPath(nodes[6]);

    // Start player at first node.
    currentNode = nodes[0];

    currentNode->setVisited(true);

    selectedPath = NO_PATH;
}

// Draws the map.
void Map::drawMap()
{
    std::cout
        << "================ MAP ================"
        << std::endl;

    std::cout << std::endl;

    std::cout
        << "                   ["
        << nodes[6]->getSymbol()
        << "]"
        << std::endl;

    std::cout
        << "                  /   \\"
        << std::endl;

    std::cout
        << "                ["
        << nodes[4]->getSymbol()
        << "]   ["
        << nodes[5]->getSymbol()
        << "]"
        << std::endl;

    std::cout
        << "                  \\   /"
        << std::endl;

    std::cout
        << "                   ["
        << nodes[3]->getSymbol()
        << "]"
        << std::endl;

    std::cout
        << "                  /   \\"
        << std::endl;

    std::cout
        << "                ["
        << nodes[1]->getSymbol()
        << "]   ["
        << nodes[2]->getSymbol()
        << "]"
        << std::endl;

    std::cout
        << "                  \\   /"
        << std::endl;

    std::cout
        << "                 [START]"
        << std::endl;

    std::cout << std::endl;

    std::cout << "Legend:" << std::endl;

    std::cout
        << "F = Fight"
        << std::endl;

    std::cout
        << "S = Shop"
        << std::endl;

    std::cout
        << "B = Backpack"
        << std::endl;

    std::cout << std::endl;

    // --------------------------
    // CURRENT NODE
    // --------------------------

    if (currentNode != nullptr)
    {
        std::cout
            << "Current Node: ["
            << currentNode->getSymbol()
            << "]"
            << std::endl;
    }

    std::cout << std::endl;

    // --------------------------
    // LEFT OPTION
    // --------------------------

    if (currentNode != nullptr &&
        currentNode->getLeftPath() != nullptr)
    {
        if (selectedPath == LEFT_PATH)
        {
            std::cout
                << "Left:  >["
                << currentNode->
                getLeftPath()->
                getSymbol()
                << "]"
                << std::endl;
        }
        else
        {
            std::cout
                << "Left:   ["
                << currentNode->
                getLeftPath()->
                getSymbol()
                << "]"
                << std::endl;
        }
    }
    else
    {
        std::cout
            << "Left:   No Path"
            << std::endl;
    }

    // --------------------------
    // RIGHT OPTION
    // --------------------------

    if (currentNode != nullptr &&
        currentNode->getRightPath() != nullptr)
    {
        if (selectedPath == RIGHT_PATH)
        {
            std::cout
                << "Right: >["
                << currentNode->
                getRightPath()->
                getSymbol()
                << "]"
                << std::endl;
        }
        else
        {
            std::cout
                << "Right:  ["
                << currentNode->
                getRightPath()->
                getSymbol()
                << "]"
                << std::endl;
        }
    }
    else
    {
        std::cout
            << "Right:  No Path"
            << std::endl;
    }
}

// Selects left path.
void Map::selectLeft()
{
    if (currentNode != nullptr &&
        currentNode->getLeftPath() != nullptr)
    {
        selectedPath = LEFT_PATH;
    }
}

// Selects right path.
void Map::selectRight()
{
    if (currentNode != nullptr &&
        currentNode->getRightPath() != nullptr)
    {
        selectedPath = RIGHT_PATH;
    }
}

// Returns whichever node is selected.
MapNode* Map::getSelectedNode()
{
    if (currentNode == nullptr)
    {
        return nullptr;
    }

    if (selectedPath == LEFT_PATH)
    {
        return currentNode->getLeftPath();
    }

    else if (selectedPath == RIGHT_PATH)
    {
        return currentNode->getRightPath();
    }

    return nullptr;
}

// Confirms selected path.
bool Map::travelSelected()
{
    MapNode* destination =
        getSelectedNode();

    // No valid path selected.
    if (destination == nullptr)
    {
        return false;
    }

    // Move to selected node.
    currentNode = destination;

    currentNode->setVisited(true);

    // Clear selection after travelling.
    selectedPath = NO_PATH;

    return true;
}

MapNode* Map::getCurrentNode()
{
    return currentNode;
}

PathChoice Map::getSelectedPath()
{
    return selectedPath;
}

// Final node is nodes[6].
bool Map::isAtFinalNode()
{
    if (currentNode == nodes[6])
    {
        return true;
    }

    return false;
}
