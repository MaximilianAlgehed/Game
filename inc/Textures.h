#ifndef TEXTURES_H
#define TEXTURES_H

#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>

//All different texture types
namespace Textures
{
    enum ID 
    {
        Destroyer,
        Hunter
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif
