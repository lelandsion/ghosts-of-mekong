//
// Created by Leland Sion on 2024-10-15.
//
// Enum: StatusEffectType
// Description: Defines various types of status effects that can be applied to players
// or enemies in the Vietnam Marine game. Each enumerator represents a specific status
// effect that alters gameplay, affecting attributes such as health, speed, or damage
// output for a limited time.
//
// Usage:
// StatusEffectType statusEffect = StatusEffectType::Poisoned;
// if (statusEffect == StatusEffectType::Stunned) {
//     // Handle stunned behavior for the affected entity
// }
//
// Notes:
// - Additional status effects can be added as needed to expand gameplay mechanics.
// - Consider the duration and interactions of status effects to ensure balanced gameplay.

// TODO: Separate the enums from the statusEffect Manager

#ifndef VIETNAM_MARINE_2_STATUSEFFECTS_H
#define VIETNAM_MARINE_2_STATUSEFFECTS_H

#include "../../include/DeathType.h"
#include <vector>

// Enum for tracking various status effects that can affect players, enemies, or objects
enum class StatusEffect {
    None,               // No active status effect

    // Positive Status Effects (Buffs)
    SpeedBoost,          // Increases movement speed temporarily
    Invincible,          // Immune to all damage
    DoubleDamage,        // Deals double damage
    Shielded,            // Reduces incoming damage or absorbs damage
    Invisibility,        // Player is invisible to enemies
    Hallucination,       // Player Hallucinates
    Energized,           // Restores energy or stamina over time
    StrengthBoost,       // Increases damage output temporarily
    AccuracyBoost,       // Increases ranged weapon accuracy temporarily
    Regeneration,        // Gradually restores health continuously
    Berserk,             // Increases attack damage but may increase incoming damage
    TimeSlow,            // Slows down time for everything but the player/enemy
    Flight,              // Temporarily allows the player/enemy to fly
    MultiShot,           // Fires multiple projectiles at once for ranged weapons
    Invincibility,     // Player is temporarily invincible
    instantKill,
    HealthRegen,       // Player regenerates health over time
    AmmoFull,          // Player regenerates ammo over time
    berserk,           // Player is temporarily invisible to enemies


    // Negative Status Effects (Debuffs)
    Poisoned,            // Gradual health loss over time (damage over time, ignores entity defense)
    Acid,                // Faster health loss over time (entity defense is taken into account)
    Burning,             // Health loss due to fire (DoT)
    Frozen,              // Immobilized due to freezing (may shatter at death)
    Stunned,             // Temporary immobilization or inability to act
    Slowed,              // Reduced movement speed
    Bleeding,            // Health gradually drains from wounds (stackable)
    Weakened,            // Reduces attack damage output
    Blinded,             // Reduces accuracy or prevents vision
    Confused,            // Disorients movement or actions (reversed controls, etc.)
    Electrified,         // Taking damage over time due to electric shock
    Paralyzed,           // Total immobilization, no actions allowed
    Dazed,               // Slows movement and reaction times
    Feared,              // Forces uncontrollable movement away from a source
    Drowning,
    KnockedDown,         // Temporarily knocked down and immobilized
    Radiation,           // slow sickness that has debuffs as it progressively gets worse, until bar is full where the entity will die
    MicroWave,           // Slowly damages until bar is full where the entity will die instantly
    Death,               // Does nothing until bar is fully filled in which the player dies

};

struct ActiveStatusEffect {
    StatusEffect effect;  // The type of status effect
    float duration;       // Remaining duration of the effect

    ActiveStatusEffect(StatusEffect effect, float duration)
            : effect(effect), duration(duration) {}
};

// Class to manage and apply status effects to entities (players, enemies, objects)
class StatusEffectManager {
public:
    StatusEffectManager() = default;

    // Apply a new status effect to the entity
    void applyStatusEffect(StatusEffect newEffect, float duration, bool stackable = true);

    // Update the status effect over time (reduce duration, apply ongoing effects)
    void update(float deltaTime);

    // Get the current status effect active on the entity
    const std::vector<ActiveStatusEffect>& getActiveEffects() const;

    // Checks if a certain status effect is on the entity
    bool hasStatusEffect(StatusEffect effect) const;

    // Remove the active status effect (e.g., when the effect ends)
    void removeStatusEffect(StatusEffect effect);

    // Remove all status effects
    void clearAllEffects();

    // Determine the death type based on the current status effect
    DeathType getDeathType() const;

private:
    std::vector<ActiveStatusEffect> activeEffects;  // List of active status effects
};


#endif // VIETNAM_MARINE_2_STATUSEFFECTS_H

