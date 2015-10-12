#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/System.hpp>

#include "SceneNode.h"
#include "Projectile.h"

class Weapon : public SceneNode
{
    public:
        //The different types of weapons
        enum Type
        {
            LaserBlaster,
            TypeCount
        };

        //Data for the weapon
        struct WeaponData
        {
            sf::Time maxTimeout;
            float spreadAngle, reachAngle;
            Projectile::Type projectileType;
        };

        //Constructor
        explicit Weapon(Type, SceneNode*);

        //If possible, fire the wepon at a global position
        void fire(sf::Vector2f);

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

    protected:
        //Update the weapon
        virtual void updateCurrent(sf::Time dt);
};

#endif
