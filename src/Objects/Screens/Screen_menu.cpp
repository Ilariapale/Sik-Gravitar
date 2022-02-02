#include "../../../include/Objects/Screens/Screen_menu.h"

Screen_menu::Screen_menu(void)
{
    alpha_max = intro_speed * 255;
    alpha_div = intro_speed;
    playing = false;
};

void Screen_menu::Reset()
{
    playing = false;
}

int Screen_menu::Run(sf::RenderWindow &app)
{
    sf::Event event;
    bool Running = true;
    sf::Texture texture;
    sf::Sprite menu_bg;
    sf::Font font;
    sf::Text menu_voce_play;
    sf::Text menu_voce_exit;
    sf::Text menu_voce_cont;
    int alpha = 0;
    int menu_current = 0;

    int screen_w = app.getSize().x;
    int screen_h = app.getSize().y;
    float menu_position = screen_h - 280;
    float font_size = screen_h / 9;
    float font_size_w = (font_size / 2 ) - ( (font_size / 100) * 10);
    float font_spacer = (font_size / 100) * 140;


    if (!texture.loadFromFile("res/images/backgrounds/menu_bg.png"))
    {
        std::cerr << "Errore durante il caricamento del background del menu" << std::endl;
        return (-1);
    }
    menu_bg.setTexture(texture);
    menu_bg.setColor(sf::Color(255, 255, 255, alpha));
    if (!font.loadFromFile("res/fonts/Orbitronio.ttf"))
    {
        std::cerr << "Errore durante il caricamento del font" << std::endl;
        return (-1);
    }
    menu_voce_play.setFont(font);
    menu_voce_play.setCharacterSize(font_size);
    menu_voce_play.setString("Play");
    menu_voce_play.setOrigin((menu_voce_play.getLetterSpacing() * menu_voce_play.getString().getSize()) + (menu_voce_play.getString().getSize() * font_size_w ), font_size / 2);
    menu_voce_play.setPosition({ screen_w / 2, menu_position / 2 });

    menu_voce_exit.setFont(font);
    menu_voce_exit.setCharacterSize(font_size);
    menu_voce_exit.setString("Exit");
    menu_voce_exit.setOrigin((menu_voce_exit.getLetterSpacing() * menu_voce_exit.getString().getSize()) + (menu_voce_exit.getString().getSize() * font_size_w ), font_size / 2);
    menu_voce_exit.setPosition({ screen_w / 2, (menu_position / 2) + font_spacer });

    menu_voce_cont.setFont(font);
    menu_voce_cont.setCharacterSize(font_size);
    menu_voce_cont.setString("Continue");
    float m3_origin_x = (menu_voce_cont.getLetterSpacing() * menu_voce_cont.getString().getSize()) + (menu_voce_cont.getString().getSize() * font_size_w);
    menu_voce_cont.setOrigin(m3_origin_x - ((screen_w/100) * 5 ), font_size / 2);
    menu_voce_cont.setPosition({ screen_w / 2, menu_position / 2 });

    //Se sto giocando, salto l'intro
    if (playing)
    {
        alpha = alpha_max;
    }

    while (Running)
    {
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:  //Freccia SU
                    menu_current = 0;
                    break;
                case sf::Keyboard::Down:  //Freccia GIU
                    menu_current = 1;
                    break;
                case sf::Keyboard::Return: //Invio
                    if (menu_current == 0)
                    {
                        //Se sto gia giocando, salto il tutorial
                        if(!playing)
                        {
                            sf::Sprite tutorial;
                            sf::Texture texture_tutorial;
                            if (!texture_tutorial.loadFromFile("res/images/backgrounds/tutorial_bg.png"))
                            {
                                std::cerr << "Errore durante il caricamento dell'immagine tutorial" << std::endl;
                                return (-1);
                            }
                            tutorial.setTexture(texture_tutorial);
                            app.clear();
                            app.draw(tutorial);
                            app.display();
                            std::chrono::milliseconds timespan(3000); // or whatever
                            std::this_thread::sleep_for(timespan);
                            playing = true;
                        }
                        return (1);
                    }
                    else
                    {
                        if(playing == true)
                        {
                            return 9;
                        }
                        return (-1);
                    }
                    break;
                default:
                    break;
                }
            }
        }
        if (alpha<alpha_max)
        {
            alpha++;
        }
        menu_bg.setColor(sf::Color(255, 255, 255, alpha / alpha_div));

        //Coloro la voce del menu selezionata
        if (menu_current == 0)
        {
            menu_voce_play.setColor(sf::Color(255, 0, 0, 255));
            menu_voce_exit.setColor(sf::Color(255, 255, 255, 255));
            menu_voce_cont.setColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            menu_voce_play.setColor(sf::Color(255, 255, 255, 255));
            menu_voce_exit.setColor(sf::Color(255, 0, 0, 255));
            menu_voce_cont.setColor(sf::Color(255, 255, 255, 255));
        }

        app.clear();
        app.draw(menu_bg);

        //Se l'intro è finita mostro il menu
        if (alpha == alpha_max)
        {
            if (playing)
            {
                app.draw(menu_voce_cont);
            }
            else
            {
                app.draw(menu_voce_play);
            }
            app.draw(menu_voce_exit);
        }
        app.display();
    }


    return (-1);
}
