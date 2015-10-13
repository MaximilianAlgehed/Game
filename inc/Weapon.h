#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/System.hpp>

#include "SceneNode.h"
#include "Entity.h"
#include "Projectile.h"
#include "Textures.h"

//A Weapon class
class Weapon : public Entity
{
    public:
        //The different types of weapons
        enum Type
        {
            LaserBlaster,
            LaserCannon,
            TypeCount
        };

        //Data for the weapon
        struct WeaponData
        {
            sf::Time maxTimeout;
            sf::Time timeoutSpread;
            float spreadAngle, reachAngle;
            Projectile::Type projectileType;
        };

        //A prototype data struct
        struct WeaponPrototype
        {
            Type type;
            float rotation;
            sf::Vector2f position;
        };

        //Constructor
        explicit Weapon(Type, SceneNode*, TextureHolder&);

        //Is the target position within the angle of reach of this weapon
        bool isTargetable(sf::Vector2f);

        //Set the target for this weapon
        void setTarget(sf::Vector2f);

    private:
        //The type of this weapon
        Type type;
        //The layer on which to attach a projectile
        SceneNode * foregroundLayer;
        //The angle of reach and the angle of spread
        float spreadAngle, reachAngle;
        //Times between fiereing
        sf::Time timeout, maxTimeout;
        //The projectile type
        Projectile::Type projectileType;
        //The target to fire at
        sf::Vector2f target;
        //The resources
        TextureHolder & textures;
        //The spread in the timeout times
        sf::Time timeoutSpread;

    protected:
        //Update the weapon
        virtual void updateCurrent(sf::Time dt);
};

#endif
