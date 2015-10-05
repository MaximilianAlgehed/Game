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
}

void Spaceship::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
