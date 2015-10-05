#include <SFML/System.hpp>
#include "Spaceship.h"
#include "Textures.h"
#include "ResourceHolder.h"

Textures::ID typeToTexture(Spaceship::Type type)
{
    switch(type)
    {
        case Spaceship::Destroyer:
            return Textures::Destroyer;
    }
}

Spaceship::Spaceship(Type type, ResourceHolder<sf::Texture, Textures::ID>& textureHolder) :
    type(type), sprite(textureHolder.get(typeToTexture(type)))
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

void Spaceship::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Spaceship::updateCurrent(sf::Time dt)
{
}
