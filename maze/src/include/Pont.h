#ifndef PONT_H
#define PONT_H

#include <iostream>
#include "memtrace.h"

template<typename T>
class Pont{

    protected:

        T x;
        T y;

    public:
        Pont(T x1 = 0, T y1 = 0):x(x1), y(y1){}

        Pont(const Pont& p)
        {
            x = p.getx();
            y = p.gety();
        }

        //operatorok

        Pont& operator=(const Pont& p)
        {
            if(this != &p){
                x = p.x;
                y = p.y;
            }
            return *this;
        }

        Pont operator+(const Pont& p)
        {
           return Pont(x + p.x, y + p.y);
        }

        Pont operator-(const Pont& p)
        {
            return Pont(x - p.x, y + p.y);
        }

        Pont operator*(const int i)
        {
            return Pont(x*i, y*i);
        }

        //get-set

        T getx() const
        {
            return x;
        }

        T gety() const
        {
            return y;
        }


        void setx(T X)
        {
            x = X;
        }

        void sety(T Y)
        {
            y = Y;
        }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Pont<T>& p)
{
    os<<"x koordinata: "<<p.getx()<<"\ty koordinata"<<p.gety()<<std::endl;
    return os;
}
#endif // PONT_H
