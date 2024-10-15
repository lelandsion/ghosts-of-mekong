//
// Created by Leland Sion on 2024-10-14.
//

#include "../include/Weapon.h"

// Constructor
Weapon::Weapon(const std::string &weaponName, int maxAmmo, int damage)
        : name(weaponName), ammo(maxAmmo), maxAmmo(maxAmmo), damage(damage), isFiring(false), isReloading(false), fireRateDelay(0.f), reloadDelay(0.f), recoil(0.f) {
    // Initialize sounds, sprite, texture, etc.
    // load textures or sounds here
    // fireSound.loadFromFile("path/to/fireSound.wav");
}

// Copy constructor
Weapon::Weapon(const Weapon &other) {
    copyFrom(other);
}

// Move constructor
Weapon::Weapon(Weapon &&other) noexcept {
moveFrom(std::move(other));
}

// Destructor
Weapon::~Weapon() {
    free();
}

// Copy assignment operator
Weapon& Weapon::operator=(const Weapon &other) {
    if (this != &other) {
        free();  // Free current resources
        copyFrom(other);  // Copy resources from 'other'
    }
    return *this;
}

// Move assignment operator
Weapon& Weapon::operator=(Weapon &&other) noexcept {
if (this != &other) {
free();  // Free current resources
moveFrom(std::move(other));  // Move resources from 'other'
}
return *this;
}

// Helper function to copy resources
void Weapon::copyFrom(const Weapon &other) {
    name = other.name;
    ammo = other.ammo;
    maxAmmo = other.maxAmmo;
    damage = other.damage;
    isFiring = other.isFiring;
    isReloading = other.isReloading;
    fireRateDelay = other.fireRateDelay;
    reloadDelay = other.reloadDelay;
    recoil = other.recoil;
    fireMode = other.fireMode;
    weaponCategory = other.weaponCategory;
    weaponType = other.weaponType;

    // Copy SFML objects
    fireSound = other.fireSound;
    reloadSound = other.reloadSound;
    emptyClipSound = other.emptyClipSound;
    weaponSprite = other.weaponSprite;
    weaponTexture = other.weaponTexture;
    weaponFrame = other.weaponFrame;
}

// Helper function to move resources
void Weapon::moveFrom(Weapon &&other) noexcept {
name = std::move(other.name);
ammo = other.ammo;
maxAmmo = other.maxAmmo;
damage = other.damage;
isFiring = other.isFiring;
isReloading = other.isReloading;
fireRateDelay = other.fireRateDelay;
reloadDelay = other.reloadDelay;
recoil = other.recoil;
fireMode = other.fireMode;
weaponCategory = other.weaponCategory;
weaponType = other.weaponType;

// Move SFML objects
fireSound = std::move(other.fireSound);
reloadSound = std::move(other.reloadSound);
emptyClipSound = std::move(other.emptyClipSound);
weaponSprite = std::move(other.weaponSprite);
weaponTexture = std::move(other.weaponTexture);
weaponFrame = std::move(other.weaponFrame);

// Invalidate the other weapon's state
other.ammo = 0;
other.maxAmmo = 0;
}

// Free resources (if needed)
void Weapon::free() {
    // Any cleanup of dynamically allocated resources goes here.
    // In SFML, most resources are automatically managed (textures, sounds), so no explicit free is required.
}

// Getter for name
std::string Weapon::getName() const {
    return name;
}

// Getter for ammo
int Weapon::getAmmo() const {
    return ammo;
}

// Check if the weapon is out of ammo
bool Weapon::isOutOfAmmo() const {
    return ammo <= 0;
}

// Check if the weapon is reloading
bool Weapon::isReloading() const {
    return isReloading;
}

// Reload the weapon
void Weapon::reload() {
    if (!isReloading && ammo < maxAmmo) {
        // Start the reload process
        isReloading = true;
        reloadSound.play();  // Play the reload sound
        ammo = maxAmmo;  // Reset ammo (or adjust for partial reload if needed)
        // You can add a reload delay mechanism here
    }
}

// Fire the weapon
void Weapon::fire() {
    if (ammo > 0 && !isReloading) {
        // Fire the weapon
        ammo--;
        fireSound.play();  // Play the fire sound
        isFiring = true;    // Mark as firing
    } else if (ammo == 0) {
        // Out of ammo, play empty clip sound
        emptyClipSound.play();
    }
}

