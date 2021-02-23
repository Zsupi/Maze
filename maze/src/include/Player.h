
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Palya.h"




class Palya;
class Player: public Pont<float>
{
    private:


        sf::RectangleShape shape;
        sf::Texture texture;
        float speed = 16.0f;

        int score = 0;

        float rad;
        char* nev;
        float hossz;
    public:

        Player();

        Player(float x, float y, const char* n, float h = 80);

        Player(const Blokk kezdo, const char* n, float h = 80);

        Player(const int s, const char* n);

        Player(const Player &p);

        ~Player();

        void mozgas(const float x1, const float y1, const Palya& palya);

        bool collision(const Blokk fal);

        void rajz(sf::RenderWindow &window);

        float getspeed()const;

        Pont<float> getCenter() const;

        int gethossz()const;

        int getScore()const;

        float getRad()const;

        char* getNev()const;

        void setNev(const char* n);

        void setScore(const int s);

        void setRad(const float r);

        Player& operator=(const Player& p);
};


#endif // PLAYER_H_INCLUDED
