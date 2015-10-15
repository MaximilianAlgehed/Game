#include <stdio.h>
#include "Spaceship.h"
#include "GameplayState.h"
#include "Projectile.h"

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
        //Guide the weapons fire
        targetWeapons();
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
    sceneGraph.removeNodes();
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
    window->setView(view);
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
    Spaceship * ship = new Spaceship(Spaceship::Destroyer, textureHolder, sceneLayers[Foreground], 1);
    ship->setPosition(100, 500);
    ship->rotate(-90);
    sceneLayers[Foreground]->attachChild(ship);
    //Attach another spaceship to the scene for testing
    ship = new Spaceship(Spaceship::Hunter, textureHolder, sceneLayers[Foreground], 2);
    ship->setPosition(700, 500);
    ship->rotate(90);
    sceneLayers[Foreground]->attachChild(ship);
}

//Load up resources
void GameplayState::loadResources()
{
    textureHolder.load(Textures::Destroyer, "Media/Destroyer.png");
    textureHolder.load(Textures::Hunter, "Media/Hunter.png");
    textureHolder.load(Textures::Laser, "Media/Laser.png");
}

//Target the weapons
void GameplayState::targetWeapons()
{
    //Get the spaceships
    collectSpaceships();

    //Send the targeting command to each weapon
    Command command;
    command.targetCategory = Command::Weapon;
    command.action = [=] (SceneNode * node, sf::Time dt)
    {
        if(!dynamic_cast<Weapon*>(node))
            return;

        //Ease of writing
        Weapon * weapon = (Weapon *)node;
        std::vector<Spaceship*> & ships = this->teamTwoSpaceships;

        weapon->setTarget(sf::Vector2f(0, 0));

        //Get the reference to the ships
        if(weapon->getTeam() == 1)
            ships = this->teamTwoSpaceships;
        else if(weapon->getTeam() == 2)
            ships = this->teamOneSpaceships;

        //The best target for the weapon
        Spaceship * bestShip = (Spaceship*)NULL;
        float minDistance = 1000000;
        
        //Find the best target
        for(auto ptr : ships)
        {
            sf::Vector2f difference = ptr->getWorldPosition() - weapon->getWorldPosition();
            if(difference.x*difference.x+difference.y*difference.y < minDistance
               && weapon->isTargetable(ptr->getWorldPosition()))
                bestShip = ptr;
        }

        //We have a ship we want to fire at
        if(bestShip)
            weapon->setTarget(bestShip->getWorldPosition());
    };
    commandQueue.enqueue(command);
}

//Find the spaceships
void GameplayState::collectSpaceships()
{
    //Clear the lists
    teamOneSpaceships.clear();
    teamTwoSpaceships.clear();

    //Collect the spaceships
    Command command;
    command.targetCategory = Command::Spaceship;
    command.action = [=] (SceneNode * node, sf::Time dt)
    {
        if(!dynamic_cast<Spaceship*>(node))
            return;
        Spaceship * ship = (Spaceship *)node;
        if(ship->getTeam() == 1)
            this->teamOneSpaceships.push_back(ship);
        if(ship->getTeam() == 2)
            this->teamTwoSpaceships.push_back(ship);
    };
    commandQueue.enqueue(command);
}
