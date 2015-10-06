#ifndef GAME_H
#define GAME_H

#include "GameStack.h"

//A game class to represent the whole application
class Game
{
    private:

        //The game stack
        GameStack stack;
        const sf::Time timePerFrame = sf::seconds(1.f/60.f);
        sf::RenderWindow window;
        
    public:

        //Constructor destructor
        Game();
        ~Game();

        //Run the game loop
        void run();

    private:

        //Functions for the three game loop things
        void handleEvents();
        void update(sf::Time dt);
        void draw();
};

#endif
