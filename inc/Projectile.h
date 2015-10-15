#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Textures.h"

class Projectile : public Entity
{
    public:
        enum Type
        {
            Laser,
            LaserCannon,
            TypeCount
        };

        struct ProjectileData
        {
            float damage, speed;
            sf::Time timeout;
            Textures::ID textureID;
            sf::Vector2f scale;
        };

        Projectile(Type, TextureHolder&);
        
        void setDirection(sf::Vector2f);
        virtual bool toRemove();

    private:
        sf::Sprite sprite;
        sf::Time timeout;
        float damage, speed;
        Type type;

    protected:
        virtual void updateCurrent(sf::Time dt);
        virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
