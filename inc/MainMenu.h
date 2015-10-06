#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//A game state to represent the main menu
class MainMenu : public GameState
{
    public:
        //Constructor destructor
        MainMenu(GameStack * stack);
        ~MainMenu();

        //Update, handle event, draw the menu
        virtual void update(sf::Time dt);
        virtual void handleEvent(sf::Event event);
        virtual void draw();
        virtual void handleInput();
};

#endif
