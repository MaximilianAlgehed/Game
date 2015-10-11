#include <stdio.h>
#include "Spaceship.h"
#include "GameplayState.h"

//Initialize the gameplay
GameplayState::GameplayState(GameStack * stack) : GameState(stack), shipSelected(false), inWaiting(true), player(inWaiting, sceneGraph)
{
    //Load resources
    loadResources(); 
    //Build the scene
    buildScene();
}

//Update
void GameplayState::update(sf::Time dt)
{
    while(!commandQueue.isEmpty())
        sceneGraph.onCommand(commandQueue.pop(), dt);
    if(!inWaiting)
    {
        //Update the scene
        sceneGraph.update(dt);
        //Check the running time of this run
        runningTime += dt;
        if(runningTime >= maxRunningTime)
        {
            inWaiting = true;
            runningTime = sf::Time::Zero;
        }
    }
}

//Handle persisten input
void GameplayState::handleInput()
{
    player.handleInput();
}

//Handle events
void GameplayState::handleEvent(sf::Event event)
{
    player.handleEvent(event);
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space)
        {
            player.deselectSpaceship();
            inWaiting = false;
            Command cmd;
            cmd.targetCategory = Command::Spaceship;
            cmd.action = [] (SceneNode * node, sf::Time dt)
            {
                if(dynamic_cast<Spaceship*>(node))
                    ((Spaceship*)node)->clearTrajectory();
            };
            commandQueue.enqueue(cmd);
        }
    }
}

//Draw the scene
void GameplayState::draw()
{
    //Draw the scene
    window->draw(sceneGraph);
}

//Construct the scene
void GameplayState::buildScene()
{
    //Construct the layers
    for(int i = 0; i < LayerCount; i++)
    {
        SceneNode * node = new SceneNode();
        node->setPosition(0, 0);
        sceneGraph.attachChild(node);
        sceneLayers[i] = node;
    }
    //Attach a spaceship to the scene for testing
    Spaceship * ship = new Spaceship(Spaceship::Destroyer, textureHolder);
    ship->setPosition(500, 100);
    ship->rotate(-90);
    sceneLayers[Foreground]->attachChild(ship);
    //Attach a spaceship to the scene for testing
    ship = new Spaceship(Spaceship::Hunter, textureHolder);
    ship->setPosition(100, 100);
    ship->rotate(90);
    sceneLayers[Foreground]->attachChild(ship);
}

//Load up resources
void GameplayState::loadResources()
{
    textureHolder.load(Textures::Destroyer, "Media/Destroyer.png");
    textureHolder.load(Textures::Hunter, "Media/Hunter.png");
}
