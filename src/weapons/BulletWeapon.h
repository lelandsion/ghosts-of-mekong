//
// Created by Leland Sion on 2024-10-15.
//
#ifndef VIETNAM_MARINE_2_BULLETWEAPON_H
#define VIETNAM_MARINE_2_BULLETWEAPON_H

#ifndef VIETNAM_MARINE_2_BULLETWEAPON_H
#define VIETNAM_MARINE_2_BULLETWEAPON_H

#include "Weapon.h"
#include <SFML/Graphics.hpp>  // For visual components like bullet sprites

class BulletWeapon : public Weapon {
public:
    // Constructor
    BulletWeapon(const std::string &weaponName, int maxAmmo, int damage, float bulletSpeed, float bulletSpread);

    // Copy and move constructors
    BulletWeapon(const BulletWeapon &other);
    BulletWeapon(BulletWeapon &&other) noexcept;

    // Destructor
    ~BulletWeapon();

    // Assignment operators
    BulletWeapon& operator=(const BulletWeapon &other);
    BulletWeapon& operator=(BulletWeapon &&other) noexcept;

    // Fire the weapon (handles single-shot, burst, and automatic firing)
    void fire() override;

    // Update the weapon (handles firing delay, reload delay, etc.)
    void update(float deltaTime) override;

private:
    float bulletSpeed;    // Speed of the fired bullets
    float bulletSpread;   // Random spread angle for firing inaccuracy

    int burstFireCount;   // Number of bullets fired in a burst
    bool isAutomatic;     // True if the weapon is automatic

    // Fire a single bullet (used internally for firing logic)
    void fireBullet();

    // Helper methods to handle specific firing modes
    void handleBurstFire();
    void handleAutomaticFire();


};

#endif //VIETNAM_MARINE_2_BULLETWEAPON_H


#endif //VIETNAM_MARINE_2_BULLETWEAPON_H
