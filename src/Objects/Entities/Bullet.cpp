#include "Bullet.h"

Bullet::Bullet()
{
    setPosition(0,0);
    setRadius(3);
    setFillColor(sf::Color::Cyan);
    setOrigin(3,3);
    sparato = false;
}

bool Bullet::moveBullet(int dim_x, int dim_y, float rot, int x0, int y0, bool k)
{
    // x0 e y0 sono le coordinate del "proprietario" del proiettile
    if((getPosition().x<dim_x)&&(getPosition().y>0)&&(getPosition().x>0)&&(getPosition().y<dim_y))
    {
        if(k)
        {
            dy=(-speed*  cos(ang*3.14/180.0));
            dx=(speed*  sin(ang*3.14/180.0));
            move(dx, dy);
        }
        else
        {
            setPosition(x0,y0);
            ang=rot;
        }
        return k;
    }
    else
    {
        ang=rot;
        setPosition(x0,y0);
        return false;
    }
}

int Bullet::getDmg()
{
    return dmg;
}

