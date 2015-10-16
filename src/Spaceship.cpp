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
    data[Spaceship::Destroyer].hp = 100;
    //Initialize the weapon prototypes
    data[Spaceship::Destroyer].weapons = std::vector<Weapon::WeaponPrototype>(2);
    data[Spaceship::Destroyer].weapons[0].type = Weapon::LaserCannon;
    data[Spaceship::Destroyer].weapons[0].rotation = 90;
    data[Spaceship::Destroyer].weapons[0].position = sf::Vector2f(0, 0);
    data[Spaceship::Destroyer].weapons[1].type = Weapon::LaserCannon;
    data[Spaceship::Destroyer].weapons[1].rotation = -90;
    data[Spaceship::Destroyer].weapons[1].position = sf::Vector2f(0, 0);


    //The hunter class spaceship
    data[Spaceship::Hunter].textureID = Textures::Hunter;
    data[Spaceship::Hunter].deltaV = 200;
    data[Spaceship::Hunter].maxV = 70;
    data[Spaceship::Hunter].hp = 10;
    //Initialize the weapon prototypes
    data[Spaceship::Hunter].weapons = std::vector<Weapon::WeaponPrototype>(2);
    data[Spaceship::Hunter].weapons[0].type = Weapon::LaserBlaster;
    data[Spaceship::Hunter].weapons[0].rotation = 0;
    data[Spaceship::Hunter].weapons[0].position = sf::Vector2f(0, 0);
    data[Spaceship::Hunter].weapons[1] = data[Spaceship::Hunter].weapons[0];

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
    foregroundLayer(foreground), //Initialize the foregorund pointer
    hp(spaceshipData[type].hp), //Initialize the hitpoints
    trajectory(new Trajectory()),
    id(maxId++)
{
    //attach the trajectory in the scene graph
    attachChild(trajectory);

    //Set the category
    category = Command::Spaceship;

    //Center the origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);

    //Get the ID
    setTeam(team);

    //Add the weapons
    for(Weapon::WeaponPrototype prototype : spaceshipData[type].weapons)
    {
        Weapon * weapon = new Weapon(prototype.type, foreground, textureHolder);
        weapon->setRotation(prototype.rotation);
        weapon->setPosition(prototype.position);
        weapon->setTeam(team);
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
    if(velocity.x != 0||velocity.y != 0)
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

//Clear the trajectory
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

//Get the bounding rectangle of this object
sf::FloatRect Spaceship::getGlobalBounds() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::FloatRect rect = getWorldTransform().transformRect(bounds);
    return rect;
}

//Should this spaceship be removed?
bool Spaceship::toRemove()
{
    return hp <= 0;
}

//Deal damage to a spaceship
void Spaceship::doDamage(float damage)
{
    hp -= damage;
}

//Collide with another object
void Spaceship::collide(SceneNode * other)
{
    if(dynamic_cast<Projectile*>(other) && ((Entity*)other)->getTeam() != getTeam())
        doDamage(((Projectile*)other)->getDamage());
}
