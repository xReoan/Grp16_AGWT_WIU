#include "InspectableObject.h"

InspectableObject::InspectableObject(
    int startX,
    int startY,
    int objectWidth,
    int objectHeight,
    const std::string& name,
    const std::string& objectDialogue)
    : Interactable(
        startX,
        startY,
        objectWidth,
        objectHeight)
{
    objectName =
        name;

    dialogue =
        objectDialogue;
}

InspectableObject::~InspectableObject()
{
}

std::string InspectableObject::getName() const
{
    return objectName;
}

std::string InspectableObject::getDialogue() const
{
    return dialogue;
}

InteractionResult InspectableObject::interact()
{
    return SHOW_DIALOGUE;
}