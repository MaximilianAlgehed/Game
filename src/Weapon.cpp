#include <random>

#include "Weapon.h"

extern float abs(float);

//Initialize the weapon data
std::vector<Weapon::WeaponData> initializeWeaponData()
{
    std::vector<Weapon::WeaponData> data = std::vector<Weapon::WeaponData>(Weapon::TypeCount);

    //The blaster class weapon
    data[Weapon::LaserBlaster].projectileType = Projectile::Laser;
    data[Weapon::LaserBlaster].spreadAngle = 10;
    data[Weapon::LaserBlaster].reachAngle = 45;
    data[Weapon::LaserBlaster].maxTimeout = sf::seconds(0.2);
    data[Weapon::LaserBlaster].timeoutSpread = sf::seconds(0.05);

    //The cannon class weapon
    data[Weapon::LaserCannon].projectileType = Projectile::LaserCannon;
    data[Weapon::LaserCannon].spreadAngle = 15;
    data[Weapon::LaserCannon].reachAngle = 50;
    data[Weapon::LaserCannon].maxTimeout = sf::seconds(0.7);
    data[Weapon::LaserCannon].timeoutSpread = sf::seconds(0);

    return data;
}

//To keep a reference to the weapon's data
namespace
{
    const std::vector<Weapon::WeaponData> weaponData = initializeWeaponData();
}

//Initialize the weapon
Weapon::Weapon(Type type, SceneNode * foregroundLayer, TextureHolder& textures) :
    type(type),
    foregroundLayer(foregroundLayer),
    spreadAngle(weaponData[type].spreadAngle),
    reachAngle(weaponData[type].reachAngle),
    projectileType(weaponData[type].projectileType),
    maxTimeout(weaponData[type].maxTimeout),
    timeout(sf::Time::Zero),
    textures(textures),
    timeoutSpread(weaponData[type].timeoutSpread)
{
    category = Command::Weapon;
}

//Update the weapon
void Weapon::updateCurrent(sf::Time dt)
{
    Entity::updateCurrent(dt);
    if(dt > timeout)
        timeout = sf::Time::Zero;
    else
        timeout -= dt;
    if(timeout <= sf::Time::Zero)
    {
        if(target != sf::Vector2f(0, 0))
        {
            timeout = maxTimeout;
            timeout += sf::seconds((float(rand())/float(RAND_MAX))*timeoutSpread.asSeconds())-sf::seconds(timeoutSpread.asSeconds()*0.5);
            Projectile * projectile = new Projectile(projectileType, textures);
            projectile->setPosition(getWorldPosition());
            projectile->setRotation(getWorldRotation());
            projectile->setTeam(getTeam());
            sf::Vector2f direction = target-getWorldPosition();
            sf::Transform transform = sf::Transform::Identity;
            transform.rotate(float(rand())/float(RAND_MAX)*spreadAngle-spreadAngle/2);
            direction = transform*direction;
            projectile->setDirection(direction);
            foregroundLayer->attachChild(projectile);
        }
    }
}

//Set the target
void Weapon::setTarget(sf::Vector2f target)
{
    this->target = target;
}

//Is a position targetable?
bool Weapon::isTargetable(sf::Vector2f target)
{
    float worldRotation = getWorldRotation();
    while(worldRotation > 360)
        worldRotation -= 360;
    sf::Vector2f direction = target - getWorldPosition();
    float distance = sqrt(direction.x*direction.x+direction.y*direction.y);
    if(distance > Projectile::getMaxDistance(projectileType))
        return false;
    float angle = atan2(direction.y, direction.x)*180/3.1415+90;
    float diff = abs(angle-worldRotation);
    if(diff > 180)
        diff = 360-diff;
    return diff <= reachAngle;
}
