#include "StatusEffect.h"

// Apply a new status effect
void StatusEffectManager::applyStatusEffect(StatusEffect newEffect, float duration, bool stackable) {
    if (!stackable) {
        // Check if the effect already exists and update its duration
        for (auto& effect : activeEffects) {
            if (effect.effect == newEffect) {
                effect.duration = std::max(effect.duration, duration);
                return;
            }
        }
    }

    // Add a new status effect
    activeEffects.emplace_back(newEffect, duration);

    // Handle immediate effects (e.g., initial damage from burning)
    switch (newEffect) {
        case StatusEffect::Burning:
            // Apply initial fire damage (e.g., reduce health instantly)
            break;
        case StatusEffect::Poisoned:
            // Apply initial poison effect
            break;
        case StatusEffect::Frozen:
            // Freeze entity movement
            break;
        default:
            break;
    }
}

// Update all active status effects
void StatusEffectManager::update(float deltaTime) {
    for (auto it = activeEffects.begin(); it != activeEffects.end(); ) {
        it->duration -= deltaTime;  // Decrease the effect duration

        // Apply ongoing effects
        switch (it->effect) {
            case StatusEffect::Poisoned:
                // Apply poison damage over time
                break;
            case StatusEffect::Burning:
                // Apply burning damage over time
                break;
            case StatusEffect::Bleeding:
                // Apply bleeding damage over time
                break;
            case StatusEffect::Frozen:
                // Handle freezing logic
                break;
            default:
                break;
        }

        // Remove effect if its duration has expired
        if (it->duration <= 0.f) {
            it = activeEffects.erase(it);
        } else {
            ++it;
        }
    }
}

// Check if a specific status effect is active
bool StatusEffectManager::hasStatusEffect(StatusEffect effect) const {
    return std::any_of(activeEffects.begin(), activeEffects.end(),
                       [effect](const ActiveStatusEffect& activeEffect) {
                           return activeEffect.effect == effect;
                       });
}

// Remove a specific status effect
void StatusEffectManager::removeStatusEffect(StatusEffect effect) {
    activeEffects.erase(std::remove_if(activeEffects.begin(), activeEffects.end(),
                                       [effect](const ActiveStatusEffect& activeEffect) {
                                           return activeEffect.effect == effect;
                                       }),
                        activeEffects.end());
}

// Remove all status effects
void StatusEffectManager::clearAllEffects() {
    activeEffects.clear();
}

// Get all active status effects
const std::vector<ActiveStatusEffect>& StatusEffectManager::getActiveEffects() const {
    return activeEffects;
}

// Determine the death type based on active status effects
DeathType StatusEffectManager::getDeathType() const {
    for (const auto& effect : activeEffects) {
        switch (effect.effect) {
            case StatusEffect::Burning:
                return DeathType::Burned;
            case StatusEffect::Poisoned:
                return DeathType::Poisoned;
            case StatusEffect::Frozen:
                return DeathType::Frozen;
            case StatusEffect::Electrified:
                return DeathType::Electrified;
            case StatusEffect::Bleeding:
                return DeathType::BledOut;
            default:
                break;
        }
    }
    return DeathType::Standard;
}