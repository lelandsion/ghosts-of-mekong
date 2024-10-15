//
// Created by Leland Sion on 2024-10-14.
//

#ifndef VIETNAM_MARINE_2_WEAPON_H
#define VIETNAM_MARINE_2_WEAPON_H


#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class WeaponCategory;
enum class WeaponType;
enum class FireMode;

class Weapon {
public:
    // Constructors
    Weapon(const std::string &weaponName, int maxAmmo, int damage)
            : name(weaponName), ammo(maxAmmo), maxAmmo(maxAmmo), damage(damage);

    // Copy constructor
    Weapon(const Weapon &other);

    // Move constructor
    Weapon(Weapon &&other) noexcept;

    // Destructor
    ~Weapon();

    // Copy assignment operator
    Weapon& operator=(const Weapon &other);

    // Move assignment operator
    Weapon& operator=(Weapon &&other) noexcept;

    // Getters
    std::string getName() const;
    int getAmmo() const;
    bool isOutOfAmmo() const;
    bool isReloading() const;

    // Actions
    void reload();
    void fire();

private:
    // Visuals and sounds
    std::string name;
    sf::Sound fireSound;       // Sound played when weapon is fired
    sf::Sound reloadSound;     // Sound played when weapon is reloaded
    sf::Sound emptyClipSound;  // Sound played when out of ammo and trying to fire
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;
    sf::IntRect weaponFrame;

    // Damage
    int damage;
    int splashRadius;

    // Status and delay
    bool isFiring;
    bool isReloading;
    float fireRateDelay;
    float reloadDelay;
    float recoil;

    // Ammo
    int ammo;
    int maxAmmoCapacityMagazine; // The amount of ammunition each magazine can hold before reloading
    int maxAmmoCapacityTotal;    // The total amount of ammunition this weapon can hold

    // Bullet stats
    float bulletSpread;
    int bulletType;
    int bulletSpeed;

    // Categorization
    WeaponCategory weaponCategory;
    WeaponType weaponType;
    FireMode fireMode;

};


#endif //VIETNAM_MARINE_2_WEAPON_H
