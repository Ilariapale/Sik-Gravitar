#include "Planet.h"

void Planet::setRandomStats()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand_radius(50,85);
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> rand_color(0,255);
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> rand_alpha(100,255);

    int radius = rand_radius(rng);

    points = radius * 100;
    setRadius(radius);
    setFillColor(sf::Color(rand_color(rng), rand_color(rng), rand_color(rng), rand_alpha(rng)));
    float center = getRadius()/2;
    setOrigin(center,center);

    sf::Texture texture;
    texture.loadFromFile("res/images/backgrounds/menu_bg.png");
    setTexture(&texture);
}

void Planet::CreaOggettiDelPianeta()
{
    //Terreno
    terreno = Terreno(dim_x, dim_y);

    //Bunkers e proiettili
    int NUM_BUNKERS = 3;

    int T=0, numBunker=0;
    while(numBunker<NUM_BUNKERS)
    {
        Bunker bun = Bunker(terreno, dim_x, dim_y);
        for(int k=0; k<numBunker; k++)
        {
            if (bun.getPosition().x == bunkers[k].getPosition().x)
                T=1;
        }
        if(!T)
        {
            bunkers.push_back(bun);
            Bullet bul = Bullet();
            bullets.push_back(bul);
            numBunker++;
        }
        else
        {
            T=0;
        }
    }

    sf::Texture textureFuel;
    textureFuel.loadFromFile("res/images/Objects/fuel.png");

    //PowerUps
    int NUM_FUELS = 3;
    int numFuel=0;
    T=0;
    while(numFuel<NUM_FUELS)
    {
        Fuel fu = Fuel(terreno, dim_x, dim_y);
        for(int k=0; k<numFuel; k++)
        {
            if (fu.getX() == fuels[k].getX())
                T=1;
        }
        if(!T)
        {
            fuels.push_back(fu);
            fuels[numFuel].setTexture(&textureFuel);
            fuels[numFuel].setTextureRect(sf::IntRect(0, 0, fuels[numFuel].getR()*2, fuels[numFuel].getR()*2));
            numFuel++;
        }
        else
        {
            T=0;
        }
    }
}

Planet::Planet(int x, int y)
{
    dim_x = x;
    dim_y = y;
    setRandomStats();
    CreaOggettiDelPianeta();
}
//Costruttore fasullo
Planet::Planet()
{
}

Terreno Planet::getTerreno()
{
    return terreno;
}

std::vector<Bunker> Planet::getBunkers()
{
    return bunkers;
}

std::vector<Bullet> Planet::getBullets()
{
    return bullets;
}

Bullet Planet::getAstroBullet()
{
    return AstroBullet;
}

std::vector<Fuel> Planet::getFuels()
{
    return fuels;
}


int Planet::getPoints()
{
    return points;
}

void Planet::destroy()
{
    destroyed = true;
}

bool Planet::isDestroyed()
{
    return destroyed;
}

void Planet::updateBunkers(std::vector<Bunker> b)
{
    bunkers = b;
}

void Planet::updateFuels(std::vector<Fuel> f)
{
    fuels = f;
}

void Planet::updateBullets(std::vector<Bullet> b)
{
    bullets = b;
}
void Planet::updateAstroB(Bullet b)
{
    AstroBullet = b;
}
