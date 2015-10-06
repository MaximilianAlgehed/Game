#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>

#include "SceneNode.h"

//Represent an entity in the game world
class Entity : public SceneNode
{
    private:
        //An entity can move
        sf::Vector2f velocity;

    public:
        //Set the velocity
        void setVelocity(sf::Vector2f);
        void setVelocity(float x, float y);

        //Get the velocity
        sf::Vector2f getVelocity();

    protected:
        //Update the entity
        virtual void updateCurrent(sf::Time dt);
};

#endif
