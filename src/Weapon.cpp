#include "Weapon.h"

//Initialize the weapon data
std::vector<Weapon::WeaponData> initializeWeaponData()
{
    std::vector<Weapon::WeaponData> data = std::vector<Weapon::WeaponData>(Weapon::TypeCount);

    //The destroyer class weapon
    data[Weapon::LaserBlaster].projectileType = Projectile::Laser;
    data[Weapon::LaserBlaster].spreadAngle = 10;
    data[Weapon::LaserBlaster].reachAngle = 30;
    data[Weapon::LaserBlaster].maxTimeout = sf::seconds(0.2);

    return data;
}

//To keep a reference to the weapon's data
namespace
{
    const std::vector<Weapon::WeaponData> weaponData = initializeWeaponData();
}

//Initialize the weapon
Weapon::Weapon(Type type, SceneNode * foregroundLayer) :
    type(type),
    foregroundLayer(foregroundLayer),
    spreadAngle(weaponData[type].spreadAngle),
    reachAngle(weaponData[type].reachAngle),
    projectileType(weaponData[type].projectileType),
    maxTimeout(weaponData[type].maxTimeout),
    timeout(sf::Time::Zero)
{
}

//Update the weapon
void Weapon::updateCurrent(sf::Time dt)
{
    timeout -= dt;
}

//Fire the weapon
void Weapon::fire(sf::Vector2f target)
{
    if(timeout > sf::Time::Zero)
        return;
    sf::Vector2f position = getWorldPosition();
}
