#ifndef PLAYER_H
#define PLAYER_H

#include "Spaceship.h"

#include <SFML/System.hpp>

//The player class
class Player
{
    private:

        //Information about the state of the game
        bool & inWaiting;
        SceneNode & sceneGraph;

        //The selected ship
        Spaceship * selectedShip;
        //Is a ship currently selected
        bool shipSelected;

    public:
        explicit Player(bool&, SceneNode&);
        void handleEvent(sf::Event); 
        void handleInput();
        void deselectSpaceship();
};

#endif
