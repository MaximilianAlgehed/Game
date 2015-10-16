#ifndef PLAYER_H
#define PLAYER_H

#include "Spaceship.h"

#include <SFML/System.hpp>

//The player class
class Player
{
    private:

        //Information about the state of the game
        SceneNode & sceneGraph;

        //The selected ship
        Spaceship * selectedShip;
        //Is a ship currently selected
        bool shipSelected;

    public:
        explicit Player(SceneNode&);
        void handleEvent(sf::Event, unsigned int state); 
        void handleInput();
        void deselectSpaceship();
};

#endif
