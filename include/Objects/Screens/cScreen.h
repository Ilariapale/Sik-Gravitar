#ifndef CSCREEN_H
#define CSCREEN_H
#include <SFML/Graphics.hpp>

class cScreen
{
public :
    virtual int Run (sf::RenderWindow &app) = 0;
    virtual void Reset () = 0;
};

#endif
