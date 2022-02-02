#include "Fuel.h"

Fuel::Fuel(Terreno T, int x, int y)
{
    dim_x=x;
    dim_y=y;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(0,1);
    bool t = dis(gen);

    uniform_int_distribution<> disT(1,T.getN()-2);
    int pos = disT(gen);

    terreno_x1 = T.getLarghezza(pos);
    terreno_x2 = T.getLarghezza(pos+1);
    terreno_y1 = T.getAltezza(pos);
    terreno_y2 = T.getAltezza(pos+1);

    fuel_x=abs((terreno_x2 - terreno_x1)/2) + min(terreno_x1,terreno_x2);
    fuel_y=dim_y-(abs((terreno_y2-terreno_y1)/2) + min(terreno_y1,terreno_y2));

    //tipologia del fuel: t = 0 => fuel = 2000; t = 1 => fuel = 4000
    type = t;

    if(t)
    {
        value = 2000;
        r = 15;
    }
    else
    {
        value = 4000;
        r = 25;
    }

    setRadius(r);
    setOrigin(r,r);
    setPosition(fuel_x, fuel_y);

}

int Fuel::getX()
{
    return fuel_x;
}
int Fuel::getY()
{
    return fuel_y;
}
int Fuel::getValue()
{
    return value;
}
int Fuel::getR()
{
    return r;
}
