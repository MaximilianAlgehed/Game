#ifndef PLAYER_H
#define PLAYER_H

#include "Spaceship.h"

#include <SFML/System.hpp>

class Player
{
    private:
        bool & inWaiting;
        SceneNode & sceneGraph;
        Spaceship * selectedShip;
        bool shipSelected;
    public:
        explicit Player(bool&, SceneNode&);
        void handleEvent(sf::Event); 
        void handleInput();
};

#endif
