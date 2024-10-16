//
// Created by Leland Sion on 2024-10-15.
//

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
