//
// Created by Leland Sion on 2024-10-16.
//

#include "ShotgunWeapon.h"
#include <iostream>

// Constructor
Shotgun::Shotgun(const std::string& name, int maxAmmo, int damage, int spread)
        : Weapon(name, maxAmmo, damage), spread(spread) {}

// Fire method with spread
void Shotgun::fire(const sf::Vector2f& direction) {
    if (ammo > 0) {
        ammo--;

        // Generate multiple projectiles in a spread pattern
        for (int i = -spread / 2; i <= spread / 2; i += 5) {
            sf::Vector2f spreadDirection = direction + sf::Vector2f(i, 0); // Adjust direction for spread
            projectiles.emplace_back(Projectile(weaponSprite.getPosition(), spreadDirection, projectileSpeed, damage, ProjectileType::Bullet));
        }

        std::cout << name << " fired! Ammo left: " << ammo << std::endl;
    } else {
        std::cout << name << " is out of ammo!" << std::endl;
    }
}
