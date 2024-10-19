//
// Created by Leland Sion on 2024-10-15.
//
// Enum: DeathType
// Description: Defines the various types of death that can occur in the Vietnam Marine game.
// Each type represents a different mechanism of death, providing context for gameplay and
// potentially affecting game mechanics such as scoring, animations, or game-over conditions.
//
// Usage:
// DeathType death = DeathType::Shot;
// if (death == DeathType::Burned) {
//     // Handle burned death scenario
// }
//
// Notes:
// - The enum values can be extended for future gameplay features.
// - Consider the implications of each death type on gameplay mechanics and player experience.

#ifndef VIETNAM_MARINE_2_DEATHTYPE_H
#define VIETNAM_MARINE_2_DEATHTYPE_H

enum class DeathType {
    None,

    // Standard Death Types
    Standard,           // General death (collapsing to the ground)
    Shot,               // Death by BulletWeapon

    cut,                // death by melee weapon
    splitInHalf,         // death by high damage melee weapon

    // Fire-Related Deaths
    Burned,             // Death by minor fire damage
    Incinerated,        // Death by intense fire, full-body burn

    // Explosive Deaths
    Exploded,           // Death by explosion (e.g., grenade)
    Obliterated,        // Death by large explosion (e.g., rocket, bomb)

    // Laser/Disintegration Deaths
    Disintegrated,      // Death by low-power laser, partial disintegration
    Vaporized,          // Death by high-power laser, complete vaporization

    // Alien gun deaths
    Atomized, // reduced to a skeleton that stays in its death position

    // Ice/Freezing Deaths
    Frozen,             // Death by freezing (e.g., low-damage freezing)
    IceCube,          // High-damage freezing, body shatters

    // Poison/DoT Deaths
    Poisoned,           // Death by poison (damage over time)
    Dissolved,          // Death by Acid (DoT)
    BledOut,            // Death by slow blood loss (DoT)

    // Electric Deaths
    Electrified,        // Death by electric shock (e.g., taser)

    // Special Deaths
    Microwaved,         // Body boils then explodes
    Gooified,           // Death by plasma
    RadiationPoisoning,  // Death by radiation

    // Environmental Deaths
    Crushed,            // Death by falling or heavy object
    Drowned,            // Death by drowning (water or liquid)
    Impaled,            // Death by Spikes
    SoulStolen,         // Death by Death status effect
};


#endif //VIETNAM_MARINE_2_DEATHTYPE_H
