#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class MainMenu : public GameState
{
    public:
        MainMenu(GameStack * stack);
        ~MainMenu();

        virtual void update(sf::Time dt);
        virtual void handleEvent(sf::Event event);
        virtual void draw(sf::RenderWindow* window);
};

#endif
