#include "Player.hpp"

Player::Player(const char* fileName, float x, float y)
{
    tex.loadFromFile(fileName);
    spr.setTexture(tex);
    spr.setPosition(x, y);

    mtex.loadFromFile("res/missile.png");
    mspr.setTexture(mtex);

    //soundBuffer.loadFromFile("res/missile.ogg");
    //missileSound.setBuffer(soundBuffer);
}

void Player::Cycle(sf::RenderWindow &w, float dt)
{
    float x = spr.getPosition().x;
    float y = spr.getPosition().y;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        x -= speed * dt;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        x += speed * dt;
    }
    //Bounds
    if(x <= 0)
    {
        x = 0;
    }
    if(x+tex.getSize().x >= w.getSize().x)
    {
        x = w.getSize().x-tex.getSize().x;
    }
    spr.setPosition(x, y);

    shootMissile(w, dt);
    w.draw(spr);
}

void Player::shootMissile(sf::RenderWindow &w, float dt)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(missileTimer.getElapsedTime().asMilliseconds() > 300)
        {
            a ammo = {spr.getPosition().x+32-6, spr.getPosition().y};
            missile.push_back(ammo);
            missileSound.play();
            missileTimer.restart();
        }
    }

    for(int i = 0; i < missile.size(); i++)
    {
        missile.at(i).y -= 500 * dt;
        mspr.setPosition(missile.at(i).x, missile.at(i).y);
        w.draw(mspr);
        if(missile.at(i).y <= 0)
        {
            missile.erase(missile.begin()+i);
        }
    }
}
