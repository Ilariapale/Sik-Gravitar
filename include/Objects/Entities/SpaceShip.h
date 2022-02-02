#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics.hpp>

class SpaceShip: public sf::RectangleShape
{
private:
    int steps;
    int max_lives = 4;
    int lives = max_lives;
    int score = 00000;
    int fuel;
    int dmg = 50;
    sf::Texture textureRaggio;
    void setValues();

public:
    SpaceShip();
    sf::ConvexShape raggioTraente(int x_astronave, int y_astronave); //passare coordinate dell'astronave
    void shoot();
    void fuelUsage();
    int getSteps();
    int getLives();
    int getMaxLives();
    int getDmg();
    void takeDamage(int damage);
    int getScore();
    int getFuel();
    void updateFuel(int updatedFuel);
    void addScore(int add_score);
    void addFuel(int add_fuel);
    void fullHealth();
};

#endif
