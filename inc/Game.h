#ifndef GAME_H
#define GAME_H

#include "GameStack.h"

class Game
{
    private:

        GameStack stack;
        const sf::Time timePerFrame = sf::seconds(1.f/60.f);
        sf::RenderWindow window;
        
    public:

        Game();
        ~Game();

        void run();

    private:

        void handleEvents();
        void update(sf::Time dt);
        void draw();
};

#endif
