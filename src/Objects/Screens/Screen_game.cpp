#include "../../../include/Objects/Screens/Screen_game.h"

int Screen_game::runPlanet(sf::RenderWindow &app)
{
    bool running_planet = true;

    SpaceShip spaceShip_planet;
    spaceShip_planet.setTexture(&textureShip);
    spaceShip_planet.setPosition(lastPosition_x, lastPosition_y);

    Terreno terreno = onPlanet_planet.getTerreno();
    std::vector<Bunker> bunkers = onPlanet_planet.getBunkers();
    std::vector<Fuel> fuels = onPlanet_planet.getFuels();
    std::vector<Bullet> bullets = onPlanet_planet.getBullets();
    Bullet astroBullet = onPlanet_planet.getAstroBullet();

    while(running_planet)
    {

        sf::Event event;

        if(spaceShip_galaxy.getLives()<1)
        {
            return (2);
        }

        if(spaceShip_galaxy.getFuel()<1)
        {
            return (2);
        }

        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
        }

        app.clear();

        if(loadTexturesInPlanet)
        {
            loadTexturesInPlanet = false;
        }

        //Controllo quali tasti sono premuti
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            //Se viene premuto il tasto ESC mi salvo le istanze dei vari oggetti e torno al menu
            lastPosition_x = spaceShip_planet.getPosition().x;
            lastPosition_y = spaceShip_planet.getPosition().y;
            onPlanet_planet.updateAstroB(astroBullet);
            onPlanet_planet.updateBunkers(bunkers);
            onPlanet_planet.updateBullets(bullets);
            onPlanet_planet.updateFuels(fuels);
            planets[num_onPlanet_planet] = onPlanet_planet;
            return (0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
        {
            spaceShip_planet.move(0, -spaceShip_planet.getSteps());
            if((spaceShip_planet.getPosition().y + (spaceShip_planet.getSize().y/2)) < 0)
            {
                game_state = 0;
                lastPosition_x = app.getSize().x/2;
                lastPosition_y = 40;
                onPlanet_planet.updateBunkers(bunkers);
                onPlanet_planet.updateFuels(fuels);
                planets[num_onPlanet_planet] = onPlanet_planet;
                return 1;
            }
            spaceShip_galaxy.fuelUsage();
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::S))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
        {
            spaceShip_planet.move(0, spaceShip_planet.getSteps());
            spaceShip_galaxy.fuelUsage();
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::D))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        {
            spaceShip_planet.move(spaceShip_planet.getSteps(), 0);
            if((spaceShip_planet.getPosition().x - (spaceShip_planet.getSize().x/2)) > app.getSize().x)
            {
                spaceShip_planet.setPosition(-(spaceShip_planet.getSize().x/2),spaceShip_planet.getPosition().y);
            }
            spaceShip_galaxy.fuelUsage();
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::A))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
        {
            spaceShip_planet.move(-spaceShip_planet.getSteps(), 0);
            if((spaceShip_planet.getPosition().x + (spaceShip_planet.getSize().x/2)) < 0)
            {
                spaceShip_planet.setPosition((app.getSize().x + spaceShip_planet.getSize().x/2),spaceShip_planet.getPosition().y);
            }
            spaceShip_galaxy.fuelUsage();
        }

        //Spara
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)&&(!E))
            E=true;

        E = astroBullet.moveBullet(app.getSize().x, app.getSize().y, 180, spaceShip_planet.getPosition().x, spaceShip_planet.getPosition().y, E) ;

        //collisioni tra terreno e proiettile dell'astronave
        if(terreno.touches(astroBullet.getPosition().x, astroBullet.getPosition().y))
            astroBullet.move(spaceShip_planet.getPosition());

        // raggio traente
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            int     x = spaceShip_planet.getPosition().x,
                    y = spaceShip_planet.getPosition().y;
            app.draw(spaceShip_planet.raggioTraente(x, y));
            for(int i = 0; i < fuels.size(); i++)
            {
                if((x>(fuels[i].getX()-50))&&(x<(fuels[i].getX()+50))&&(y>(fuels[i].getY()-200)))
                {
                    spaceShip_galaxy.addFuel(fuels[i].getValue());
                    fuels.erase(fuels.begin() + i);
                }
            }
        }

        //Controllo le collisioni con il terreno
        if(terreno.touches(spaceShip_planet.getPosition().x, spaceShip_planet.getPosition().y + 10))
        {
            spaceShip_galaxy.takeDamage(1);
            spaceShip_planet.move(0, -50);
        }

        for(int i=0; i<bunkers.size(); i++)
        {
            bullets[i].moveBullet(app.getSize().x, app.getSize().y, bunkers[i].getRotation(),bunkers[i].getPosition().x, bunkers[i].getPosition().y,true);

            if(bunkers[i].touches(spaceShip_planet))
            {
                spaceShip_galaxy.takeDamage(1);
                spaceShip_planet.move(0, -50);
            }
            //collisioni tra terreno e proiettili dei bunker
            if(terreno.touches(bullets[i].getPosition().x, bullets[i].getPosition().y))
            {
                bullets[i].moveBullet(app.getSize().x, app.getSize().y, bunkers[i].getRotation(), bunkers[i].getPosition().x, bunkers[i].getPosition().y, false);
            }
            //collisione tra bunker e proiettile dell'astronave. i bunkers prendono danno e se i loro hp sono <= 0 vengono eliminati dal vettore
            if(astroBullet.getGlobalBounds().intersects(bunkers[i].getGlobalBounds()))
            {
                bunkers[i].takeDamage(spaceShip_galaxy.getDmg());
                astroBullet.move(spaceShip_planet.getPosition());
                if(!bunkers[i].isAlive())
                {
                    bunkers.erase(bunkers.begin() + i);
                }
            }
            //collisione tra proiettili dei bunker con l'astronave
            if(bullets[i].getGlobalBounds().intersects(spaceShip_planet.getGlobalBounds()))
            {
                spaceShip_galaxy.takeDamage(bunkers[i].getDmg());
                bullets[i].move(bunkers[i].getPosition());
            }
        }

        if(bunkers.size()==0)
        {
            if(!onPlanet_planet.isDestroyed())
            {
                onPlanet_planet.destroy();
                spaceShip_galaxy.addScore(planets[num_onPlanet_planet].getPoints());
                destroyed_planets++;
            }
        }



        for(int i=0; i<fuels.size(); i++)
        {
            fuels[i].setTexture(&textureFuel);
            app.draw(fuels[i]);
        }

        // Ciclo i bunkers, li stampo e attivo il trigger dello sparo
        for(int i=0; i<bunkers.size(); i++)
        {
            app.draw(bullets[i]);
            bunkers[i].Cannon(spaceShip_planet, app);
            app.draw(bunkers[i]);
        }

        app.draw(astroBullet);
        app.draw(spaceShip_planet);

        // Gestione della stampa delle vite del giocatore
        int coord_x = 50;
        sf::RectangleShape live;
        live.setSize({ 30.f, 30.f });
        live.setTexture(&livesTexture);
        for(int num = 0; num<spaceShip_galaxy.getMaxLives(); num++)
        {
            if(num==spaceShip_galaxy.getLives())
            {
                live.setTexture(&livesTexture_empty);
            }
            live.setPosition(coord_x, 20);
            app.draw(live);
            coord_x += 35;
        }

        t_score.setString("score " + std::to_string(spaceShip_galaxy.getScore()));
        app.draw(t_score);

        serbatoio.setString(to_string(spaceShip_galaxy.getFuel()));
        app.draw(serbatoio);

        terreno.Stampa(app);

        app.display();
    }
    return -1;
}

int Screen_game::runGalaxy(sf::RenderWindow &app)
{
    bool running_galaxy = true;

    while (running_galaxy)
    {
        sf::Event event;

        if(spaceShip_galaxy.getLives()<1)
        {
            return (2);
        }

        if(spaceShip_galaxy.getFuel()<1)
        {
            return (2);
        }

        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return (-1);
            }
        }

        // Controllo le collisioni con i bordi
        bool touching_top = (spaceShip_galaxy.getPosition().y < 0);
        bool touching_bottom = (spaceShip_galaxy.getPosition().y > app.getSize().y);
        bool touching_left = (spaceShip_galaxy.getPosition().x < 0);
        bool touching_right = (spaceShip_galaxy.getPosition().x > app.getSize().x);

        // Nel caso tocco un bordo e il flag è a true creo una nuova galassia
        if(change_galaxy && (touching_top || touching_bottom || touching_left || touching_right))
        {
            change_galaxy = false;
            spaceShip_galaxy.fullHealth();
            destroyed_planets = 0;
            loadTextures = true;
            CreateRandomPlanets();

            if(touching_top)
            {
                spaceShip_galaxy.setPosition(spaceShip_galaxy.getPosition().x, app.getSize().y);
            }
            if(touching_bottom)
            {
                spaceShip_galaxy.setPosition(spaceShip_galaxy.getPosition().x, 0);
            }
            if(touching_left)
            {
                spaceShip_galaxy.setPosition(app.getSize().x, spaceShip_galaxy.getPosition().y);
            }
            if(touching_right)
            {
                spaceShip_galaxy.setPosition(0, spaceShip_galaxy.getPosition().y);
            }
        }

        bool onPlanet_cond = false;

        std::random_device dev;
        std::mt19937 rng(dev());

        for(int j = 0; j< planets.size() ; j++)
        {
            if(loadTextures)
            {
                rng.seed(std::random_device()());
                std::uniform_int_distribution<std::mt19937::result_type> rand_n(1,3);
                int selectTexture = rand_n(rng);
                switch(selectTexture)
                {
                case 1 :
                    planets[j].setTexture(&texture1);
                    break;
                case 2 :
                    planets[j].setTexture(&texture2);
                    break;
                case 3 :
                    planets[j].setTexture(&texture3);
                    break;
                }
                planets[j].setTextureRect(sf::IntRect(20,20,planets[j].getRadius()*2,planets[j].getRadius()*2));
            }
            if(!onPlanet_cond && spaceShip_galaxy.getGlobalBounds().intersects(planets[j].getGlobalBounds()))
            {
                onPlanet_cond = true;
                onPlanet_planet = planets[j];
                num_onPlanet_planet = j;
                planets[j].setOutlineThickness(3);
            }
            else
            {
                planets[j].setOutlineThickness(0);
            }
        }

        loadTextures = false;

        //Controllo quali tasti sono premuti
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            return (0);
        }
        if(!touching_top && ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))))
        {
            spaceShip_galaxy.move(0, -spaceShip_galaxy.getSteps());
            spaceShip_galaxy.fuelUsage();
        }
        if(!touching_bottom && ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))))
        {
            spaceShip_galaxy.move(0, spaceShip_galaxy.getSteps());
            spaceShip_galaxy.fuelUsage();
        }
        if(!touching_right && ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))))
        {
            spaceShip_galaxy.move(spaceShip_galaxy.getSteps(), 0);
            spaceShip_galaxy.fuelUsage();
        }
        if(!touching_left && ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))
        {
            spaceShip_galaxy.move(-spaceShip_galaxy.getSteps(), 0);
            spaceShip_galaxy.fuelUsage();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            if(onPlanet_cond && !onPlanet_planet.isDestroyed())
            {
                game_state = 1;
                return 1;
            }
        }

        //Controllo se tutti i pianeti sono distrutti
        if(destroyed_planets >= total_planets)
        {
            change_galaxy = true;
        }

        //Refresh
        app.clear();
        for(int i =0; i<planets.size(); i++)
        {
            if(!planets[i].isDestroyed())
            {
                planet_points.setString(std::to_string(planets[i].getPoints()));
                planet_points.setPosition(planets[i].getPosition().x, planets[i].getPosition().y + (planets[i].getRadius() * 1.33));

                app.draw(planet_points);
                app.draw(planets[i]);
            }
        }

        app.draw(spaceShip_galaxy);

        int coord_x = 50;
        sf::RectangleShape live;
        live.setSize({ 30.f, 30.f });
        live.setTexture(&livesTexture);
        for(int num = 0; num<spaceShip_galaxy.getMaxLives(); num++)
        {
            if(num==spaceShip_galaxy.getLives())
            {
                live.setTexture(&livesTexture_empty);
            }
            live.setPosition(coord_x, 20);
            app.draw(live);
            coord_x += 35;
        }

        app.draw(t_score);

        serbatoio.setString(to_string(spaceShip_galaxy.getFuel()));
        app.draw(serbatoio);

        app.display();
    }
    return -1;
}

Screen_game::Screen_game(void)
{
    //carico il font
    font.loadFromFile("res/fonts/Orbitronio.ttf");
    //Posiziono l'astronave
    spaceShip_galaxy.setPosition(posx,posy);
}

int Screen_game::getScore()
{
    return spaceShip_galaxy.getScore();
}

void Screen_game::Reset()
{
    game_state = 0;
    first_time_boot = true;
    change_galaxy = false;
    loadTextures = true;
    destroyed_planets = 0;
    CreateRandomPlanets();
    spaceShip_galaxy = SpaceShip();
    spaceShip_galaxy.setPosition(posx,posy);
}

int Screen_game::Run(sf::RenderWindow &app)
{
    dim_x = app.getSize().x;
    dim_y = app.getSize().y;

    t_score.setFont(font);
    t_score.setCharacterSize(30);
    t_score.setPosition(1100,10);

    serbatoio.setFont(font);
    serbatoio.setCharacterSize(30.f);
    serbatoio.setColor(sf::Color::Yellow);
    serbatoio.setPosition({300, 10});

    textureShip.loadFromFile("res/images/Objects/astronave.png");

    livesTexture.loadFromFile("res/images/Objects/life.png");
    livesTexture_empty.loadFromFile("res/images/Objects/lifeEmpty1.png");

    textureFuel.loadFromFile("res/images/Objects/fuel.png");

    spaceShip_galaxy.setTexture(&textureShip);

    planet_points.setFont(font);
    planet_points.setCharacterSize(24);

    if(first_time_boot)
    {
        //Setto la posizione iniziale della navicella sul pianeta
        lastPosition_x = app.getSize().x/2;
        //Creo i pianeti
        CreateRandomPlanets();

        texture1.loadFromFile("res/images/Objects/Pianeta4.png");
        texture2.loadFromFile("res/images/Objects/Pianeta5.png");
        texture3.loadFromFile("res/images/Objects/Pianeta6.png");

        first_time_boot = false;
    }

    bool running = true;
    int ret = 1;
    while (running)
    {
        if(game_state == 0)
        {
            // Passo alla visualizzazione della galassia
            ret = runGalaxy(app);
        }
        if(game_state == 1)
        {
            // Passo alla visualizzazione del pianeta
            ret = runPlanet(app);
        }
        if(ret != 1)
        {
            return ret;
        }
    }
    return -1;
}

void Screen_game::CreateRandomPlanets()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand_n(3,6);
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> rand_screenPos_X(100,1200);
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> rand_screenPos_Y(90,600);

    planets.clear();

    //Numero dei pianeti
    total_planets = rand_n(rng);

    for( int i=0; i<total_planets; i++)
    {
        Planet new_planet = Planet(dim_x, dim_y);

        bool collision;
        do
        {
            collision = false;
            //Posizione del pianeta
            new_planet.setPosition(rand_screenPos_X(rng),rand_screenPos_Y(rng));

            for(int j = 0; j< planets.size(); j++)
            {
                if(new_planet.getGlobalBounds().intersects(planets[j].getGlobalBounds()))
                {
                    // Continuo a creare pianeti casuali finchè non vengono creati in spazi liberi
                    collision = true;
                }
            }
            if(new_planet.getGlobalBounds().intersects(spaceShip_galaxy.getGlobalBounds()))
            {
                collision = true;
            }
        }
        while(collision);

        planets.push_back(new_planet);

    }
}
