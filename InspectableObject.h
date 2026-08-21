#pragma once

#include "Interactable.h"

#include <string>

class InspectableObject : public Interactable
{
private:
    std::string objectName;
    std::string dialogue;

public:
    InspectableObject(
        int startX,
        int startY,
        int objectWidth,
        int objectHeight,
        const std::string& name,
        const std::string& objectDialogue);

    ~InspectableObject() override;

    std::string getName() const;
    std::string getDialogue() const;

    InteractionResult interact() override;
};