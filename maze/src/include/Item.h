
#include "Player.h"

#ifndef ITEM_H
#define ITEM_H

#include "Pont.h"
#include <SFML/Graphics.hpp>

class Player;
class Item: public Pont<float>
{
    protected:
        static const int hossz = 40.0f;
        bool available;


    public:

        Item(float x, float y);

        virtual ~Item(){}

        int gethossz()const;

        bool getstatus()const;

        Pont<float> getCenter()const;

        virtual void hatas(Player& player) = 0;

        virtual void rajzol(sf::RenderWindow& window) = 0;

        virtual void pickedupby(Player &player) = 0;
};

#endif // ITEM_H
