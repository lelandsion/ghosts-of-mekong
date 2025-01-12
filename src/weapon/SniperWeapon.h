//
// Created by Leland Sion on 2024-10-16.
//

#ifndef VIETNAM_MARINE_2_SNIPERWEAPON_H
#define VIETNAM_MARINE_2_SNIPERWEAPON_H

#include "Weapon.h"

class SniperRifle : public Weapon {
public:
    SniperRifle(const std::string& spritePath, const std::string& projectileSpritePath, const std::string& name, int maxAmmo, float fireDelay, float bulletSpeed, int damage, float precisionRadius, FireMode fireMode);
    void fire(const sf::Vector2f& direction);

private:
    float precisionRadius;  // The accuracy radius around the target
};

#endif // VIETNAM_MARINE_2_SNIPERWEAPON_H

