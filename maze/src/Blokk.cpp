#include "include/Blokk.h"

#include<SFML/Graphics.hpp>
#include <iostream>

//konst
Blokk::Blokk():ut(false)
{
    #ifndef CPORTA
    sf::RectangleShape uj(sf::Vector2f(x, y));
    #endif // CPORTA
    body = uj;
}

Blokk::Blokk(const Blokk& b)
{
    x = b.getx();
    y = b.gety();
    ut = b.getut();
    hossz = b.hossz;
    #ifndef CPORTA
    body = b.getbody();
    #endif // CPORTA

}

//get-set
void Blokk::setut(bool u)
{
    ut = u;
}

bool Blokk::getut()const
{
    return ut;
}

sf::RectangleShape Blokk::getbody()const
{
    return body;
}

float Blokk::gethossz()const
{
    return hossz;
}

void Blokk::sethossz(float h = 80.0f)
{
    hossz = h;
    std::cout<<hossz<<std::endl;
}

//operator
Blokk& Blokk::operator=(const Blokk& b)
{
    if(&b != this){
        ut = b.getut();
        x = b.getx();
        y = b.gety();
        hossz = b.hossz;
        #ifndef CPORTA
        body = b.getbody();
        #endif // CPORTA
    }
    return *this;
}
#ifndef CPORTA
void Blokk::rajz(sf::RenderWindow& window, sf::Texture &blokkTexture)
{
    //minden frame updatenel megadjuk a blokkok kozepet

    this->body.setPosition(sf::Vector2f(x, y));
    this->body.setSize(sf::Vector2f(hossz, hossz));

    if(!ut){
        body.setTexture(&blokkTexture);

    }
    else{
        this->body.setFillColor(sf::Color::Black);
    }
    std::cout<<hossz<<std::endl;
    window.draw(body);

}
#endif
