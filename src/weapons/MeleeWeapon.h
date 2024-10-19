//
// Created by Leland Sion on 2024-10-16.
//

#ifndef VIETNAM_MARINE_2_MELEEWEAPON_H
#define VIETNAM_MARINE_2_MELEEWEAPON_H


#include "Weapon.h"

class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(const std::string& name, int damage, float attackSpeed, float range);

    // Overridden fire method (in melee weapons, this would represent attacking)
    void fire(const sf::Vector2f& direction) override;

    // Getters
    float getRange() const;
    float getAttackSpeed() const;

private:
    float attackSpeed;  // The speed at which the weapon can attack
    float range;        // The range of the melee attack (e.g., longer for swords than for knives)
};


#endif //VIETNAM_MARINE_2_MELEEWEAPON_H
