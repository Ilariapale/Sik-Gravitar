#define GAME_H
#include <SFML/Graphics.hpp>

class Game : public sf::Drawable
{
public:
    Game();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
