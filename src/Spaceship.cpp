#include <vector>
#include <SFML/System.hpp>

#include "Spaceship.h"
#include "Weapon.h"
#include "Textures.h"
#include "ResourceHolder.h"

//Initialize the spaceship data
std::vector<Spaceship::SpaceshipData> initializeSpaceshipData()
{
    std::vector<Spaceship::SpaceshipData> data = std::vector<Spaceship::SpaceshipData>(Spaceship::TypeCount);

    //The destroyer class spaceship
    data[Spaceship::Destroyer].textureID = Textures::Destroyer;
    data[Spaceship::Destroyer].deltaV = 10;
    data[Spaceship::Destroyer].maxV = 40;

    //The hunter class spaceship
    data[Spaceship::Hunter].textureID = Textures::Hunter;
    data[Spaceship::Hunter].deltaV = 100;
    data[Spaceship::Hunter].maxV = 70;

    return data;
}

//To keep a reference to the spaceship's data
namespace
{
    const std::vector<Spaceship::SpaceshipData> spaceshipData = initializeSpaceshipData();
}

//For initialization
unsigned int Spaceship::maxId = 0;

//Initializ the spaceship
Spaceship::Spaceship(Type type, ResourceHolder<sf::Texture, Textures::ID>& textureHolder, SceneNode * foreground, unsigned int team) :
    type(type), //The type, to define the behavior
    sprite(textureHolder.get(spaceshipData[type].textureID)), //Initilize the sprite
    deltaV(spaceshipData[type].deltaV), //Initialize the deltaV
    maxV(spaceshipData[type].maxV), //Initialize the maxV
    foregroundLayer(foreground)
{
    trajectory = new Trajectory();
    attachChild(trajectory);
    category = Command::Spaceship;
    //Center the origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
    //Get the ID
    id = maxId++;
    setTeam(team);
    Weapon * weapon = new Weapon(Weapon::LaserBlaster, foreground, textureHolder);
    weapon->setTeam(team);
    attachChild(weapon);
    if(type == Destroyer)
    {
        weapon = new Weapon(Weapon::LaserCannon, foreground, textureHolder);
        weapon->setTeam(team);
        weapon->setRotation(90);
        attachChild(weapon);
        weapon = new Weapon(Weapon::LaserCannon, foreground, textureHolder);
        weapon->setTeam(team);
        weapon->setRotation(270);
        attachChild(weapon);
    }
}

//Draw the spaceship
void Spaceship::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw the main body sprite
    target.draw(sprite, states);
}

//Get the absolute of a float
float abs(float f)
{
    if(f > 0)
        return f;
    else return -f;
}

//Normalize a vector
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
    Entity::updateCurrent(dt);
    //If we don't have a target, stay where we are
    if(target == sf::Vector2f(0, 0))
        target = getWorldPosition();
    sf::Vector2f velocity = getVelocity();
    velocity += normalize((target-getWorldPosition()))*deltaV*dt.asSeconds();
    if(sqrt(velocity.x*velocity.x+velocity.y*velocity.y) > maxV)
            velocity = normalize(velocity)*maxV;
    setVelocity(velocity);
    if(velocity.x != 0 || velocity.y != 0)
    {
        float rotation = atan2(velocity.y, velocity.x)*180/3.1415+90;
        while(rotation > 360)
            rotation -= 360;
        setRotation(rotation);
    }
}

//Check if this ship is clicked
bool Spaceship::clickedCurrent(float x, float y)
{
    sf::Vector2f pos = getWorldPosition();
    return sprite.getGlobalBounds().contains(x-pos.x, y-pos.y);
}

void Spaceship::clearTrajectory()
{
    trajectory->clear();
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
    //Integrate the trajectory
    while(accumulatedTime < maxTime)
    {
        sf::Vector2f diff = target-position;
        velocity += normalize((target-position))*deltaV*dt.asSeconds();
        if(sqrt(velocity.x*velocity.x+velocity.y*velocity.y) > maxV)
            velocity = normalize(velocity)*maxV;
        position += velocity*dt.asSeconds();
        trajectory->add(getWorldPosition()+position);
        accumulatedTime += dt;
    }
}
