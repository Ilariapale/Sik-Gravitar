#include "Screen_results.h"

int Screen_results::finalScreen(sf::RenderWindow &app)
{
    sf::Event event;
    bool running = true;
    std::string line;
    std::ifstream i_file;
    std::ofstream o_file;
    i_file.open("res/ladder.txt");
    if(!i_file)
    {
        std::cout<<"Impossiibile leggere il file ladder.txt";
        return 0;
    }
    int i = 0;
    while(getline(i_file, line)|| i<10)
    {
        ladder.push_back(line);
        i++;
    }
    i_file.close();

    //Ladder Sort
    int n = ladder.size();
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            int score_a = std::stoi(ladder[i].substr(4));
            int score_b = std::stoi(ladder[j].substr(4));
            if(score_a < score_b)
            {
                std::string appo = ladder[i];
                ladder[i] = ladder[j];
                ladder[j] = appo;
            }
        }
    }

    o_file.open("res/ladder.txt");
    if(!o_file)
    {
        std::cout<<"Impossiibile leggere il file ladder.txt";
        return 0;
    }
    //togliere il ladder.size()-1 se si vuole avere in memoria tutti i punteggi
    for(int i=0; i<ladder.size() - 1; i++)
    {
        o_file << ladder[i] + '\n';
    }
    o_file.close();

    while(running)
    {
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Return)
                {
                    return 9;
                }
            }

        }


        app.clear();

        //Draw scores;
        float pos_x_mx = 0.23;
        float pos_y_mx = 0.1;
        for(int i=1; i<11; i++)
        {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(i)+' '+ladder[i-1]);
            text.setCharacterSize(46);
            text.setPosition(app.getSize().x * pos_x_mx, app.getSize().y * pos_y_mx);
            app.draw(text);
            pos_y_mx += 0.12;
            if(i == 5)
            {
                pos_x_mx = 0.58;
                pos_y_mx = 0.1;
            }
        }

        t_enter.setColor(sf::Color(255, 0, 0, 200));
        app.draw(t_enter);

        app.display();

    }
    return -1;
}

Screen_results::Screen_results()
{
    font.loadFromFile("res/fonts/Orbitronio.ttf");

    //GAME OVER
    t_game_over.setFont(font);
    t_game_over.setString("GAME OVER");
    t_game_over.setCharacterSize(46);

    //SCORE
    t_score.setFont(font);
    t_score.setCharacterSize(46);

    //INSERT YOUR NAME
    t_name.setFont(font);
    t_name.setString("insert your name");
    t_name.setCharacterSize(46);
    t_name.setColor(sf::Color(255, 0, 0, 200));

    //PRESS ENTER TO CONTINUE
    t_enter.setFont(font);
    t_enter.setString("press enter to continue");
    t_enter.setCharacterSize(46);

    int letters_size = 200;
    letter_one_text.setFont(font);
    letter_one_text.setCharacterSize(letters_size);
    letter_two_text.setFont(font);
    letter_two_text.setCharacterSize(letters_size);
    letter_three_text.setFont(font);
    letter_three_text.setCharacterSize(letters_size);

    letter_one_text.setString(letter_one[letter_one_index]);
    letter_two_text.setString(letter_two[letter_two_index]);
    letter_three_text.setString(letter_three[letter_three_index]);

}

void Screen_results::Reset()
{
    score = 0;
    letter_one_index = 0;
    letter_two_index = 0;
    letter_three_index = 0;
    ladder.clear();
}

void Screen_results::setScore(int s_score)
{
    score = s_score;
}

int Screen_results::Run(sf::RenderWindow &app)
{
    sf::Event event;
    t_score.setString("score " + std::to_string(score));

    t_game_over.setPosition(app.getSize().x * 0.32, app.getSize().y * 0.12);
    t_score.setPosition(app.getSize().x * 0.395, app.getSize().y * 0.20);
    t_name.setPosition(app.getSize().x * 0.35, app.getSize().y * 0.40);

    letter_one_text.setPosition(app.getSize().x * 0.36, app.getSize().y * 0.39);
    letter_two_text.setPosition(app.getSize().x * 0.46, app.getSize().y * 0.39);
    letter_three_text.setPosition(app.getSize().x * 0.56, app.getSize().y * 0.39);

    t_enter.setPosition(app.getSize().x * 0.28, app.getSize().y * 0.77);
    t_enter.setColor(sf::Color(255, 255, 255, 255));

    bool running = true;
    while (running)
    {
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if(event.type == sf::Event::KeyPressed)
            {
                // Con W e S scorro la colonna di lettere
                if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    switch(current_letter)
                    {
                    case 0 :
                    {
                        letter_one_index--;
                        if(letter_one_index < 0) letter_one_index = letter_one.size()-1;
                        letter_one_text.setString(letter_one[letter_one_index]);
                        break;
                    }
                    case 1 :
                    {
                        letter_two_index--;
                        if(letter_two_index < 0) letter_two_index = letter_two.size()-1;
                        letter_two_text.setString(letter_two[letter_two_index]);
                        break;
                    }
                    case 2 :
                    {
                        letter_three_index--;
                        if(letter_three_index < 0) letter_three_index = letter_three.size()-1;
                        letter_three_text.setString(letter_three[letter_three_index]);
                        break;
                    }
                    }
                }
                if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    switch(current_letter)
                    {
                    case 0 :
                    {
                        letter_one_index++;
                        if(letter_one_index > letter_one.size()-1) letter_one_index = 0;
                        letter_one_text.setString(letter_one[letter_one_index]);
                        break;
                    }
                    case 1 :
                    {
                        letter_two_index++;
                        if(letter_two_index > letter_two.size()-1) letter_two_index = 0;
                        letter_two_text.setString(letter_two[letter_two_index]);
                        break;
                    }
                    case 2 :
                    {
                        letter_three_index++;
                        if(letter_three_index > letter_three.size()-1) letter_three_index = 0;
                        letter_three_text.setString(letter_three[letter_three_index]);
                        break;
                    }
                    }
                }
                // Con A e D scorro le colonne
                if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    current_letter++;
                    if(current_letter>2) current_letter = 0;
                }
                if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    current_letter--;
                    if(current_letter<0) current_letter = 2;
                }
                // Se premo INVIO confermo la selezione
                if(event.key.code == sf::Keyboard::Return)
                {
                    std::string user_score;
                    user_score+=letter_one[letter_one_index];
                    user_score+=letter_two[letter_two_index];
                    user_score+=letter_three[letter_three_index];
                    user_score+=' ';
                    user_score+=std::to_string(score);
                    ladder.push_back(user_score);
                    return finalScreen(app);
                }
            }
        }

        // A seconda di quale "colonna" di lettere sto usando, coloro le lettere della colonna
        switch(current_letter)
        {
        case 0 :
        {
            letter_one_text.setColor(sf::Color(255, 0, 0, 255));
            letter_two_text.setColor(sf::Color(255, 255, 255, 255));
            letter_three_text.setColor(sf::Color(255, 255, 255, 255));
            break;
        }
        case 1 :
        {
            letter_one_text.setColor(sf::Color(255, 255, 255, 255));
            letter_two_text.setColor(sf::Color(255, 0, 0, 255));
            letter_three_text.setColor(sf::Color(255, 255, 255, 255));
            break;
        }
        case 2 :
        {
            letter_one_text.setColor(sf::Color(255, 255, 255, 255));
            letter_two_text.setColor(sf::Color(255, 255, 255, 255));
            letter_three_text.setColor(sf::Color(255, 0, 0, 255));
            break;
        }
        }

        app.clear();

        app.draw(t_game_over);
        app.draw(t_score);
        app.draw(t_name);
        app.draw(letter_one_text);
        app.draw(letter_two_text);
        app.draw(letter_three_text);
        app.draw(t_enter);

        app.display();
    }

    return -1;
}
