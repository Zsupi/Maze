#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstring>

#include "include/Player.h"

#define DARK

Player::Player():Pont(0, 0), rad(200.0f)
{
    nev = new char[1];
    nev[0] = '\0';
}

Player::Player(float x, float y, const char* n, float h):Pont(x, y), rad(h*5), hossz(h)
{
    nev = new char[strlen(n)+1];
    strcpy(nev, n);


    texture.loadFromFile("texture/Tod.png");
    shape.setSize(sf::Vector2f(hossz+8 , hossz+8));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setTexture(&texture);
}

Player::Player(const Blokk kezdo, const char* n, float h):Pont(kezdo.getx(), kezdo.gety()), rad(h*5), hossz(h)
{
    nev = new char[strlen(n)+1];
    strcpy(nev, n);

    texture.loadFromFile("texture/Tod.png");
    shape.setSize(sf::Vector2f(hossz+8, hossz+8));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setTexture(&texture);
}

Player::Player(const int s, const char* n):Pont(0, 0), score(s), rad(200.0f)
{
    nev = new char[strlen(n)+1];
    strcpy(nev, n);
}

Player::Player(const Player& p)
{
    shape = p.shape;
    texture = p.texture;
    score = p.score;
    rad = p.rad;
    hossz = p.hossz;

    nev = new char[strlen(p.nev)+1];
    strcpy(nev, p.nev);

    x = p.x;
    y = p.y;
}

Player::~Player()
{
    delete[] nev;
}

void Player::mozgas(const float x1, const float y1, const Palya& palya)
{

    //minden mozgasnal csereljuk a centert csereljuk a pontokat
    //es itt is allitjuk be
    x += x1;
    y += y1;

    //eleg csak a jatekost korul vevo 3*3 as reszhalmazt vizsgalni és ennek
    int idx_x = std::min(static_cast<int>(ceil((x-palya.palya[0][0].getx())/(2*hossz))), palya.getwin().getx()-1);
    int idx_y = std::min(static_cast<int>(ceil((y-palya.palya[0][0].gety())/(2*hossz))), palya.getwin().getx()-1);

    for(int i = idx_x-1; i<idx_x+1; i++){
        for(int j = idx_y-1; j<idx_y+1; j++){
            if(collision(palya.palya[i][j])){
                x -= x1;
                y -= y1;
                return;
            }
        }
    }
    shape.move(x1, y1);

    for(int i = 0; i<maxTargy; i++){
        palya.targyak[i]->pickedupby(*this);
    }
}

void Player::rajz(sf::RenderWindow &window)
{
    #ifndef DARK
    float r = rad;
    float window_size = 21;

    sf::CircleShape circle(getCenter().getx(), getCenter().gety());

    circle.setRadius(r);
    circle.setPosition(getCenter().getx()-r, getCenter().gety()-r);
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    circle.setOutlineThickness(window_size);

    for(int i = 0; i< 10; i++){
        r -= 4*i;
        circle.setRadius(r);
        circle.setPosition(getCenter().getx()-r, getCenter().gety()-r);
        circle.setOutlineColor(sf::Color(0, 0, 0, 255-25*i));
        window.draw(circle);
    }
    #endif // DARK
    window.draw(shape);
}

bool Player::collision(const Blokk fal)
{

    float deltax = fal.getCenter().getx() - getCenter().getx();
    float deltay = fal.getCenter().gety() - getCenter().gety();

    float metszesx = abs(deltax) - (fal.gethossz()/2 + hossz/2);
    float metszesy = abs(deltay) - (fal.gethossz()/2 + hossz/2);

    if(metszesx < 0.0f && metszesy < 0.0f && !fal.getut()){
        return true;

    }
    else
        return false;
}

float Player::getspeed()const
{
    return speed;
}

int Player::gethossz()const
{
    return hossz;
}

Pont<float> Player::getCenter() const
{
    return Pont<float>(x + hossz/2, y + hossz/2);
}

int Player::getScore()const
{
    return score;
}

float Player::getRad()const
{
    return rad;
}

char* Player::getNev()const
{
    return nev;
}

void Player::setNev(const char* n)
{
    delete[] nev;
    nev = new char [strlen(n)+1];
    strcpy(nev, n);
}

void Player::setScore(const int s)
{
    score = s;
}

void Player::setRad(const float r)
{
    rad = r;
}

Player& Player::operator=(const Player &p)
{
    if(this != &p){
        shape = p.shape;
        texture = p.texture;
        score = p.score;
        rad = p.rad;
        shape.setTexture(&texture);
        hossz = p.hossz;

        delete[] nev;
        nev = new char[strlen(p.nev)+1];
        strcpy(nev, p.nev);
        x = p.x;
        y = p.y;
    }
    return *this;
}
