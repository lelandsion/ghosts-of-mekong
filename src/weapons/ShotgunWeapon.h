//
// Created by Leland Sion on 2024-10-16.
//

#ifndef VIETNAM_MARINE_2_SHOTGUNWEAPON_H
#define VIETNAM_MARINE_2_SHOTGUNWEAPON_H

#include "Weapon.h"
#include "<SFML/Graphics.hpp>"

class Shotgun : public Weapon {
public:
    Shotgun(const std::string& name, int maxAmmo, int damage, int spread);
    void fire(const sf::Vector2f& direction) override;

private:
    sf::fireSprite;      // Sprite of bullets if the weapon does not have projectiles

    bool hasProjectile;  // Whether the weapon uses the projectile class or it uses a damage distance

    float range;         // Distance from the end of the barrel that inflicts damage
    float spread;        // Spread angle for the shotgun
};

#endif // VIETNAM_MARINE_2_SHOTGUNWEAPON_H

