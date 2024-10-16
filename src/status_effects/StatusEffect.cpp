//
// Created by Leland Sion on 2024-10-15.
//

#include "StatusEffect.h"

void StatusEffectManager::applyStatusEffect(StatusEffect newEffect, float duration) {
    currentEffect = newEffect;
    effectDuration = duration;

    // Handle immediate effects (e.g., initial damage from burning)
    switch (newEffect) {
        case StatusEffect::Burning:
            // Initial fire damage
            break;
        case StatusEffect::Poisoned:
            // Apply initial poison effect
            break;
        case StatusEffect::Frozen:
            // Slow down or freeze movement
            break;
        default:
            break;
    }
}

void StatusEffectManager::updateStatusEffect(float deltaTime) {
    if (currentEffect != StatusEffect::None) {
        effectDuration -= deltaTime;

        if (effectDuration <= 0.f) {
            removeStatusEffect();  // Remove the effect when the duration is over
        }

        // Apply ongoing damage or debuffs if applicable
        switch (currentEffect) {
            case StatusEffect::Poisoned:
                // Damage over time (Poison)
                break;
            case StatusEffect::Burning:
                // Damage over time (Fire)
                break;
            case StatusEffect::Bleeding:
                // Gradual health loss (Bleeding)
                break;
            case StatusEffect::Frozen:
                // Slows or immobilizes the entity
                break;
            default:
                break;
        }
    }
}

void StatusEffectManager::removeStatusEffect() {
    currentEffect = StatusEffect::None;
    effectDuration = 0.f;
}

StatusEffect StatusEffectManager::getCurrentEffect() const {
    return currentEffect;
}

DeathType StatusEffectManager::getDeathType() const {
    switch (currentEffect) {
        case StatusEffect::Poisoned:
            return DeathType::Poisoned;
        case StatusEffect::Burning:
            return DeathType::Burned;
        case StatusEffect::Frozen:
            return DeathType::Frozen;
        case StatusEffect::Electrified:
            return DeathType::Electrified;
        case StatusEffect::Bleeding:
            return DeathType::BledOut;
        default:
            return DeathType::Standard;
    }
}