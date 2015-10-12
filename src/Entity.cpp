#include "Entity.h"

Entity::Entity() :
    team(0)
{
}

//Setter
void Entity::setVelocity(float x, float y)
{
    this->velocity.x = x;
    this->velocity.y = y;
}

//Setter
void Entity::setVelocity(sf::Vector2f v)
{
    this->velocity = v;
}

//Getter
sf::Vector2f Entity::getVelocity()
{
    return this->velocity;
}

//Update the entity
void Entity::updateCurrent(sf::Time dt)
{
    move(velocity*dt.asSeconds());
}

//Set the team of this entity
void Entity::setTeam(unsigned int team)
{
    this->team = team;
}
