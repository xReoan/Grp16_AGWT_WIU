#include "Card.h"

Card::Card()
    : type(cardtype::attack),
      cardeffect(effecttype::damage),
      multiplier(1.0f),
      value(0)
{
}

string Card::getitemname()
{
    return name;
}

string Card::getdescription()
{
    return description;
}

int Card::getvalue()
{
    return value;
}
