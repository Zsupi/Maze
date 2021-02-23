#include "include/Torch.h"
#include "include/Item.h"
#include <iostream>
#include <SFML/Graphics.hpp>



Torch::Torch(float x, float y): Item(x, y)
{
    texture.loadFromFile("texture/Torch.png");

    body.setPosition(x, y);
    body.setSize(sf::Vector2f(hossz, hossz));
    body.setTexture(&texture);
    //body.setFillColor(sf::Color::Blue);
}

void Torch::hatas(Player& player)
{
    if (available == true){
        player.setRad(player.getRad()+25.0f);
    }

    available = false;
    texture.loadFromFile("texture/Blank.png");
    body.setTexture(&texture);

}

void Torch::rajzol(sf::RenderWindow& window)
{
    window.draw(body);
}

void Torch::pickedupby(Player& player)
{
    float deltax = player.getCenter().getx() - getCenter().getx();
    float deltay = player.getCenter().gety() - getCenter().gety();

    float metszesx = abs(deltax) - (player.gethossz()/2 + hossz/2);
    float metszesy = abs(deltay) - (player.gethossz()/2 + hossz/2);

    if(metszesx < 0.0f && metszesy < 0.0f){
        hatas(player);
    }
}
