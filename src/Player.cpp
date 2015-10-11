#include "Player.h"

//Initialize the player
Player::Player(bool & inWaiting, SceneNode & sceneGraph) :
    inWaiting(inWaiting),
    sceneGraph(sceneGraph),
    shipSelected(false)
{
}

//Deselect the spaceship
void Player::deselectSpaceship()
{
    shipSelected = false;
}

//Handle events from the window
void Player::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        //Deselect the ship
        if(event.key.code == sf::Keyboard::Escape)
        {
            shipSelected = false;
            if(selectedShip)
                selectedShip->clearTrajectory();
        }
    }
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            //Select a ship for moving around
            if(!shipSelected && inWaiting)
            {
                SceneNode * node = NULL;
                if(sceneGraph.isClicked(&node, event.mouseButton.x, event.mouseButton.y))
                {
                    if(dynamic_cast<Spaceship*>(node))
                    {
                        selectedShip = (Spaceship*)node;
                        shipSelected = true;
                    }
                }
            }
            else if(shipSelected && inWaiting)
                selectedShip->calculateTrajectory(
                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y),
                        sf::seconds(0.1),
                        sf::seconds(3)
                );
        }
    }
}

void Player::handleInput()
{
}
