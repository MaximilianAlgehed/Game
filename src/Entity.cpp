#include "Entity.h"

void Entity::setVelocity(float x, float y)
{
    this->velocity.x = x;
    this->velocity.y = y;
}

void Entity::setVelocity(sf::Vector2f v)
{
    this->velocity = v;
}

sf::Vector2f Entity::getVelocity()
{
    return this->velocity;
}

void Entity::update(sf::Time dt)
{
    move(velocity*dt.asSeconds());
}
