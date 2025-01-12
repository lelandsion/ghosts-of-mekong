//
// Created by Leland Sion on 2024-10-15.
//
// Enum: EnemyClass
// Description: Defines various classes of enemies in the Vietnam Marine game.
// Each enumerator represents a specific enemy class that determines the enemy's
// combat role and characteristics, affecting gameplay mechanics and strategies.
//
// Usage:
// EnemyClass enemyClass = EnemyClass::Ranged;
// if (enemyClass == EnemyClass::Heavy) {
//     // Handle behavior specific to heavy enemies
// }
//
// Notes:
// - Additional enemy classes can be added as needed to expand gameplay variety.
// - Consider the implications of each enemy class on gameplay balance and design.

#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

enum class EnemyClass {
    None,

    // Combat Roles
    Ranged,               // Enemies that attack from a distance (e.g., soldiers with AKs, snipers)
    Melee,                // Enemies that use melee weapons or charge (e.g., pitchfork-wielding farmers)
    Explosive,            // Enemies that use grenades, RPGs, bombs (e.g., grenadiers, RPG operators)
    Stealth,              // Enemies that use stealth (e.g., guerrilla fighters, assassins)
    Heavy,                // Durable and hard-hitting enemies (e.g., heavy gunners, tanks)
    Special,              // Enemies with unique traits (e.g., aliens, politicians, creatures)
    Vehicle,              // Vehicles like trucks, tanks, helicopters, etc.
    MiniBoss,             // Mini boss enemies,
    Boss,                 // Main Boss enemies,
    Animal,               // Animal-based enemies (e.g., tigers, elephants, pythons)
};

#endif // ENEMY_CLASS_H
