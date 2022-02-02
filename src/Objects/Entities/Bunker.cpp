#include "Bunker.h"

Bunker::Bunker(Terreno T, int x, int y)
{
    dim_x=x;
    dim_y=y;
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(0,1);
    tipologia = dis(gen);

    uniform_int_distribution<> disT(1,T.getN()-2);
    int pos = disT(gen);

    terreno_x1 = T.getLarghezza(pos);
    terreno_x2 = T.getLarghezza(pos+1);
    terreno_y1 = T.getAltezza(pos);
    terreno_y2 = T.getAltezza(pos+1);

    angolazione_terreno=-atan((float(terreno_y1 - terreno_y2)/float(terreno_x2-terreno_x1)))*180/3.14;

    bunker_x=abs((terreno_x2 - terreno_x1)/2) + min(terreno_x1,terreno_x2);
    bunker_y=dim_y-(abs((terreno_y2-terreno_y1)/2) + min(terreno_y1,terreno_y2));

    rotation=0;

    setRadius(r);
    setOrigin(r,r);
    setOutlineColor(sf::Color::Cyan);
    setOutlineThickness(3);
    setPosition(bunker_x, bunker_y);

    C.setSize(sf::Vector2f(r/4, -5*r/3));
    C.setOrigin(r/8,-r/8);
    C.setFillColor(sf::Color::Red);
    C.setPosition(bunker_x, bunker_y);

}

Bunker::Bunker()
{
};

void Bunker::Cannon(SpaceShip astronave, RenderWindow &Window)
{
    int astro_y = astronave.getPosition().y;
    int astro_x = astronave.getPosition().x;
    switch (tipologia)
    {
    /********************/
    case 0: //tipo che segue l'astronave
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

        break;

    /********************/
    case 1: //tipo che si muove di moto costante
        /*******************/
        if (rotation >= (90 - int(angolazione_terreno) - 10))
            v=1;
        else if (rotation <= (- 90 - int(angolazione_terreno) + 10))
            v=0;
        if (v==0)
            rotation = rotation + r_speed;
        else if (v==1)
            rotation = rotation - r_speed;

        break;

    }
    C.rotate(rotation-C.getRotation());
    Window.draw(C);
}

float Bunker::getRotation()
{
    return rotation;
}

int Bunker::getDmg()
{
    return dmg;
}

void Bunker::takeDamage(int damage)
{
    hp = hp - damage;
}

bool Bunker::isAlive()
{
    if (hp<=0)
        return false;
    else
        return true;
}

bool Bunker::touches(SpaceShip astronave)
{
    if(astronave.getGlobalBounds().intersects(C.getGlobalBounds()) || astronave.getGlobalBounds().intersects(getGlobalBounds()))
    {
        return true;
    }
    return false;
}

