//
// Created by Leland Sion on 2024-10-15.
//
// Enum: PowerUpType
// Description: Defines various types of power-ups available to the player in the Vietnam Marine game.
// Each enumerator represents a specific power-up that can enhance the player's abilities,
// provide temporary boosts, or grant unique effects during gameplay.
//
// Usage:
// PowerUpType powerUp = PowerUpType::HealthPack;
// if (powerUp == PowerUpType::SpeedBoost) {
//     // Apply speed increase to the player
// }
//
// Notes:
// - Additional power-up types can be added as needed to expand gameplay variety.
// - Consider the implications of each power-up on game balance and player strategy.


#ifndef VIETNAM_MARINE_2_POWERUPTYPEENUMS_H
#define VIETNAM_MARINE_2_POWERUPTYPEENUMS_H

enum class PowerUpType {
    None,                   // No power-up

    // Temporary Buffs (also tied to status effects)
    SpeedBoost,             // Increases movement speed temporarily
    Invincibility,          // Immune to damage for a short time
    DamageBoost,            // Increases weapon damage temporarily
    Shielded,               // Absorbs damage with a shield
    Invisibility,           // Makes the player invisible to enemies

    // Permanent/One-Time Effects
    ExtraLife,              // Grants an extra life
    FullHealthRestore,      // Restores health to 100%
    FullAmmoRestore,        // Restores full ammunition
    WeaponUpgrade,          // Permanently upgrades the current weapon
    DoubleJump,             // Grants the ability to double-jump permanently
    EnhancedRegeneration,   // Speeds up health regeneration over time
    PermanentDamageBoost,   // Permanently increases player’s damage output
    AmmoBoost,              // Increases max ammo capacity
};


#endif //VIETNAM_MARINE_2_POWERUPTYPEENUMS_H
