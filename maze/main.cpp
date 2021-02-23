#include "src/include/Palya.h"
#include "src/include/Menu.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <ctime>
#include <cstdlib>


//#define DARK
using namespace std;

void init(sf::RenderWindow& window, sf::Font& font)
{

    window.create(sf::VideoMode(2000, 2000), "Maze", sf::Style::Close | sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    if(!font.loadFromFile("font/blrrpix.strict.ttf")){
        std::cout<< "A font nem nyithato meg"<<std::endl;
        system("pause");
    }


}

///----------------------------------------------------------------------
///DARK makro definialasaval, a Player.cpp-ben, a sotetseg kikapcsolhato
///----------------------------------------------------------------------

int main()
{
    srand(time(0));

    sf::RenderWindow window;
    sf::Font font;

    init(window, font);
    float hossz = (window.getSize().x + window.getSize().y)/50;
    Menu menu(window.getSize().x, window.getSize().y, window, font, hossz);

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code){
                        case sf::Keyboard::W:
                            menu.MoveUp();
                            break;
                        case sf::Keyboard::S:
                            menu.MoveDown();
                            break;
                        case sf::Keyboard::Return:
                            menu.select();
                            break;
                        default:
                            break;
                    }
                default:
                    break;

            }
        }

        window.clear();

        menu.rajzol(window);

        window.display();

    }

    return 0;
}

///1417
