#ifndef BUNKER_H
#define BUNKER_H
#include "Terreno.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Bunker : public sf::CircleShape
{
protected:
    int tipologia;
    int hp = 200;
    int r = 32;
    int bunker_x;
    int bunker_y;
    int dmg = 1;
    int v=0;
    float rotation;
    float yProiettile;
    float xProiettile;
    int dim_x;
    int dim_y;
    int last_space_pos_x = 0;
    int last_space_pos_y = 0;
    int terreno_x1 = 0;
    int terreno_y1 = 0;
    int terreno_x2 = 0;
    int terreno_y2 = 0;
    float angolazione_terreno=0;
    float angolazione_astronave=0;
    float r_speed = 0.3;

    sf::RectangleShape C;

    sf::Text textCannone;
public:
    Bunker(Terreno T, int x, int y);
    Bunker();
    virtual void Cannon(SpaceShip astronave, RenderWindow &Window);
    float getRotation();
    int getDmg();
    void takeDamage(int damage);
    bool isAlive();
    bool touches(SpaceShip astronave);
};
#endif // BUNKER_H
