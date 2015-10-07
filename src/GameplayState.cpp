#include "Spaceship.h"
#include "GameplayState.h"

//Initialize the gameplay
GameplayState::GameplayState(GameStack * stack) : GameState(stack)
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
    //Update the scene
    sceneGraph.update(dt);
}

//Handle persisten input
void GameplayState::handleInput()
{
}

//Handle events
void GameplayState::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            SceneNode * node;
            if(sceneGraph.isClicked(&node, event.mouseButton.x, event.mouseButton.y))
            {
                Command command;
                command.targetCategory = Command::Spaceship;
                command.action = [=] (SceneNode * n, sf::Time dt)
                {
                    if(n != node)
                        return;
                    Entity * m = (Entity *)n;
                    m->setVelocity(m->getVelocity()*(-1.f));
                    m->rotate(180);
                };
                commandQueue.enqueue(command);
            }
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
        sceneGraph.attachChild(node);
        sceneLayers[i] = node;
    }
    //Attach a spaceship to the scene for testing
    Spaceship * ship = new Spaceship(Spaceship::Destroyer, textureHolder);
    ship->setPosition(100, 100);
    ship->rotate(90);
    ship->setVelocity(30, 0);
    sceneLayers[Foreground]->attachChild(ship);
    //Attach a spaceship to the scene for testing
    ship = new Spaceship(Spaceship::Destroyer, textureHolder);
    ship->setPosition(100, 200);
    ship->rotate(90);
    ship->setVelocity(30, 0);
    sceneLayers[Foreground]->attachChild(ship);
}

//Load up resources
void GameplayState::loadResources()
{
    textureHolder.load(Textures::Destroyer, "Media/Destroyer.png");
}
