#ifndef FUEL_H
#define FUEL_H
#include "SpaceShip.h"
#include "Terreno.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Fuel : public sf::CircleShape
{
private:
    int tipologia;
    int fuel_x;
    int fuel_y;
    int r;
    int dim_x;
    int dim_y;
    int last_space_pos_x = 0;
    int last_space_pos_y = 0;
    int terreno_x1 = 0;
    int terreno_y1 = 0;
    int terreno_x2 = 0;
    int terreno_y2 = 0;
    bool type;
    int value;


    sf::Texture fuelTexture;

public:
    Fuel(Terreno T, int x, int y);
    int getX();
    int getY();
    int getValue();
    int getR();
};

#endif // FUEL_H
