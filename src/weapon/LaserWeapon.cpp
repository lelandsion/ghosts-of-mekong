//
// Created by Leland Sion on 2024-10-16.
//

#include "LaserWeapon.h"
#include <iostream>

// Constructor
LaserWeapon::LaserWeapon(const std::string& spritePath, const std::string& projectileTexturePath, const std::string& name, int damage,  FireMode fireMode)
        : Weapon(spritePath, name, 0, damage, projectileTexturePath, 50, -1, fireMode) {}


// Fire method for laser weapons (hit scan)
void LaserWeapon::fire(const sf::Vector2f& direction) {
    // Instant hit scan logic (no projectiles)
    std::cout << name << " fired a laser! Instantly hit enemies in a line." << std::endl;
}

