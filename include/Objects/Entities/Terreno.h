#ifndef TERRENO_H
#define TERRENO_H
#include <random>
#include <SFML/Graphics.hpp>
#include "SpaceShip.h"
#include <iostream>
using namespace std;
using namespace sf;

class Terreno
{
private:
    int n=10; //max ris x
    vector<int> altezza;
    vector<int> larghezza;
    sf::Texture textTerreno;
    int rX, rY;
public:
    Terreno(int risX, int risY);
    //Costruttore Farlocco
    Terreno();
    void Stampa(RenderWindow &Window);
    int getAltezza(int i);
    int getLarghezza(int i);
    int getN();
    bool touches(int objX, int objY);
};

#endif // TERRENO_H
