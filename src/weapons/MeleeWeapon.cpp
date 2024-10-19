//
// Created by Leland Sion on 2024-10-16.
//

#include "MeleeWeapon.h"
#include <iostream>

// Constructor
MeleeWeapon::MeleeWeapon(const std::string& name, int damage, float attackSpeed, float range)
        : Weapon(name, 0, damage), attackSpeed(attackSpeed), range(range) {}

// Fire method (melee attack)
void MeleeWeapon::fire(const sf::Vector2f& direction) {
    // In melee weapons, "fire" would represent an attack in the specified direction
    std::cout << name << " attacks in melee! Damage: " << damage << ", Range: " << range << std::endl;

    // Logic to detect collision with nearby enemies based on range and direction can be added here
}

// Getter for range
float MeleeWeapon::getRange() const {
    return range;
}

// Getter for attack speed
float MeleeWeapon::getAttackSpeed() const {
    return attackSpeed;
}

