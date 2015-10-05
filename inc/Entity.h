#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>

#include "SceneNode.h"

class Entity : SceneNode
{
    private:
        sf::Vector2f velocity;

    public:
        void setVelocity(sf::Vector2f);
        void setVelocity(float x, float y);

        sf::Vector2f getVelocity();
};

#endif
