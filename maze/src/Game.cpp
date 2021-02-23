#include "include/Game.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstring>
#include <codecvt>

#define maxNev 25
#define DELETE_KEY 8

Game::Game(sf::RenderWindow &window, sf::Font &font, float h)
    :window(window), font(font), hossz(h){}

void Game::GameState()
{

    bool jatek = true;
    while(jatek && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))){
        sf::Event ev;
        while(window.pollEvent(ev)){
            switch(ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    switch(ev.key.code){
                        case sf::Keyboard::Escape:
                            jatek = false;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        Move();
        Draw();
        window.display();
        jatek = Gameover();

    }

    UpdateScore();
}

void Game::Move()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        player.mozgas(-player.getspeed(), 0.0f, palya);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        player.mozgas(player.getspeed(), 0.0f, palya);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        player.mozgas(0.0f, player.getspeed(), palya);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        player.mozgas(0.0f, -player.getspeed(), palya);
}

void Game::Draw()
{
    window.clear(sf::Color::Black);
    palya.rajz(window);
    player.rajz(window);

    char str[15+1] = "Score:";
    scoreConverter(player.getScore(), str);

    Pont<float> p2(300, 25);
    felirat(font, window, p2 , 100, sf::String(str));
}

bool Game::Gameover()
{
    if(palya.getkiut().getx() <= player.getx() && palya.getkiut().gety() <= player.gety()){
        while(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))){
            sf::Texture backgroundTexture;
            backgroundTexture.loadFromFile("texture/Background.png");

            sf::Sprite n(backgroundTexture);
            n.scale(window.getSize().x/backgroundTexture.getSize().x, window.getSize().y/backgroundTexture.getSize().y);
            window.draw(n);
            Pont<float> p(window.getSize().x/2, window.getSize().y/2);
            Pont<float> p2(window.getSize().x/2, window.getSize().y/2-300);

            char str[15+1] = "Score:";
            scoreConverter(player.getScore(), str);

            felirat(font, window, p, 400, "win");
            felirat(font, window, p2 , 100, sf::String(str));
            window.display();
        }
        return false;
    }
    return true;
}

void Game::UpdateScore()
{
    std::ifstream in("save/Scoreboard.txt");
    if(!in.is_open())
        std::cout<<"ERROR: Can't open 'in'"<<std::endl;

    char nevTxt[maxNev+5];
    nevTxt[0] = '\0';
    int scoreTxt = 0;

    bool valid = true;
    Player* p = new Player[10];

    int i = 0;
    while((in >> nevTxt >> scoreTxt)&&(i<10)){
        Player uj(scoreTxt, nevTxt);

        if(scoreTxt < player.getScore()&& valid){
            valid = false;
            p[i] = player;
            i++;
            p[i] = uj;
        }
        else{
            p[i] = uj;
        }
        i++;
    }
    in.close();

    std::ofstream out("save/Scoreboard.txt");
    if(!out.is_open())
        std::cout<<"ERROR: Can't open 'out'"<<std::endl;

    for(int i = 0; i<10; i++){
        out<<p[i].getNev()<<" "<<p[i].getScore()<<std::endl;

    }
    for(int i = 0; i<10; i++){
        std::cout<<p[i].getNev()<<" "<<p[i].getScore()<<std::endl;
    }
    out.close();

    delete[] p;
}

void Game::Name()
{
    bool enter = false;
    Pont<float>kozeppont(window.getSize().x/2, window.getSize().y/2);

    char nev[maxNev];
    nev[0] = '\0';
    size_t idx = 0;


    while(!enter){
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::TextEntered:
                    if((event.text.unicode >= 'a' && event.text.unicode<= 'z')
                       ||(event.text.unicode >= 'A' && event.text.unicode<= 'Z')){
                        if (idx < maxNev){
                            nev[idx] = static_cast<char32_t>(event.text.unicode);
                            idx++;
                            nev[idx] = '\0';

                        }
                    }
                    if (strlen(nev) > 0 && event.text.unicode == DELETE_KEY){
                            idx--;
                            nev[idx] = '\0';
                        }
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::Return:
                            enter = true;
                            break;
                        default:
                            break;
                    }
                break;
                default:
                    break;
            }
        }
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("texture/Background.png");

        sf::Sprite n(backgroundTexture);
        n.scale(window.getSize().x/backgroundTexture.getSize().x, window.getSize().y/backgroundTexture.getSize().y);
        window.draw(n);

        felirat(font, window, kozeppont, 80, sf::String(nev));
        Pont<float> felirat2KP(kozeppont.getx(), kozeppont.gety()-200);
        felirat(font, window, felirat2KP, 120, "Your Name:");

        window.display();

    }
    player.setNev(nev);
    return;
}

void Game::NewGame( Pont<int> kezdo)
{
    Palya ujpalya((window.getSize().x - 21*80)/2, (window.getSize().y - 21*80)/2);
    palya = ujpalya;

    palya.kepez(kezdo);
    palya.setkiut();
    palya.item_kepez();

    Player ujplayer(palya.palya[1][1], "", hossz/2);
    player = ujplayer;
    Name();
}


///---------------///


void dicsoseglista(sf::Font &font, sf::RenderWindow &window)
{

    std::ifstream file("save/Scoreboard.txt");
    if(!file.is_open())
        std::cout<<"ERROR: Cannot be open"<<std::endl;

    window.clear();
    char nev [maxNev];
    nev[0] = '\0';
    int i = 0;

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("texture/Background.png");

    sf::Sprite n(backgroundTexture);
    n.scale(window.getSize().x/backgroundTexture.getSize().x, window.getSize().y/backgroundTexture.getSize().y);
    window.draw(n);

    while(file.good() && i<10){


        file.getline(nev, maxNev+5);
        Pont<float> p(window.getSize().x/2, 300+i*160);
        felirat(font, window, p, 80, nev);

        i++;
    }
    file.close();
    window.display();

    bool open = true;
    while(open){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            open = false;
        }
    }
}

void scoreConverter(int score, char* str)
{
    char tmp[15+1];
    sprintf(tmp, "\t%d", score);
    strcat(str, tmp);
}

void felirat(sf::Font &font, sf::RenderWindow &window, Pont<float> kozeppont, int meret, sf::String szoveg){

    sf::Text Felirat;

    Felirat.setFont(font);
    Felirat.setString(szoveg);
    Felirat.setCharacterSize(meret);
    Felirat.setFillColor(sf::Color::White);
    Felirat.getScale();
    Felirat.setPosition(kozeppont.getx()-Felirat.getGlobalBounds().width/2, kozeppont.gety()-Felirat.getGlobalBounds().height/2);

    sf::Text kekFelirat;
    sf::Text pirosFelirat;

    kekFelirat = Felirat;
    kekFelirat.setPosition(Felirat.getPosition().x-10, Felirat.getPosition().y);
    kekFelirat.setFillColor(sf::Color(0, 0, 255, 125));

    pirosFelirat = Felirat;
    pirosFelirat.setPosition(Felirat.getPosition().x+10, Felirat.getPosition().y);
    pirosFelirat.setFillColor(sf::Color(255, 0, 0, 125));


    window.draw(pirosFelirat);
    window.draw(kekFelirat);
    window.draw(Felirat);
}
