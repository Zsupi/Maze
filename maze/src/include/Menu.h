#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


#include "Game.h"
#include <SFML/Graphics.hpp>

class Menu
{
    public:
        Menu(const unsigned int x, const unsigned int y, sf::RenderWindow &w, sf::Font &font, float hossz = 80.0f);

        void rajzol(sf::RenderWindow& window);
        void MoveUp();
        void MoveDown();
        void select();


    private:
        int selectedIdx;
        sf::RenderWindow &window;
        sf::Font &font;
        sf::Text text[4];
        sf::Text title;
        sf::String str[3] = {"Play", "Scoreboard", "Exit"};
        sf::Sprite background;
        sf::Texture backgroundTexture;
        Game game;
};
#endif // MENU_H_INCLUDED
