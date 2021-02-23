

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Player.h"
#include "Palya.h"
#include "Kepzes.h"
#include <SFML/Graphics.hpp>

class Game{
    private:
        sf::RenderWindow& window;
        sf::Font &font;
        Palya palya;
        Player player;

        float hossz;
    public:
        Game(sf::RenderWindow& window, sf::Font &font, float h = 80.0f);

        void GameState();

        void Move();

        void Draw();

        bool Gameover();

        void UpdateScore();

        void Name();

        void NewGame(Pont<int> kezdo = Pont<int>(1, 1));

};

void dicsoseglista(sf::Font &font, sf::RenderWindow &window);

void scoreConverter(int score, char* str);

void felirat(sf::Font &font, sf::RenderWindow &window, Pont<float> kozeppont, int meret, sf::String szoveg);

#endif // GAME_H_INCLUDED
