#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStack.h"

//The state of the game
class GameState
{
    protected:
        //Reference to the stack
        GameStack * stack;
        sf::RenderWindow * window;
        sf::View view;

    public:
        //Constructor destructor pair
        GameState(GameStack * stack);
        ~GameState();

        virtual void update(sf::Time dt) = 0;
        virtual void handleEvent(sf::Event event) = 0;
        virtual void draw() = 0;
        virtual void handleInput() = 0;
};

#endif
