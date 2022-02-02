#ifndef BUNKERA_H
#define BUNKERA_H

#include "Bunker.h"
#include "Terreno.h"


class BunkerA : public Bunker
{
public:
    BunkerA(Terreno T, int x, int y):Bunker(T, x, y)
    {
    }
    virtual ~BunkerA() {};

    void Cannon(SpaceShip astronave, RenderWindow &Window) override
    {
        int astro_y = astronave.getPosition().y;
        int astro_x = astronave.getPosition().x;
        // proiettile.getFillColor(sf::Color::White);
        /********************/
        if(bunker_y!=astro_y)
            angolazione_astronave=+atan(float (astro_x - bunker_x)/(float (bunker_y - astro_y)))*180/3.14;
        else
        {
            if (astro_x < bunker_x)
                angolazione_astronave = -90;
            else
                angolazione_astronave = 90;
        }
        if(angolazione_terreno >= 0)
        {
            if(astro_y <= bunker_y)          //caso 1A
            {
                if(angolazione_astronave >= (90-angolazione_terreno))
                    rotation = 90 - angolazione_terreno;
                else
                    rotation = angolazione_astronave;
            }
            else                             //caso 1B
            {
                if(angolazione_astronave <= (90 - angolazione_terreno))
                {
                    if(angolazione_astronave > 0)
                        rotation = -90 - angolazione_terreno;
                    else
                        rotation = 90 - angolazione_terreno;
                }
                else
                    rotation = angolazione_astronave - 180;
            }
        }
        else
        {
            if(astro_y <= bunker_y)      //caso 2A
            {
                if(angolazione_astronave <= (-90 - angolazione_terreno))
                    rotation = -90 -angolazione_terreno;
                else
                    rotation = angolazione_astronave;
            }
            else                         //caso 2B
            {
                if(angolazione_astronave >= (-90 - angolazione_terreno))
                {
                    if (angolazione_astronave < 0)
                        rotation = 90 - angolazione_terreno;
                    else
                        rotation = - 90 - angolazione_terreno;
                }
                else
                    rotation = angolazione_astronave + 180;
            }
        }
        C.rotate(rotation-C.getRotation());
        Window.draw(C);
    }

protected:

private:

};

#endif // BUNKERA_H
