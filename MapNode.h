#pragma once

enum NodeType
{
    FIGHT,
    SHOP,
    BACKPACK
};

class MapNode
{
private:
    // Type of encounter at this node.
    NodeType type;

    // Position used when drawing the node on screen.
    int x;
    int y;

    // Possible paths leading from this node.
    MapNode* leftPath;
    MapNode* rightPath;

    // Tracks whether the player already visited this node.
    bool visited;

public:
    MapNode(NodeType nodeType, int startX, int startY);

    NodeType getType();

    int getX();
    int getY();

    MapNode* getLeftPath();
    MapNode* getRightPath();

    bool getVisited();

    void setLeftPath(MapNode* node);
    void setRightPath(MapNode* node);

    void setVisited(bool value);

    char getSymbol();
};