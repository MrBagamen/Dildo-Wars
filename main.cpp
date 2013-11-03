#include <iostream>
#include <GL/gl.h>
#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

int main()
{
    sf::VideoMode videoMode(600, 768);
    sf::RenderWindow window(videoMode, "Dildo Wars -- Press F to display framerate, V to disable VSYNC", sf::Style::Close);
    sf::Time deltaTime;
    sf::Clock deltaClock;

    //Background
    sf::Texture bgTex;
    bgTex.loadFromFile("res/spacebg.png");
    sf::Sprite bgSpr;
    bgSpr.setTexture(bgTex);

    //Instance player
    Player player("res/spaceship.png", 250, 670);

    //Enemy
    Enemy enemy("res/dildo.png");

    //Score
    int score = 0;
    sf::Text scoreText;
    sf::Font scoreFont;
    scoreFont.loadFromFile("res/Titania.ttf");
    scoreText.setFont(scoreFont);
    scoreText.setString("Score: 0");
    scoreText.setPosition(12, 12);

    //Show FPS
    bool showfps = false;
    sf::Text showFPSText;
    showFPSText.setFont(scoreFont);
    showFPSText.setPosition(12, 44);
    int frames = 0;
    sf::Clock frameClock;

    // vsync
    bool vsync = true;
    window.setVerticalSyncEnabled(vsync);

    //BG Music
    sf::Music bgMusic;
    bgMusic.openFromFile("res/af.ogg");
    bgMusic.setVolume(50);
    bgMusic.play();

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::F)
                {
                    if(showfps == true)
                        showfps = false;
                    else if(showfps == false)
                        showfps = true;
                }
                if(event.key.code == sf::Keyboard::V)
                {
                    if(vsync == true)
                    {
                        window.setVerticalSyncEnabled(false);
                        vsync = false;
                    }
                    else if(vsync == false)
                    {
                        window.setVerticalSyncEnabled(true);
                        vsync = true;
                    }
                }
                break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        window.clear(sf::Color(100, 50, 100, 255));
        window.draw(bgSpr);//draw background

        player.Cycle(window, deltaTime.asSeconds());
        enemy.Cycle(window, deltaTime.asSeconds(), player.missile, score);

        //Draw score
        char scoreToText[20];
        sprintf(scoreToText, "Score: %d", score);
        scoreText.setString(scoreToText);
        window.draw(scoreText);

        if(showfps)
        {
            window.draw(showFPSText);
            if(frameClock.getElapsedTime().asMilliseconds() >= 1000)
            {
                char fpsToText[20];
                sprintf(fpsToText, "FPS: %d", frames);
                showFPSText.setString(fpsToText);

                frameClock.restart();
                frames = -1;
            }
            frames++;
        }

        window.display();
        deltaTime = deltaClock.restart();
    }

    return 0;
}

