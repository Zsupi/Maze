
#include "include/Palya.h"
#include "include/Kepzes.h"

#include <iostream>

//konst-dest

Palya::Palya(int x1, int y1, float h):window(21, 21), hossz(h)
{
    int x = x1;
    int y = y1;



    palya = new Blokk*[window.getx()];
    for(int i = 0; i<window.getx(); i++){
        palya[i] = new Blokk[window.gety()];
        y = y1;
        for(int j = 0; j<window.gety(); j++){
            palya[i][j].setx(x);
            palya[i][j].sety(y);
            palya[i][j].sethossz(hossz);
            y += hossz;
        }
        x += hossz;
    }

    targyak[0] = nullptr;

}

Palya::Palya(const Palya& p)
{
    palya = p.palya;
    window = p.getwin();
    kiut = p.getkiut();
    hossz = p.hossz;
}

Palya::~Palya()
{
    for(int i = 0; i<window.gety(); i++){
            delete[] palya[i];
        }
        delete[]palya;

    if(targyak[0] != nullptr){
        for(int i = 0; i<maxTargy; i++){
            delete targyak[i];
        }
    }
}

//getset
Pont<int> Palya::getwin()const
{
    return window;
}

void Palya::setwin(const Pont<int> p)
{
    window = p;
}

void Palya::setkiut()
{
    int ix = window.getx()-1;
    int iy = rand() % (window.gety()-1)+1;

    while(palya[ix-1][iy].getut() != true){
        int ix = window.getx()-1;
        int iy = rand() % (window.gety()-1)+1;
        if(palya[ix-1][iy].getut() == true)
            break;
    }

    palya[ix][iy].setut(true);

    Pont<float> p(palya[ix][iy].getx(), palya[ix][iy].gety());
    kiut = p;


}

Pont<float> Palya::getkiut()const
{
    return kiut;
}

//operatorok
Palya& Palya::operator=(const Palya& p)
{
    window = p.getwin();


    palya = new Blokk*[window.getx()];
    for(int i = 0; i<window.getx(); i++){
        palya[i] = new Blokk[window.gety()];
    }


    for(int i = 0; i<window.getx(); i++){
        for(int j = 0; j<window.gety(); j++){
            palya[i][j] = p.palya[i][j];
        }
    }

    return *this;
}

//draw
void Palya::rajz(sf::RenderWindow& w)
{
    sf::Texture blokkTexture;
    blokkTexture.loadFromFile("texture/wall.png");
    for(int i = 0; i<window.getx(); i++){
        for(int j = 0; j<window.gety(); j++){
            palya[i][j].rajz(w, blokkTexture);
        }
    }

    for(int i = 0; i<maxTargy; i++){
        targyak[i]->rajzol(w);
    }
}

//else
void Palya::kepez(Pont<int> kezdo)
{
   Irany irany[4] = {fel, le, bal, jobb};
    for(int i = 3; i>0; --i){
        int r = rand() % (i+1);
        Irany temp = irany[i];
        irany[i] = irany[r];
        irany[r] = temp;
    }
    if(kezdo.getx() == 0 || kezdo.getx() == window.getx()-1 || kezdo.gety() == 0 || kezdo.gety() == window.gety()-1)
        return;


    palya[kezdo.getx()][kezdo.gety()].setut(true);
    for(int i = 0; i<4; i++){
        switch(irany[i]){
            case fel:
                if(kezdo.gety() >= 2 && palya[kezdo.getx()][kezdo.gety()-2].getut() != true){
                    palya[kezdo.getx()][kezdo.gety()-1].setut(true);

                    Pont<int> uj(kezdo.getx(), kezdo.gety()-2);
                    kepez(uj);
                }
                break;
            case le:
               if(kezdo.gety() < window.gety()-2 && palya[kezdo.getx()][kezdo.gety()+2].getut() != true){
                    palya[kezdo.getx()][kezdo.gety()+1].setut(true);

                    Pont<int> uj(kezdo.getx(), kezdo.gety()+2);
                    kepez(uj);
                }
                break;
            case jobb:
                if(kezdo.getx() < window.getx()-2 && palya[kezdo.getx()+2][kezdo.gety()].getut() != true){
                    palya[kezdo.getx()+1][kezdo.gety()].setut(true);

                    Pont<int> uj(kezdo.getx()+2, kezdo.gety());
                    kepez(uj);
                }
                break;
            case bal:
                if(kezdo.getx() >= 2 && palya[kezdo.getx()-2][kezdo.gety()].getut() != true){
                    palya[kezdo.getx()-1][kezdo.gety()].setut(true);

                    Pont<int> uj(kezdo.getx()-2, kezdo.gety());
                    kepez(uj);
                }
                break;
        }
    }
    return;
}

void Palya::item_kepez()
{
    for(int i = 0; i<maxTargy; i++){
        int ix = rand() % window.getx();
        int iy = rand() % window.gety();

        while(palya[ix][iy].getut() != true){
            ix = rand() % window.getx();
            iy = rand() % window.gety();
        }
        if(i < maxTargy/2){
            Torch* t = new Torch(palya[ix][iy].getx(), palya[ix][iy].gety());
            targyak[i] = t;
        }
        else{
            Coin* c = new Coin(palya[ix][iy].getx(), palya[ix][iy].gety());
            targyak[i] = c;
        }

    }
}
