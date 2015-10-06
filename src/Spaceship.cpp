#include <SFML/System.hpp>
#include "Spaceship.h"
#include "Textures.h"
#include "ResourceHolder.h"

//Get the texture type for the spacship type we have
Textures::ID typeToTexture(Spaceship::Type type)
{
    switch(type)
    {
        case Spaceship::Destroyer:
            return Textures::Destroyer;
    }
}

unsigned int Spaceship::maxId = 0;

//Initializ the spaceship
Spaceship::Spaceship(Type type, ResourceHolder<sf::Texture, Textures::ID>& textureHolder) :
    type(type), //The type, to define the behavior
    sprite(textureHolder.get(typeToTexture(type))) //Initilize the sprite
{
    category = Command::Spaceship;
    //Center the origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
    //Get the ID
    id = maxId++;
}

//Draw the spaceship
void Spaceship::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw the main body sprite
    target.draw(sprite, states);
}

//Update the spaceship
void Spaceship::updateCurrent(sf::Time dt)
{
    //Update the underlying entity
    Entity::updateCurrent(dt);
}
