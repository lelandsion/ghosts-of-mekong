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

#ifndef VIETNAM_MARINE_2_STATUSEFFECTS_H
#define VIETNAM_MARINE_2_STATUSEFFECTS_H

#include "../../include/DeathType.h"

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

// Class to manage and apply status effects to entities (players, enemies, objects)
class StatusEffectManager {
public:
    StatusEffectManager() : currentEffect(StatusEffect::None), effectDuration(0.f) {}

    // Apply a new status effect to the entity
    void applyStatusEffect(StatusEffect newEffect, float duration);

    // Update the status effect over time (reduce duration, apply ongoing effects)
    void updateStatusEffect(float deltaTime);

    // Get the current status effect active on the entity
    StatusEffect getCurrentEffect() const;

    // Remove the active status effect (e.g., when the effect ends)
    void removeStatusEffect();

    // Determine the death type based on the current status effect
    DeathType getDeathType() const;

private:
    StatusEffect currentEffect;  // Current active status effect
    float effectDuration;        // How long the effect will last
};


#endif // VIETNAM_MARINE_2_STATUSEFFECTS_H

