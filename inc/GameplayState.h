#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "Textures.h"
#include "GameState.h"
#include "SceneNode.h"
#include "Command.h"
#include "Spaceship.h"
#include "Player.h"
#include "Weapon.h"

#include <array>

//A GameState for the stack
//that represents gameplay
class GameplayState : public GameState
{
    private:

        //The different layers in the scene
        enum SceneLayer
        {
            Background,
            Foreground,
            LayerCount
        };

        //The root node for the scene graph
        SceneNode sceneGraph;
        //Pointers for the layers, which lets us add objects to the
        //right layer
        std::array<SceneNode*, LayerCount> sceneLayers;
        //Resource holder for texures
        TextureHolder textureHolder;

        //The state
        bool inWaiting;
        //The time to play a scene
        sf::Time runningTime;
        const sf::Time maxRunningTime = sf::seconds(3);

        //The player
        Player player;

        //The selected ship for moving
        Spaceship * selectedShip;
        //Is there a selected ship?
        bool shipSelected;

        //Initialize the resources
        void loadResources();
        //Construct the scene
        void buildScene();
        //Internal command queue
        CommandQueue commandQueue;

        //the spaceships that are within the 
        void collectSpaceships();
        void targetWeapons();

    public:
        //Initialize the state
        GameplayState(GameStack * stack);

        //Update, handle events, and draw the world
        virtual void update(sf::Time dt);
        virtual void handleEvent(sf::Event event);
        virtual void draw();
        virtual void handleInput();

        void checkCollisions();

        std::vector<Spaceship*> teamOneSpaceships, teamTwoSpaceships;
};

#endif
