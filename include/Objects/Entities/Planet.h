#ifndef PLANET.H
#define PLANET.H
#include <SFML/Graphics.hpp>
#include "Terreno.h"
#include "Bunker.h"
#include "BunkerA.h"
#include "Fuel.h"
#include "Bullet.h"
#include <random>

class Planet : public sf::CircleShape
{
private:
    int dim_x, dim_y;
    int points;
    bool destroyed = false;
    Terreno terreno;
    std::vector<Bunker> bunkers;
    std::vector<Fuel> fuels;
    std::vector<Bullet> bullets;
    Bullet AstroBullet = Bullet(); //bullet dell'astronave

    void setRandomStats();
    void CreaOggettiDelPianeta();

public:
    Planet(int x, int y);
    //Costruttore fasullo
    Planet();
    Terreno getTerreno();
    std::vector<Bunker> getBunkers();
    std::vector<Bullet> getBullets();
    Bullet getAstroBullet();
    std::vector<Fuel> getFuels();
    int getPoints();
    void destroy();
    bool isDestroyed();
    void updateBunkers(std::vector<Bunker> b);
    void updateFuels(std::vector<Fuel> f);
    void updateBullets(std::vector<Bullet> b);
    void updateAstroB(Bullet b);
};

#endif
