

#ifndef PALYA_H_INCLUDED
#define PALYA_H_INCLUDED

#include "Blokk.h"
#include "Torch.h"
#include "Coin.h"


#define maxTargy 10

enum Irany{
    fel,
    le,
    jobb,
    bal
};

class Item;
class Palya
{
    public:
        Blokk** palya;
        Item* targyak[maxTargy];

    private:
        Pont<int> window;
        Pont<float> kiut;
        float hossz;

    public:
        Palya(int x1 = 0, int y1 = 0, float h = 80.0f);

        Palya(const Palya& p);

        ~Palya();

        //get-set

        Pont<int> getwin()const;

        void setwin(const Pont<int> p);

        void setkiut();

        Pont<float>getkiut()const;

        //operator

        Palya& operator=(const Palya& p);

        //draw
        void rajz(sf::RenderWindow& w);

        //else
        void kepez(Pont<int> kezdo);

        void item_kepez();
};
#endif // PALYA_H_INCLUDED
