//
// Created by Leland Sion on 2024-10-16.
//

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SniperWeapon.h"
#include "WeaponEnums.h"
#include "Projectile.h"
#include <iostream>

// Constructor
SniperRifle::SniperRifle(const std::string& spritePath, const std::string& projectileSpritePath, const std::string& name, int maxAmmo, float fireDelay, float bulletSpeed, int damage, float precisionRadius, FireMode fireMode)
        : Weapon(spritePath, name, fireDelay, damage, projectileSpritePath, maxAmmo), precisionRadius(precisionRadius) {}


// Fire method for snipers
/*void SniperRifle::fire(const sf::Vector2f& direction) {

    if (ammo > 0) {
        ammo--;

        // Fire one precise projectile
        projectiles.emplace_back(Projectile(weaponSprite.getPosition(), direction, projectileSpeed, damage, ProjectileType::Bullet));
        std::cout << name << " fired a precise shot! Ammo left: " << ammo << std::endl;
    } else {
        std::cout << name << " is out of ammo!" << std::endl;
    }

}*/
