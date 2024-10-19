//
// Created by Leland Sion on 2024-10-16.
//

#ifndef VIETNAM_MARINE_2_LASERWEAPON_H
#define VIETNAM_MARINE_2_LASERWEAPON_H

#include "Weapon.h"

class LaserWeapon : public Weapon {
public:
    LaserWeapon(const std::string& name, int damage);
    void fire(const sf::Vector2f& direction) override;
};


#endif //VIETNAM_MARINE_2_LASERWEAPON_H
