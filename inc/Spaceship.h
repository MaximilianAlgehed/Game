#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entity.h"
#include "ResourceHolder.h"
#include "Textures.h"
#include "Trajectory.h"

//Represent a spaceship entity
class Spaceship : public Entity
{
    public:

        //Different types of spaceships
        enum Type {
            Destroyer,
            Hunter,
            TypeCount
        };

        //Spaceship data
        struct SpaceshipData
        {
            Textures::ID textureID;
            float deltaV, maxV;
        };

    //Bookeeping variables for the spacship
    //that are shared among all spaceship
    private:
    
        //The type and sprite for this spaceship
        Type type;
        sf::Sprite sprite;
        //The id of this spaceship
        unsigned int id;
        //The id of the next spaceship
        static unsigned int maxId;
        //The target this spaceship is going for
        sf::Vector2f target;
        //The trajectory of this spaceship
        Trajectory * trajectory;
        //The scene node on which to attach projectiles
        SceneNode * foregroundLayer;

    //Stat's that all spaceship have in common
    protected:

        //The dv/dt of this spaceship
        float deltaV;
        //the maximum velocity of this spaceship
        float maxV;

    public:

        //Only possible constructor
        explicit Spaceship(Type, ResourceHolder<sf::Texture, Textures::ID>&, SceneNode*);
        //Calculate trajectory from the position of this spaceship to the target, globally
        void calculateTrajectory(sf::Vector2f target, sf::Time dt, sf::Time maxTime);
        //Stop displaying the trajectory
        void clearTrajectory(); 

    //SceneNode methods
    protected:

        //Draw the spaceship
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
        //Update the spaceship
        virtual void updateCurrent(sf::Time dt);
        //Is this object clicked
        virtual bool clickedCurrent(float x, float y);
};

#endif
