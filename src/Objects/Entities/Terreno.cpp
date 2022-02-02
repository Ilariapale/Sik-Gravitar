#include "Terreno.h"

Terreno::Terreno(int risX, int risY)
{
    rX=risX;
    rY=risY;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(risY/9,risY*2/5);
    for (int k=0; k<=n; k++)
    {
        altezza.push_back(dis(gen));
        larghezza.push_back(k*risX/n);
    }
}

Terreno::Terreno()
{
}


void Terreno::Stampa(RenderWindow &Window)
{
    sf::VertexArray quad(sf::Quads, 4);
    sf::Texture t;
    t.loadFromFile("res/images/Objects/terreno4B.jpg");
    t.setRepeated(true);


    for(int k=0; k<=n-1; k++)
    {
        quad[0].position = sf::Vector2f(larghezza[k], rY);
        quad[1].position = sf::Vector2f(larghezza[k], rY - altezza[k]);
        quad[2].position = sf::Vector2f(larghezza[k+1], rY - altezza[k+1]);
        quad[3].position = sf::Vector2f(larghezza[k+1], rY);

        quad[0].texCoords = sf::Vector2f(larghezza[k], rY);
        quad[1].texCoords = sf::Vector2f(larghezza[k], rY - altezza[k]);
        quad[2].texCoords = sf::Vector2f(larghezza[k+1], rY - altezza[k+1]);
        quad[3].texCoords = sf::Vector2f(larghezza[k+1], rY);

        Window.draw(quad, &t);
    }
}
int Terreno::getAltezza(int i)
{
    return altezza[i];
}
int Terreno::getLarghezza(int i)
{
    return larghezza[i];
}

int Terreno::getN()
{
    return n;
}

bool Terreno::touches(int objX, int objY) //quando viene usato per l'astronave, bisogna aumentare la y di qualche pixel perchè non è un punto
{
    int y;
    int c = rX/n;
    int d = objX/c;
    if(larghezza[d]>objX)
        d--;
    if ((objX>0)&&(objX<rX))
        y = (float(objX - larghezza[d])/float(larghezza[d+1] - larghezza[d])) * (altezza[d+1] - altezza[d]) +  altezza[d]; // y in cui collide
    else
        y = 0;
    return(((rY - objY) <= y));
}
