#include <iostream>
#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>


class Screen_menu : public cScreen
{
private:
    //Velocità dell'intro
    const int intro_speed = 2;
    //Con questi due valori alpha_* gioco con l'opacità dell'immagine
    int alpha_max;
    int alpha_div;
    bool playing;

public:
    Screen_menu(void);
    void Reset();
    int Run(sf::RenderWindow &app);

};
