#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "Textures.h"
#include "GameState.h"
#include "SceneNode.h"
#include "Command.h"
#include "Spaceship.h"
#include "Player.h"
#include "Weapon.h"
#include "TextNodeTimed.h"

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

        //The possible states
        enum State
        {
            P1Planning,
            P2Planning,
            Resolution,
            StateCount
        };

        //The state of the gameplay
        unsigned int state = P1Planning;

        //The root node for the scene graph
        SceneNode sceneGraph;
        SceneNode HUDNode;
        TextNodeTimed * playerText;
        //Pointers for the layers, which lets us add objects to the
        //right layer
        std::array<SceneNode*, LayerCount> sceneLayers;
        //Resource holder for texures
        TextureHolder textureHolder;

        //The time to play a scene
        sf::Time runningTime;
        const sf::Time maxRunningTime = sf::seconds(3);

        //The player
        Player player;

        //Initialize the resources
        void loadResources();
        //Construct the scene
        void buildScene();
        //Internal command queue
        CommandQueue commandQueue;

        //Handle spaceships
        void collectSpaceships();
        void targetWeapons();

        //clear the trajectories of all spaceship
        void clearTrajectories();

        //Create the text in the middle of the screen
        void nextState();

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
