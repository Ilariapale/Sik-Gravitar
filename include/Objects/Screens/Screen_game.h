#include <iostream>
#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <random>
#include "../Entities/Planet.h"
#include "SpaceShip.h"
#include "Terreno.h"
#include "Fuel.h"
#include "Bullet.h"

class Screen_game : public cScreen
{
private:
    //Controllo se è la prima volta che avvio la schermata
    bool first_time_boot = true;
    //Posizione iniziale dell'oggetto
    const int posx = 320;
    const int posy = 240;
    //
    // Stato del gioco 0 = Galaxy ; 1 = Planet
    int game_state = 0;

    //Metto le textures solo la prima volta
    bool loadTextures = true;
    bool loadTexturesInPlanet = true;

    //dimensioni dello schermo
    int dim_x, dim_y;

    //Mi salvo le ultime posizioni sul pianeta
    int lastPosition_x;
    int lastPosition_y = 40;

    //Font dei punteggi
    sf::Font font;

    //Numero pianeti distrutti
    int destroyed_planets = 0;
    int total_planets = 0;

    //Mi segno il momento in cui non ci sono piu pianeti e posso cambiare galassia
    bool change_galaxy = false;

    //Informazione dello stato del serbatoio
    sf::Text serbatoio;
    //Informazione dello score
    sf::Text t_score;
    //Informazione sui punti del pianeta
    sf::Text planet_points;

    //variabile booleana per lo sparo singolo dei proiettili dall'astronave
    bool E = false;

    SpaceShip spaceShip_galaxy;
    std::vector<Planet> planets;
    Planet onPlanet_planet;
    int num_onPlanet_planet;

    sf::Texture livesTexture;
    sf::Texture livesTexture_empty;
    sf::Texture textureShip;

    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;

    sf::Texture textureFuel;

    int runPlanet(sf::RenderWindow &app);
    int runGalaxy(sf::RenderWindow &app);

    public:
        Screen_game(void);

        int getScore();

        void Reset();

        int Run(sf::RenderWindow &app);

        void CreateRandomPlanets();
    };
