//
// Created by Leland Sion on 2024-10-15.
//

#ifndef ENEMY_TYPE_H
#define ENEMY_TYPE_H

enum class EnemyType {
    None,

    // Basic Ranged Enemies
    VietnamSoldier,               // Regular Vietnam soldiers with hats
    VietnamArmySoldier,           // Better equipped Vietnam army soldiers
    PretendVillagerSoldier,       // Villagers posing as soldiers
    GuerrillaRanged,              // Guerrilla fighters hiding in bushes, trees, ground
    FarmerWithAK,                 // Farmers with AK-47s
    TorturedMarine,               // Tortured US Marines or Viet Cong soldiers

    // Special Weapons Enemies
    BombPusher,                   // Enemies pushing bombs on bicycles
    Grenadier,                    // Enemies throwing grenades
    Sniper,                       // Long-range sniper enemies
    MortarOperator,               // Mortar operators with explosive rounds
    RPGOperator,                  // Enemies equipped with RPGs

    // Basic Melee Enemies
    FarmerMelee,                  // Farmers with melee weapons (pitchforks, sickles)
    GuerrillaMelee,               // Guerrilla fighters using melee attacks
    MeleeCharger,                 // Enemies charging with melee weapons

    // Animals and Special Creatures
    Monkey,                       // Monkeys used by enemies or wild
    Python,                       // Pythons used for ambush attacks
    Buffalo,                      // Super durable buffalo
    Tiger,                        // A stronger, more aggressive tiger
    Elephant,                     // A potential enemy elephant
    KillerDuck,                   // Disguised duck that becomes super powerful when provoked
    LivingBush,                   // Hallucination enemy (tree or bush during drug trip)
    AggressiveFauna,              // Large, aggressive plants (e.g., Venus flytrap)
    Zombie,                       // Zombie enemies
    Alien,                        // Squishy but dangerous aliens
    AlienSpaceSuit,               // Flying aliens in space suits
    AlienHoverKiller,             // Hovering alien enemies

    // Heavy Enemies
    SkilledSoldier,               // Particularly strong or skilled soldiers
    HeavyMachineGunOperator,      // Heavy machine gunners
    SpecialForces,                // Elite special forces
    Assassin,                     // Special assassins with stealth abilities
    VeteranVietCong,              // Experienced Viet Cong soldiers
    General,                      // Powerful generals
    Politician,                   // Politicians who fight barehanded but are very powerful

    // Vehicles/Utility Enemies
    AAOperator,                   // Anti-aircraft operators
    ElephantRider,                // People riding elephants
    Pillbox,                      // Stationary pillbox enemies
    Truck,                        // Trucks used for transport or attacks
    Gunboat,                      // Enemy gunboats on rivers
    Tank,                         // Heavy enemy tanks
    Helicopter,                   // Enemy helicopters
    Jet,                          // Fighter jets (e.g., MiG jets)

    // Mini-Bosses
    APCMiniBoss,                  // Armored personnel carrier mini-boss
    MartialArtsMaster,            // Martial arts master (powerful melee boss)
    DerangedCommander,            // US Army commander (like Colonel Kurtz)
    SuperMutantMiniBoss,          // A more powerful mutant mini-boss
    ChemistMutant,                // Scientist who mutated using chemical weapons
    Xenomorph,                    // Xenomorph with acid blood attacks
    FlyingSaucerMiniBoss,         // Flying saucer mini-boss with a second phase (squid alien)
    Rambo,                        // Rambo-like mini-boss
    TerminatorMiniBoss,           // The Terminator as a mini-boss

    // Main Bosses
    EarlyGeneralBoss,             // Early-game boss general
    MiG35Boss,                    // MiG-35 jet as a boss
    GeneralVoNguyenGiap,          // Final boss with soldiers and vehicles
    MechBoss,                     // Giant mech as a boss
    DragonBoss,                   // Dragon boss
    PredatorBoss,                 // The Predator as a surprise mid-game boss
    HoChiMinhBoss,                // Endgame boss with multiple phases
    TheMasterBoss,                // The Master from Fallout guarding a nuclear missile
};

#endif // ENEMY_TYPE_H
