//
// Created by Leland Sion on 2024-10-14.
//
// Class: Weapon
// Description: Represents a weapon in the Vietnam Marine game. The Weapon class defines
// the attributes and behaviors associated with different weapon types, including damage,
// range, firing rate, and ammunition management. It serves as a base for various weapon
// implementations such as firearms, melee weapons, and explosives.
//
// Usage:
// Weapon weapon;
// weapon.setDamage(50);
// weapon.fire(); // Call this method to simulate firing the weapon
//
// Notes:
// - This class may be extended for specific weapon types, each with unique behaviors
//   and attributes (e.g., Shotgun, Sniper, Grenade).
// - Consider implementing a system for weapon upgrades or modifications to enhance
//   gameplay dynamics.

#ifndef VIETNAM_MARINE_2_WEAPON_H
#define VIETNAM_MARINE_2_WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

enum class WeaponCategory;
enum class WeaponType;
enum class FireMode;

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, int speed, int damage);

    // Update the projectile's position based on its speed and direction
    void update(float deltaTime);

    // Check if the projectile has collided with something
    bool checkCollision(const sf::FloatRect& target);

    // Render the projectile
    void render(sf::RenderWindow& window) const;

private:
    sf::Vector2f position;
    sf::Vector2f direction;
    int speed;
    int damage;
    sf::Sprite projectileSprite;
};

class Weapon {
public:
    // Constructors
    Weapon(const std::string& weaponName, int maxAmmo, int damage);

    // Copy constructor
    Weapon(const Weapon& other);

    // Move constructor
    Weapon(Weapon&& other) noexcept;

    // Destructor
    ~Weapon();

    // Copy assignment operator
    Weapon& operator=(const Weapon& other);

    // Move assignment operator
    Weapon& operator=(Weapon&& other) noexcept;

    // Getters
    std::string getName() const;
    int getAmmo() const;
    bool isOutOfAmmo() const;
    bool isReloading() const;

    // Actions
    virtual void fire(const sf::Vector2f& direction) = 0;  // Pure virtual method for firing, uses direction
    virtual void reload();
    void updateProjectiles(float deltaTime);
    void renderProjectiles(sf::RenderWindow& window);

protected:
    // Visuals and sounds
    std::string name;
    sf::Sound fireSound;        // Sound played when the weapon is fired
    sf::Sound reloadSound;      // Sound played when the weapon is reloaded
    sf::Sound emptyClipSound;   // Sound played when out of ammo
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;
    sf::IntRect weaponFrame;

    // Damage
    int damage;
    int splashRadius;

    // Ammo
    int ammo;
    int maxAmmoCapacityMagazine;  // The amount of ammo per magazine
    int maxAmmoCapacityTotal;     // Total ammo capacity

    // Bullet stats
    float bulletSpread;
    int bulletType;
    int bulletSpeed;

    // Projectile list for this weapon
    std::vector<Projectile> projectiles;
    float projectileSpeed;
    float projectileHitRadius;

    // Categorization
    WeaponCategory weaponCategory;
    WeaponType weaponType;
    FireMode fireMode;
};

#endif // VIETNAM_MARINE_2_WEAPON_H
