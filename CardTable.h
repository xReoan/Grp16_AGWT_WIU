#pragma once

#include "Interactable.h"

// CardTable is a type of Interactable.
//
// Interacting with the CardTable
// opens the branching Run Map.
class CardTable : public Interactable
{
public:
    // Constructor.
    CardTable(int startX, int startY,
        int tableWidth, int tableHeight);

    // Destructor.
    ~CardTable() override;

    // Overrides Interactable::interact().
    //
    // Returns OPEN_MAP because interacting
    // with the table allows the player to sit down
    // and view the branching map.
    InteractionResult interact() override;
};