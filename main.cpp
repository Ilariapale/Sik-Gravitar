#include <iostream>
#include <SFML/Graphics.hpp>
#include "include/Objects/Screens/Screens.h"

int main(int argc, char** argv)
{
    //Variabili
    std::vector<cScreen*> Screens;
    int screen = 0;

    //Creo la finestra e tolgo il mouse
    sf::RenderWindow app(sf::VideoMode(1366, 768), "S.I.K. AntiGravitar", sf::Style::Titlebar | sf::Style::Close);
    app.setMouseCursorVisible(false);

    //Gestione finestre
    Screen_menu s_menu;
    Screens.push_back(&s_menu);
    Screen_game s_game;
    Screens.push_back(&s_game);
    Screen_results s_results;
    Screens.push_back(&s_results);

    //Esecuzione
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(app);

        //Schermata Punteggi
        if(screen == 2)
        {
            s_results.setScore(s_game.getScore());
        }

        //New Game
        if(screen == 9)
        {
            Screens[0]->Reset();
            Screens[1]->Reset();
            Screens[2]->Reset();
            screen = 0;
        }
    }

    return EXIT_SUCCESS;
}
