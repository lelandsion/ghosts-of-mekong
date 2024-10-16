//
// Created by Leland Sion on 2024-10-15.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "../../include/GameObject.h"
#include "EnemyTypeEnum.h"
#include "EnemyClassEnum.h"
#include "EnemyFactionEnum.h"
#include "../status_effects/StatusEffect.h"  // For applying status effects
#include "../player/Player.h"         // Shared functionality like health, position
#include <vector>

// Enemy states for behavior management
enum class EnemyState {
    Patrolling,        // Enemy is patrolling an area
    Alerted,           // Enemy has detected the player and is on high alert
    Attacking,         // Enemy is actively attacking the player
    TakingCover,       // Enemy is seeking cover
    Reloading,         // Enemy is reloading after emptying ammo
    MeleeAttack,       // Enemy is in melee attack range
    Searching,         // Searching for player after losing sight
    Dead               // Enemy is dead
};

class Enemy : public GameObject {
public:
    // Constructors
    Enemy(EnemyType type, EnemyClass enemyClass, EnemyFaction faction, int health, int damage, int ammo);

    // Getters
    EnemyType getType() const;
    EnemyClass getClass() const;
    EnemyFaction getFaction() const;
    int getHealth() const;
    bool isAlive() const;
    EnemyState getCurrentState() const;

    // Setters
    void setHealth(int newHealth);
    void applyDamage(int damage);
    void applyStatusEffect(StatusEffect effect, float duration);
    void setPatrolRoute(const std::vector<sf::Vector2f>& patrolPoints);  // Set patrol route

    // Core Enemy Logic
    void patrol(float deltaTime);                 // Patrol along a route
    void detectPlayer(const Player& player);      // Detect the player within a certain range
    void engagePlayer(const Player& player);      // Attack or take cover when alerted
    void advanceTowardPlayer(float deltaTime);    // Move toward the player if out of sight
    void takeCover();                             // Enemy takes cover if under fire or near explosion
    void reloadWeapon();                          // Reload after firing all ammo
    void fireWeapon(const Player& player);        // Fire weapon at the player
    void meleeAttack(Player& player);             // Melee attack when close to the player
    void searchForPlayer(float deltaTime);        // Search for the player if lost sight

    // Rendering and Movement
    void move(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    // Death and destruction
    void die();                                   // Handle enemy death
    void playDeathAnimation();                    // Play appropriate death animation

private:
    // Attributes
    EnemyType type;
    EnemyClass enemyClass;
    EnemyFaction faction;
    int health;
    int damage;
    bool alive;
    int ammo;                                     // Ammunition count for ranged enemies
    EnemyState currentState;                      // Current state (Patrolling, Attacking, etc.)

    std::vector<sf::Vector2f> patrolPoints;       // Patrol route points
    int currentPatrolIndex;                       // Current patrol point index

    // Status Effect Management
    StatusEffectManager statusEffectManager;

    // Visuals
    sf::Sprite enemySprite;
    sf::Texture enemyTexture;

    // Private helper methods
    bool isPlayerInLineOfSight(const Player& player);  // Checks if the player is within enemy line of sight
};

#endif // ENEMY_H
