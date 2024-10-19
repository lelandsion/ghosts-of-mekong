//
// Created by Leland Sion on 2024-10-15.
//
//
// Created by Leland Sion on 2024-10-15.
//
// Enum: WeaponType
// Description: Defines various types of weapons available in the Vietnam Marine game.
// Each enumerator represents a specific weapon class that influences gameplay mechanics,
// such as damage, range, and firing behavior.
//
// Usage:
// WeaponType weaponType = WeaponType::Ranged;
// if (weaponType == WeaponType::Melee) {
//     // Handle melee-specific logic
// }
//
// Notes:
// - Additional weapon types can be added as needed to expand gameplay variety.
// - Consider the implications of each weapon type on game balance and player strategy.

#ifndef VIETNAM_MARINE_2_WEAPONENUMS_H
#define VIETNAM_MARINE_2_WEAPONENUMS_H

// Enum for weapon categories (e.g., types of weapons like Rifle, Shotgun, etc.)
enum class WeaponCategory {
    Melee,
    Pistol,
    Rifle,
    Shotgun,
    Heavy,
    SniperRifle,
    RocketLauncher,
    Laser,
    Special
};

// Enum for specific weapon types (e.g., specific models like AK-47, Desert Eagle, etc.)
enum class WeaponType {
    AK47,
    DesertEagle,
    RPG7,
    M16,
    Shotgun,
    SniperRifle,
    Flamethrower,
    Railgun,
    Minigun
};

// Enum for firing modes (e.g., single-shot, burst fire, etc.)
enum class FireMode {
    SingleShot,
    BurstFire,
    Automatic
};

// Enum for different types of ammo
enum class AmmoType {
    Bullet,
    Shell,
    Rocket,
    Energy,
    Explosive,
    Arrow
};

// Enum for different types of damage a weapon can deal
enum class DamageType {
    Kinetic,
    Explosive,
    Fire,
    Electric,
    Ice,
    Poison,
    Radiation,
    Energy
};

// Enum for the weapon's state (idle, firing, reloading, etc.)
enum class WeaponState {
    Idle,
    Firing,
    Reloading,
    Overheated,
    Jammed
};

// Enum for different types of bullets (armor-piercing, explosive, etc.)
enum class BulletType {
    Normal,
    ArmorPiercing,
    Explosive,
    Incendiary,
    Tracer,
    Poisoned,
    Shock
};

// Enum for different types of reload mechanics
enum class ReloadType {
    Magazine,
    Single,
    EnergyCell
};

#endif // VIETNAM_MARINE_2_WEAPONENUMS_H



#endif //VIETNAM_MARINE_2_WEAPONENUMS_H
