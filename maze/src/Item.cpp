#include "include/Item.h"

Item::Item(float x, float y):Pont(x, y), available(true)
{
}

int Item::gethossz()const
{
    return hossz;
}

bool Item::getstatus()const
{
    return available;
}

Pont<float> Item::getCenter()const
{
    return Pont<float>(x+hossz/2, y+hossz/2);
}


