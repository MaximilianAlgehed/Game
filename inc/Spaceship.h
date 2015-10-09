#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entity.h"
#include "ResourceHolder.h"
#include "Textures.h"

//Represent a spaceship entity
class Spaceship : public Entity
{
    public:

        //Different types of spaceships
        enum Type {Destroyer};

    private:
    
        //The type and sprite for this spaceship
        Type type;
        sf::Sprite sprite;
        //The id of this spaceship
        unsigned int id;
        //The id of the next spaceship
        static unsigned int maxId;
        //The dv/dt of this spaceship
        float deltaV;

    public:

        //Only possible constructor
        explicit Spaceship(Type, ResourceHolder<sf::Texture, Textures::ID>&);

    protected:

        //Draw the spaceship
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
        //Update the spaceship
        virtual void updateCurrent(sf::Time dt);
        //Is this object clicked
        virtual bool clickedCurrent(float x, float y);

};

#endif
