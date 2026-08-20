#include "CardTable.h"

// Passes the table's position and size
// to the Interactable parent constructor.
CardTable::CardTable(
    int startX,
    int startY,
    int tableWidth,
    int tableHeight)
    : Interactable(
        startX,
        startY,
        tableWidth,
        tableHeight)
{
}

// Destructor.
CardTable::~CardTable()
{
}

// CardTable's version of interact().
//
// This is FUNCTION OVERRIDING.
InteractionResult CardTable::interact()
{
    return OPEN_MAP;
}