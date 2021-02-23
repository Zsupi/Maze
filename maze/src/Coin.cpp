#include "include/Coin.h"
#include "include/Item.h"
#include <iostream>
#include <SFML/Graphics.hpp>



Coin::Coin(float x, float y): Item(x, y)
{
    texture.loadFromFile("texture/Coin.png");

    body.setPosition(x, y);
    body.setSize(sf::Vector2f(hossz, hossz));
    body.setTexture(&texture);
}

void Coin::hatas(Player& player)
{
    if (available == true){
        player.setScore(player.getScore()+25);
    }

    available = false;
    texture.loadFromFile("texture/Blank.png");
    body.setTexture(&texture);

}

void Coin::rajzol(sf::RenderWindow& window)
{
    window.draw(body);
}

void Coin::pickedupby(Player& player)
{
    float deltax = player.getCenter().getx() - getCenter().getx();
    float deltay = player.getCenter().gety() - getCenter().gety();

    float metszesx = abs(deltax) - (player.gethossz()/2 + hossz/2);
    float metszesy = abs(deltay) - (player.gethossz()/2 + hossz/2);

    if(metszesx < 0.0f && metszesy < 0.0f){
        hatas(player);
    }
}
