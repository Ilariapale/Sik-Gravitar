#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

class Bullet : public sf::CircleShape
{
private:
    int dmg = 1;
    int speed = 2;
    float ang;
    float dx=1;
    float dy=1;
    bool sparato;


public:
    Bullet();
    bool moveBullet(int dim_x, int dim_y, float rot, int x0, int y0, bool k);
    int getDmg();
};

#endif // BULLET_H
