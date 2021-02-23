#ifndef BLOKK_H
#define BLOKK_H

#include "Pont.h"

#include <iostream>
#include<SFML/Graphics.hpp>

class Blokk: public Pont<float>
{
    public:
        Blokk();

        Blokk(const Blokk& b);

        void setut(bool u);

        bool getut()const;

        Pont<float> getCenter() const
        {
            return Pont<float>(x + hossz/2, y + hossz/2);
        }

        sf::RectangleShape getbody()const;

        void rajz(sf::RenderWindow& window, sf::Texture &blokkTexture);
        Blokk& operator=(const Blokk& b);

        float gethossz()const;

        void sethossz(float h);

    private:
        bool ut;
        sf::RectangleShape body;
        float hossz;

};

#endif // BLOKK_H
