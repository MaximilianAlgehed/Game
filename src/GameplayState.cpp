#include <stdio.h>
#include "Spaceship.h"
#include "GameplayState.h"
#include "Projectile.h"
#include "TextNodeTimed.h"

//Initialize the gameplay
GameplayState::GameplayState(GameStack * stack) : GameState(stack), player(sceneGraph), playerText(NULL), state(-1)
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
    if(state == Resolution)
    {
        //Check collisions
        checkCollisions();
        //Guide the weapons fire
        targetWeapons();
        //Update the scene
        sceneGraph.update(dt);
        //Check the running time of this run
        runningTime += dt;
        if(runningTime >= maxRunningTime)
        {
            nextState();
            runningTime = sf::Time::Zero;
        }
    }
    HUDNode.update(dt);
    HUDNode.removeNodes();
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
    player.handleEvent(event, state);
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space)
        {
            player.deselectSpaceship();
            if(state != Resolution)
            {
                nextState();
            }
            clearTrajectories();
        }
    }
    //Resize the window
    else if(event.type == sf::Event::Resized)
        view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
}

//Create the player text
void GameplayState::nextState()
{
    (++state) %= StateCount;
    if(state == Resolution)
        return;
    std::string text = state == P1Planning ? "Player 1" : "Player 2";
    sf::Font font;
    font.loadFromFile("Media/arial.ttf");
    if(playerText)
        playerText->destroy();
    playerText = new TextNodeTimed(text, font, 30, sf::Color::Red, sf::seconds(1));
    playerText->setPosition(100, 100);
    HUDNode.attachChild(playerText);
}

//Clear trajectories of all spaceships in the scene
void GameplayState::clearTrajectories()
{
    Command cmd;
    cmd.targetCategory = Command::Spaceship;
    cmd.action = [] (SceneNode * node, sf::Time dt)
    {
        if(dynamic_cast<Spaceship*>(node))
            ((Spaceship*)node)->clearTrajectory();
    };
    commandQueue.enqueue(cmd);
}

//Draw the scene
void GameplayState::draw()
{
    //Draw the scene
    window->setView(view);
    window->draw(sceneGraph);
    window->draw(HUDNode);
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
    ship->setPosition(100, 200);
    ship->rotate(90);
    sceneLayers[Foreground]->attachChild(ship);
    //Attach another spaceship to the scene for testing
    ship = new Spaceship(Spaceship::Hunter, textureHolder, sceneLayers[Foreground], 2);
    ship->setPosition(500, 500);
    ship->rotate(-90);
    sceneLayers[Foreground]->attachChild(ship);
    //Attach yet another spaceship to the scene
    ship = new Spaceship(Spaceship::Hunter, textureHolder, sceneLayers[Foreground], 2);
    ship->setPosition(700, 200);
    ship->rotate(90);
    sceneLayers[Foreground]->attachChild(ship);
    nextState();
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

//Check collisions between scene nodes
void GameplayState::checkCollisions()
{
    std::set<std::pair<SceneNode*, SceneNode*>> set;
    sceneGraph.collectCollisions(&sceneGraph, set);

    for(auto pair : set)
    {
        pair.first->collide(pair.second);
        pair.second->collide(pair.first);
    }
}
