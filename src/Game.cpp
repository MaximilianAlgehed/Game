#include "MainMenu.h"
#include "Game.h"
#include <SFML/System.hpp>

Game::Game() : window(sf::VideoMode(500, 500), "Game"), stack(&window)
{
}

Game::~Game()
{
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    stack.push(new MainMenu(&stack));
    while(!stack.isExiting())
    {
        handleEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame.asSeconds());
        }
        draw();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            stack.exit();
        else
            stack.handleEvent(event);
    }
}

void Game::update(float dt)
{
    if(!stack.isExiting())
        stack.update(dt);
}

void Game::draw()
{
    window.clear();
    if(!stack.isExiting())
        stack.draw();
    window.display();
}
