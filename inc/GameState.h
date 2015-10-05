#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStack.h"

class GameState
{
    protected:
        GameStack * stack;

    public:
        GameState(GameStack * stack);
        ~GameState();

        virtual void update(sf::Time dt) = 0;
        virtual void handleEvent(sf::Event event) = 0;
        virtual void draw(sf::RenderWindow* window) = 0;
};

#endif
