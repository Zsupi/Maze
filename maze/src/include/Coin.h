#ifndef COIN_H
#define COIN_H



#include <SFML/Graphics.hpp>
#include "Item.h"

class Coin: public Item
{
    private:
        sf::Texture texture;
        sf::RectangleShape body;

    public:
        Coin(float x, float y);

        virtual void hatas(Player& player);

        virtual void rajzol(sf::RenderWindow& window);

        virtual void pickedupby(Player &player);
};
#endif // COIN_H
