#include "SpaceShip.h"

void SpaceShip::setValues()
{
    //Velocità dell'oggetto
    steps = 2;
    //Colore dell'oggetto
    setFillColor(sf::Color(255, 255, 255, 255));
    //Dimensione dell'oggetto
    setSize({ 40.f, 40.f });
    setOrigin(getSize().x/2, getSize().y/2);
    fuel = 5000;
    //textures
    textureRaggio.loadFromFile("res/images/Objects/raggio-01.png");
}

SpaceShip::SpaceShip()
{
    setValues();
}


sf::ConvexShape SpaceShip::raggioTraente(int x_astronave, int y_astronave) //passare coordinate dell'astronave
{
    sf::ConvexShape raggio;
    raggio.setPointCount(3);
    raggio.setPoint(0, sf::Vector2f(x_astronave, y_astronave));
    raggio.setPoint(1, sf::Vector2f(x_astronave+30, y_astronave+200));
    raggio.setPoint(2, sf::Vector2f(x_astronave-30, y_astronave+200));

    raggio.setTexture(&textureRaggio);

    return raggio;
}

void SpaceShip::shoot()
{
}
void SpaceShip::fuelUsage()
{
    fuel-=1;
}

int SpaceShip::getSteps()
{
    return steps;
}

int SpaceShip::getLives()
{
    return lives;
}

int SpaceShip::getMaxLives()
{
    return max_lives;
}

int SpaceShip::getDmg()
{
    return dmg;
}

void SpaceShip::takeDamage(int damage)
{
    lives -= damage;
}

int SpaceShip::getScore()
{
    return score;
}

int SpaceShip::getFuel()
{
    return fuel;
}

void SpaceShip::updateFuel(int updatedFuel)
{
    fuel=updatedFuel;
}

void SpaceShip::addScore(int add_score)
{
    score += add_score;
}

void SpaceShip::addFuel(int add_fuel)
{
    fuel += add_fuel;
}

void SpaceShip::fullHealth()
{
    lives = max_lives;
}
