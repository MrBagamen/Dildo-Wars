#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

struct a
{
    float x;
    float y;
};

class Player
{
public:
    static int score;
    sf::Texture tex, mtex;
    sf::Sprite spr, mspr;
    float speed = 300;
    std::vector<a> missile;

    Player(const char* fileName, float x, float y);
    void Cycle(sf::RenderWindow &w, float dt);

private:
    sf::SoundBuffer soundBuffer;
    sf::Sound missileSound;
    sf::Clock missileTimer;
    void shootMissile(sf::RenderWindow &w, float dt);
};

#endif // PLAYER_HPP
