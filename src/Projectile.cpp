#include "Projectile.h"

extern float abs(float);
extern sf::Vector2f normalize(sf::Vector2f);

//Initialize the projectile data
std::vector<Projectile::ProjectileData> initializeProjectileData()
{
    std::vector<Projectile::ProjectileData> data = std::vector<Projectile::ProjectileData>(Projectile::TypeCount);

    //The laser projectile
    data[Projectile::Laser].textureID = Textures::Laser;
    data[Projectile::Laser].speed = 500;
    data[Projectile::Laser].damage = 1;
    data[Projectile::Laser].timeout = sf::seconds(10);
    data[Projectile::Laser].scale = sf::Vector2f(0.1, 0.1);

    //The laser cannon
    data[Projectile::LaserCannon].textureID = Textures::Laser;
    data[Projectile::LaserCannon].speed = 250;
    data[Projectile::LaserCannon].damage = 10;
    data[Projectile::LaserCannon].timeout = sf::seconds(10);
    data[Projectile::LaserCannon].scale = sf::Vector2f(0.3, 0.3);

    return data;
}

//To keep a reference to the spaceship's data
namespace
{
    const std::vector<Projectile::ProjectileData> projectileData = initializeProjectileData();
}

//Initialzie a projectile
Projectile::Projectile(Type type, TextureHolder& textureHolder) :
    type(type), //The type
    sprite(textureHolder.get(projectileData[type].textureID)), //the sprite
    timeout(projectileData[type].timeout), //The timeout 
    speed(projectileData[type].speed), //The speed
    damage(projectileData[type].damage) //the damage
{
    setScale(projectileData[type].scale);
}

//Update the projectile
void Projectile::updateCurrent(sf::Time dt)
{
    Entity::updateCurrent(dt);
    if(timeout > dt)
        timeout -= dt;
    else
        timeout = sf::Time::Zero;
}

//Set the direction pof a projectile
void Projectile::setDirection(sf::Vector2f dir)
{
    setVelocity(normalize(dir)*speed);
    setRotation(90-atan2(getVelocity().x, getVelocity().y)*180/3.1415);
}

//Draw the projectile
void Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
