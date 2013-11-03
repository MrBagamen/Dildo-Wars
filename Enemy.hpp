#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Player.hpp"

class Enemy
{
public:
    sf::Sprite spr;
    sf::Texture tex;
    std::vector<a> enemy;
    sf::Clock spawnClock;

    Enemy(const char* fileName);
    void Cycle(sf::RenderWindow &w,float dt, std::vector<a> col, int &score);
private:
    sf::SoundBuffer soundBuffer;
    sf::Sound explodeSound;
};

#endif // ENEMY_HPP
