#ifndef SCREEN_RESULTS_H
#define SCREEN_RESULTS_H
#include "cScreen.h"
#include <fstream>
#include <iostream>

class Screen_results : public cScreen
{
private:
    sf::Font font;

    //GAME OVER
    sf::Text t_game_over;
    //SCORE
    sf::Text t_score;
    //PRESS ENTER TO CONTINUE
    sf::Text t_enter;
    //INSERT YOUR NAME
    sf::Text t_name;

    //Le 3 lettere del nome
    sf::Text letter_one_text;
    sf::Text letter_two_text;
    sf::Text letter_three_text;

    //Gestione delle lettere
    std::vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0'};
    std::vector<char> letter_one = alphabet;
    std::vector<char> letter_two = alphabet;
    std::vector<char> letter_three = alphabet;
    int letter_one_index = 0;
    int letter_two_index = 0;
    int letter_three_index = 0;

    //Gestione classifica generale
    std::vector<std::string> ladder;

    int current_letter = 0;

    int score = 0;

    int finalScreen(sf::RenderWindow &app);


public:
    Screen_results();
    void Reset();
    void setScore(int s_score);
    int Run(sf::RenderWindow &app);
};

#endif // SCREEN_RESULTS_H
