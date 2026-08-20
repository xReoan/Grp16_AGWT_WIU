#include "MapRNG.h"
#include <cstdlib>

// Generates a random node type.
//
// rand() % 100 gives a value from 0 to 99.
//
// 0  - 59 = Fight
// 60 - 79 = Shop
// 80 - 99 = Backpack
NodeType MapRNG::generateNodeType()
{
    int randomNumber = rand() % 100;

    if (randomNumber < 60)
    {
        return FIGHT;
    }
    else if (randomNumber < 80)
    {
        return SHOP;
    }
    else
    {
        return BACKPACK;
    }
}