#include "MapNode.h"

// Creates one map node.
MapNode::MapNode(NodeType nodeType, int startX, int startY)
{
    type = nodeType;

    x = startX;
    y = startY;

    // No paths are connected yet.
    leftPath = nullptr;
    rightPath = nullptr;

    visited = false;
}

// Returns the type of the node.
NodeType MapNode::getType()
{
    return type;
}

// Returns the x-coordinate of the node.
int MapNode::getX()
{
    return x;
}

// Returns the y-coordinate of the node.
int MapNode::getY()
{
    return y;
}

// Returns the node connected to the left path.
MapNode* MapNode::getLeftPath()
{
    return leftPath;
}

// Returns the node connected to the right path.
MapNode* MapNode::getRightPath()
{
    return rightPath;
}

// Returns whether the node has already been visited.
bool MapNode::getVisited()
{
    return visited;
}

// Connects another node to the left path.
void MapNode::setLeftPath(MapNode* node)
{
    leftPath = node;
}

// Connects another node to the right path.
void MapNode::setRightPath(MapNode* node)
{
    rightPath = node;
}

// Changes whether the node has been visited.
void MapNode::setVisited(bool value)
{
    visited = value;
}

// Returns the character used to display the node.
char MapNode::getSymbol()
{
    if (type == FIGHT)
    {
        return 'F';
    }
    else if (type == SHOP)
    {
        return 'S';
    }
    else
    {
        return 'B';
    }
}