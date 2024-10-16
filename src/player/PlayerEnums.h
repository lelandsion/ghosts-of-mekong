//
// Created by Leland Sion on 2024-10-15.
//

#ifndef VIETNAM_MARINE_2_PLAYERENUMS_H
#define VIETNAM_MARINE_2_PLAYERENUMS_H

// Enum for the player's state, tracking overall behavior and actions
enum class PlayerState {
    Idle,              // Player is standing still
    Running,           // Player is moving left or right
    Jumping,           // Player is in the air
    Falling,           // Player is falling down after a jump or drop
    Attacking,         // Player is attacking (melee or ranged)
    Reloading,         // Player is reloading a weapon
    Crouching,         // Player is crouched
    Dashing,           // Player is performing a dash or sprint action
    Dead               // Player has no health and is dead
};

// Enum for the player's movement direction
enum class MovementDirection {
    None,              // No movement
    Left,              // Moving left
    Right,             // Moving right
    Up,                // Moving up (e.g., climbing or jumping)
    Down               // Moving down (e.g., falling or crouching)
};

// Enum for the player’s weapon state
enum class PlayerWeaponState {
    Unarmed,           // Player is not carrying any weapon
    Armed,             // Player has a weapon equipped
    Reloading,         // Player is in the process of reloading the weapon
    OutOfAmmo,         // Player has no ammo in the current weapon
    SwitchingWeapon    // Player is switching between weapons
};

// Enum for player armor types or shield status (if applicable)
enum class PlayerArmorType {
    None,              // No armor
    LightArmor,        // Wearing light armor (minimal protection)
    MediumArmor,       // Wearing medium armor (balanced protection)
    HeavyArmor,        // Wearing heavy armor (high protection)
    Shielded           // Temporarily shielded (e.g., from a power-up or ability)
};

enum class PlayerInventoryType {
    None,
    AdditionalHolster,
    BackPack,
    StockedPack
};

// Enum for special player abilities or power-up effects
enum class PlayerAbility {
    None,              // No special ability active
    SpeedBoost,        // Temporary speed boost from a power-up
    Invincibility,     // Player is temporarily invincible
    DoubleDamage,      // Player deals double damage
    instantKill,
    HealthRegen,       // Player regenerates health over time
    AmmoFull,          // Player regenerates ammo over time
    Shielded,          // Player has an active shield
    berserk,           // Player is temporarily invisible to enemies
    Hallucination,     // Player will hallucinate
};

// Enum for tracking player health state (e.g., healthy, injured, critical)
enum class PlayerHealthState {
    Healthy,           // Full health or near full health
    Injured,           // Health is below 75% but above 25%
    Critical,          // Health is below 25% s
    Dead               // Player is dead
};

// Enum for player actions, useful for managing inputs and transitions between different actions
enum class PlayerAction {
    MoveLeft,          // Moving left
    MoveRight,         // Moving right
    Jump,              // Jumping
    Crouch,            // Crouching
    Attack,            // Attacking (melee or ranged)
    Reload,            // Reloading weapon
    UseAbility,        // Using a special ability (e.g., power-up or skill)
    SwitchWeapon,      // Switching to another weapon
    Interact,          // Interact with objects in the environment (e.g., open doors, pick up items)
    ThrowGrenade       // Throwing a grenade or throwable weapon
};

#endif //VIETNAM_MARINE_2_PLAYERENUMS_H
