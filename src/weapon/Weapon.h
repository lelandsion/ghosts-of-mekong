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
#include "Projectile.h"
#include "WeaponEnums.h"

enum class WeaponCategory;
enum class WeaponType;
enum class FireMode;


class Weapon {
public:
    // Constructors
    Weapon(const std::string& texturePath,  const std::string& weaponName,
            float fireDelay, int damage, const std::string& projectileTexturePath = "",
            int maxAmmo = 30, float projectileSpeed = 500, FireMode fireMode = FireMode::SingleFire);

    // Copy constructor
    Weapon(const Weapon& other);

    // Move constructor
    Weapon(Weapon&& other);

    // Destructor
    ~Weapon();

    // Copy assignment operator
    Weapon& operator=(const Weapon& other);

    // Move assignment operator
    Weapon& operator=(Weapon&& other);

    // Update the weapon
    void update(float deltaTime, const sf::Vector2f& playerPosition, bool isFlipped);
    void updateProjectiles(float deltaTime);

    // Render the weapon
    void render(sf::RenderWindow& window, const sf::Vector2f& playerPosition, bool isFlipped);
    void renderProjectiles(sf::RenderWindow& window);

    // Getters and setters
    sf::Vector2f getPosition() const;
    std::string getName() const;
    int getAmmo() const;
    void setAmmo(int newAmmo);
    std::vector<std::shared_ptr<Projectile>>& getProjectiles();
    float getCurrentRecoil () const;
    bool isOutOfAmmo() const;
    bool checkReloading() const;
    bool checkCanFire() const;
    FireMode getFireMode() const;
    float getFireDelay() const;
    void setFireMode(FireMode mode);
    void setCanFire(bool value);

    // Actions
    void fire(const sf::Vector2f& direction, const sf::Vector2f& playerPosition, const sf::Vector2f &origin, bool isFlipped);
    void aim(float angle, const sf::Vector2f &origin, bool isFlipped);
    void reload();

protected:
    // Visuals and sounds
    std::string name;
    sf::Sound fireSound;        // Sound played when the weapon is fired
    sf::Sound reloadSound;      // Sound played when the weapon is reloaded
    sf::Sound emptyClipSound;   // Sound played when out of ammo
    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;
    sf::Texture projectileTexture;
    sf::Texture projectileImpactTexture;
    sf::Texture projectileEnemyImpactTexture;
    sf::IntRect weaponFrame;
    sf::Sprite muzzleFlashSprite;
    sf::Texture muzzleFlashTexture;
    sf::IntRect muzzleFlashFrame;
    int currentMuzzleFlashFrame = 0;
    float muzzleFlashFrameTime = 0.1f; // Time per frame
    float muzzleFlashElapsedTime = 0.f;
    bool isMuzzleFlashVisible = false;
    bool isFlipped;

    sf::Vector2f offset; // rename this to origin and the muzzle flash offset
    sf::Vector2f muzzleFlashOffset; // combine the spawn position and the offset they can probably do the same thing
    sf::Vector2f muzzleFlashPosition;
    sf::Vector2f muzzleFlashStaticPosition;
    sf::Vector2f muzzleFlashStaticOrigin;
    bool isMuzzleFlashFlipped;
    float muzzleFlashStaticAngle;
    float muzzleFlashAngle;

    sf::Vector2f spawnPosition;

    // Damage
    int damage;
    int splashRadius;

    // Ammo
    int ammo;
    int maxAmmo;

    // Weapon state
    bool isReloading;
    bool canFire; // Whether or not the weapon can fire
    bool isFiring = false;

    // Bullet stats
    float bulletSpread;
    float bulletSpeed;
    float fireDelay;
    float timeSinceLastFire;
    bool isRecoiling;
    float recoilDuration;
    float recoilTimer;
    float recoilAngle;
    float currentRecoilAngle;

    // Projectile list for this weapon
    std::vector<std::shared_ptr<Projectile>> projectiles; // List of projectiles

    float projectileSpeed;
    float projectileHitRadius;
    ProjectileType projectileType = ProjectileType::Bullet;

    // Categorization
    WeaponCategory weaponCategory;
    WeaponType weaponType;
    FireMode fireMode;

private:

    void copyFrom(const Weapon& other);
    void moveFrom(Weapon&& other);
    void free();
};

#endif // VIETNAM_MARINE_2_WEAPON_H