#include "GameplayState.h"
#include "MainMenu.h"
#include "Game.h"
#include <SFML/System.hpp>

//Initialize the game application
Game::Game() : window(sf::VideoMode(500, 500), "Game"), stack(&window)
{
}

//Possible destructor, if it is needed
Game::~Game()
{
}

//Run the game
void Game::run()
{
    //Push the spaslcreen to the stack
    stack.push(new GameplayState(&stack));
    //Initialization for the fixed timestep
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    //if the stack is empty we terminate the game loop
    while(!stack.isExiting())
    {
        //Handle events like close etc
        handleEvents();
        //Fixed timestep
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame);
        }
        //Draw the game
        draw();
    }
}

//Handle events
void Game::handleEvents()
{
    //Handle static input on the stack
    stack.handleInput();
    sf::Event event;
    //Handle all events
    while(window.pollEvent(event))
    {
        //Close the game
        if(event.type == sf::Event::Closed)
            stack.exit();
        //Handle the events in the stack
        else
            stack.handleEvent(event);
    }
}

//Update the game
void Game::update(sf::Time dt)
{
    //If we are exiting there is no point to update
    if(!stack.isExiting())
        stack.update(dt);
}

//Draw the game
void Game::draw()
{
    window.clear();
    if(!stack.isExiting())
        stack.draw();
    window.display();
}
