#ifndef WORLD_H
#define WORLD_H

#include "Textures.h"
#include "GameState.h"
#include "SceneNode.h"
#include "Command.h"
#include "Spaceship.h"
#include "Player.h"
#include "Weapon.h"

#include <array>

class World
{
    public:
        explicit World(TextureHolder&);

        void update(sf::Time dt);
        void handleEvent(sf::Event event);
        void handleInput();

        //The different layers in the scene
        enum SceneLayer
        {
            Background,
            Foreground,
            LayerCount
        };

        //The possible states
        enum State
        {
            P1Planning,
            P2Planning,
            Resolution,
            StateCount
        };

    private:
        void checkCollisions();

        std::vector<Spaceship*> teamOneSpaceships, teamTwoSpaceships;

        //The scene graph
        SceneNode sceneGraph;
        
        //The state of the gameplay
        unsigned int state = P1Planning;

};

#endif
