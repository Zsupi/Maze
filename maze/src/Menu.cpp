#include "include/Menu.h"

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


Menu::Menu(const unsigned int x, const unsigned int y, sf::RenderWindow &window, sf::Font &font, float hossz)
:window(window), font(font), game(window, font, hossz)
{
    selectedIdx = 0;

    title.setFont(font);
    title.setString("labyrinth");
    title.setCharacterSize(300);
    title.setFillColor(sf::Color::White);
    title.setPosition(x/2, y/2-150);
    text[3] = title;

    for(int i = 0; i < 3; i++){
       text[i].setFont(font);
       text[i].setPosition(x/10, y/2 + 200*(i-1));
       text[i].setString(str[i]);
       text[i].setFillColor(sf::Color::White);
       text[i].setCharacterSize(80);
    }
    text[0].setFillColor(sf::Color::Green);

    backgroundTexture.loadFromFile("texture/Background.png");

    sf::Sprite n(backgroundTexture);
    n.scale(window.getSize().x/backgroundTexture.getSize().x, window.getSize().y/backgroundTexture.getSize().y);
    background = n;


}

void Menu::MoveUp()
{
    text[selectedIdx].setFillColor(sf::Color::White);
    if(selectedIdx == 0){
        selectedIdx = 2;
    }
    else
        selectedIdx--;

    text[selectedIdx].setFillColor(sf::Color::Green);
}

void Menu::MoveDown()
{
    text[selectedIdx].setFillColor(sf::Color::White);
    selectedIdx++;
    selectedIdx%=3;

    text[selectedIdx].setFillColor(sf::Color::Green);
}

void Menu::select()
{
    switch(selectedIdx){
        case 0:
            game.NewGame();
            game.GameState();
            break;
        case 1:
            dicsoseglista(font, window);
            break;
        case 2:
            window.close();
            break;
    }
}

void Menu::rajzol(sf::RenderWindow &window)
{
    window.draw(background);

    for(size_t i = 0; i<4; i++){
        int kul = 8;

        if(i == 3)
            kul = 16;

        sf::Text kekFelirat;
        sf::Text pirosFelirat;

        kekFelirat = text[i];
        kekFelirat.setPosition(text[i].getPosition().x-text[i].getCharacterSize()/kul, text[i].getPosition().y);
        kekFelirat.setFillColor(sf::Color(0, 0, 255, 125));

        pirosFelirat = text[i];
        pirosFelirat.setPosition(text[i].getPosition().x+text[i].getCharacterSize()/kul, text[i].getPosition().y);
        pirosFelirat.setFillColor(sf::Color(255, 0, 0, 125));

        window.draw(pirosFelirat);
        window.draw(kekFelirat);
        window.draw(text[i]);

    }

}
