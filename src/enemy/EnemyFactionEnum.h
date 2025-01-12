//
// Created by Leland Sion on 2024-10-15.
//
// Enum: EnemyFaction
// Description: Defines various factions of enemies in the Vietnam Marine game.
// Each enumerator represents a specific faction that groups enemies based on their
// allegiance or characteristics, impacting gameplay dynamics and interactions.
//
// Usage:
// EnemyFaction faction = EnemyFaction::Guerrilla;
// if (faction == EnemyFaction::Military) {
//     // Handle behavior specific to military enemies
// }
//
// Notes:
// - Additional factions can be added as necessary to enhance gameplay depth.
// - Consider the implications of faction relationships on gameplay mechanics,
//   such as alliances or rivalries between enemy factions.

#ifndef ENEMY_FACTION_H
#define ENEMY_FACTION_H

enum class EnemyFaction {
    None,

    // Human Factions
    VietCong,                   // Viet Cong soldiers and guerrilla fighters
    NorthVietnameseArmy,         // North Vietnamese Army soldiers
    GuerrillaForces,             // General guerrilla forces, including farmers and villagers
    USDerangedForces,            // Deranged US Army forces (e.g., Colonel Kurtz-like commanders)
    Mercenaries,                 // Mercenaries or special forces (e.g., assassins, special soldiers)

    // Creature Factions
    Animals,                     // Wild animals (e.g., tigers, elephants, etc.)
    Creatures,                   // More fantastical creatures (e.g., killer ducks, plants)

    // Supernatural/Alien Factions
    Aliens,                      // Alien forces (squishy or heavily armored)
    Supernatural,                // Special or supernatural enemies (e.g., Predator, Terminator)

    // Zombies
    Zombies,                     // Zombie faction
};

#endif // ENEMY_FACTION_H
