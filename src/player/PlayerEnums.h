//
// Created by Leland Sion on 2024-10-15.
//
// Enum: PlayerClass
// Description: Defines various classes or types of players in the Vietnam Marine game.
// Each enumerator represents a specific player class that may have unique abilities,
// attributes, or roles within the game, impacting gameplay dynamics and strategies.
//
// Usage:
// PlayerClass playerClass = PlayerClass::Infantry;
// if (playerClass == PlayerClass::Sniper) {
//     // Handle sniper-specific logic
// }
//
// Notes:
// - Additional player classes can be added as needed to enhance gameplay variety.
// - Consider implementing class-specific abilities and characteristics to diversify
//   player interactions and strategies.

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
enum class PlayerMovementDirection {
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

// Enum for tracking player health state (e.g., healthy, injured, critical)
enum class PlayerHealthState {
    Happy,             // Full health or near full health
    RoughedUp,         // Health is below 75% but above 25%
    Dying,             // Health is below 25% s
    Dead               // Player is dead
};

// Enum for player actions, useful for managing inputs and transitions between different actions
enum class PlayerAction {
    None,
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

enum class PlayerClass {
    Infantry,          // Starts with a rifle and basic weapons
    Sniper,            // Starts with a sniper lower health better stealth
    Heavy,             // More health heavier weapons less maneuverable
    Medic              // Can heal himself better special weapons
};


#endif //VIETNAM_MARINE_2_PLAYERENUMS_H
