//
// Created by Leland Sion on 2024-10-16.
//

#include "SniperWeapon.h"
#include <iostream>

// Constructor
SniperRifle::SniperRifle(const std::string& name, int maxAmmo, int damage, float precisionRadius)
        : Weapon(name, maxAmmo, damage), precisionRadius(precisionRadius) {}

// Fire method for snipers
void SniperRifle::fire(const sf::Vector2f& direction) {
    if (ammo > 0) {
        ammo--;

        // Fire one precise projectile
        projectiles.emplace_back(Projectile(weaponSprite.getPosition(), direction, projectileSpeed, damage, ProjectileType::Bullet));
        std::cout << name << " fired a precise shot! Ammo left: " << ammo << std::endl;
    } else {
        std::cout << name << " is out of ammo!" << std::endl;
    }
}
