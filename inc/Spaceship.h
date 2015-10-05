#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entity.h"
#include "ResourceHolder.h"
#include "Textures.h"

class Spaceship : public Entity
{
    public:

        enum Type {Destroyer};

    private:
    
        Type type;
        sf::Sprite sprite;

    public:

        explicit Spaceship(Type, ResourceHolder<sf::Texture, Textures::ID>&);

    protected:

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
