//
// Created by Leland Sion on 2024-10-16.
//

#ifndef VIETNAM_MARINE_2_SNIPERWEAPON_H
#define VIETNAM_MARINE_2_SNIPERWEAPON_H

#include "Weapon.h"

class SniperRifle : public Weapon {
public:
    SniperRifle(const std::string& name, int maxAmmo, int damage, float precisionRadius);
    void fire(const sf::Vector2f& direction) override;

private:
    float precisionRadius;  // The accuracy radius around the target
};

#endif // VIETNAM_MARINE_2_SNIPERWEAPON_H

