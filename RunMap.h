#pragma once

#include "MapNode.h"
#include "MapRNG.h"

// Stores which path the player
// is currently selecting.
enum PathChoice
{
    NO_PATH,
    LEFT_PATH,
    RIGHT_PATH
};

class Map
{
private:
    MapNode* nodes[7];

    int nodeCount;

    // Node the player is currently standing on.
    MapNode* currentNode;

    // Path currently highlighted by A/D.
    PathChoice selectedPath;

    // Generates random node types.
    MapRNG mapRNG;

public:
    Map();

    ~Map();

    // Creates the randomized map.
    void generateMap();

    // Draws the map.
    void drawMap();

    // Selects a path without travelling yet.
    void selectLeft();
    void selectRight();

    // Travels along the currently selected path.
    //
    // Returns true if movement happened.
    bool travelSelected();

    // Returns the node currently selected.
    MapNode* getSelectedNode();

    // Returns the node the player
    // is currently standing on.
    MapNode* getCurrentNode();

    // Returns selected path.
    PathChoice getSelectedPath();

    // Checks whether player reached
    // the final node.
    bool isAtFinalNode();
};