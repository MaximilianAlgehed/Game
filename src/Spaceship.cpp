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
    sprite(textureHolder.get(typeToTexture(type))), //Initilize the sprite
    deltaV(20),
    maxV(40)
{
    trajectory = new Trajectory();
    attachChild(trajectory);
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

float abs(float f)
{
    if(f > 0)
        return f;
    else return -f;
}

sf::Vector2f normalize(sf::Vector2f v)
{
    float size = sqrt(v.x*v.x+v.y*v.y);
    if(size != 0)
        return v*(1/abs(size));
    else
        return v;
}

//Update the spaceship
void Spaceship::updateCurrent(sf::Time dt)
{
    if(target == sf::Vector2f(0, 0))
        target = getWorldPosition();
    sf::Vector2f velocity = getVelocity();
    velocity += normalize((target-getWorldPosition()))*deltaV*dt.asSeconds();
    if(sqrt(velocity.x*velocity.x+velocity.y*velocity.y) > maxV)
            velocity = normalize(velocity)*maxV;
    setVelocity(velocity);
    setRotation(180-atan2(velocity.x, velocity.y)*180/3.1415);
    //Update the underlying entity
    Entity::updateCurrent(dt);
}

//Check if this ship is clicked
bool Spaceship::clickedCurrent(float x, float y)
{
    sf::Vector2f pos = getWorldPosition();
    return sprite.getGlobalBounds().contains(x-pos.x, y-pos.y);
}

void Spaceship::clearTrajectory()
{
    delete detachChild(*trajectory);
    trajectory = new Trajectory();
    attachChild(trajectory);
}

//Calculate the trajectory from the positon of this spaceship to the global point
void Spaceship::calculateTrajectory(sf::Vector2f globalTarget, sf::Time dt, sf::Time maxTime)
{
    sf::Vector2f target = globalTarget - getWorldPosition();
    this->target = globalTarget;
    sf::Vector2f position(0, 0);
    sf::Vector2f velocity = getVelocity();
    sf::Time accumulatedTime = sf::Time::Zero;
    clearTrajectory(); 
    trajectory->add(getWorldPosition());
    while(accumulatedTime < maxTime)
    {
        velocity += normalize((target-position))*deltaV*dt.asSeconds();
        if(sqrt(velocity.x*velocity.x+velocity.y*velocity.y) > maxV)
            velocity = normalize(velocity)*maxV;
        position += velocity*dt.asSeconds();
        trajectory->add(getWorldPosition()+position);
        accumulatedTime += dt;
    }
}
