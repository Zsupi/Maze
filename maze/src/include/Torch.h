#ifndef TORCH_H
#define TORCH_H

#include <SFML/Graphics.hpp>
#include "Item.h"


class Torch: public Item
{
    private:
        sf::Texture texture;
        sf::RectangleShape body;

    public:
        Torch(float x, float y);

        virtual void hatas(Player& player);

        virtual void rajzol(sf::RenderWindow& window);

        virtual void pickedupby(Player &player);
};

#endif // TORCH_H
