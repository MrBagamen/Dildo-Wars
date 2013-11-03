#include "Enemy.hpp"

Enemy::Enemy(const char* fileName)
{
    tex.loadFromFile(fileName);
    spr.setTexture(tex);

    srand(time(nullptr));

    soundBuffer.loadFromFile("res/explode.ogg");
    //explodeSound.setBuffer(soundBuffer);
    //explodeSound.setVolume(5);
}

void Enemy::Cycle(sf::RenderWindow &w, float dt, std::vector<a> col, int &score)
{
    for(int i = 0; i < enemy.size(); i++)
    {
        float tx = enemy.at(i).x + 200 * dt;
        float ty = enemy.at(i).y;
        enemy.at(i).y = ty + 150 * dt;

        //Check collision with missile
        for(int j = 0; j < col.size(); j++)
        {
            if(     tx < col.at(j).x &&
                    tx+tex.getSize().x > col.at(j).x &&
                    ty < col.at(j).y &&
                    ty+tex.getSize().y > col.at(j).y)
            {
                enemy.erase(enemy.begin()+i);
                score++;
                explodeSound.play();
            }
        }
        if(ty > w.getSize().y)
        {
            enemy.erase(enemy.begin()+i);
            score--;
        }

        spr.setPosition(tx, ty);
        w.draw(spr);
    }
    if(spawnClock.getElapsedTime().asMilliseconds() >= 800)
    {
        a en{static_cast<float>(rand() % 650), 50.0f};
        enemy.push_back(en);
        spawnClock.restart();
    }
}
