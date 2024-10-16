//
// Created by Leland Sion on 2024-10-15.
//

#include "Enemy.h"
#include <cmath>  // For distance calculations

// Constructor
Enemy::Enemy(EnemyType type, EnemyClass enemyClass, EnemyFaction faction, int health, int damage, int ammo)
        : type(type), enemyClass(enemyClass), faction(faction), health(health), damage(damage), ammo(ammo), alive(true), currentState(EnemyState::Patrolling), currentPatrolIndex(0) {
    // Load the appropriate texture for the enemy based on the type
    // Example: loading texture based on type
    if (!enemyTexture.loadFromFile("path/to/texture.png")) {
        // Handle error
    }
    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(position);  // Position initialized from GameObject
}

// Getters
EnemyType Enemy::getType() const {
    return type;
}

EnemyClass Enemy::getClass() const {
    return enemyClass;
}

EnemyFaction Enemy::getFaction() const {
    return faction;
}

int Enemy::getHealth() const {
    return health;
}

bool Enemy::isAlive() const {
    return alive;
}

EnemyState Enemy::getCurrentState() const {
    return currentState;
}

// Setters
void Enemy::setHealth(int newHealth) {
    health = newHealth;
    if (health <= 0) {
        die();
    }
}

void Enemy::applyDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        die();
    }
}

void Enemy::applyStatusEffect(StatusEffect effect, float duration) {
    statusEffectManager.applyStatusEffect(effect, duration);
}

// Patrol logic: Move the enemy along predefined patrol points
void Enemy::patrol(float deltaTime) {
    if (currentPatrolIndex < patrolPoints.size()) {
        // Move toward the next patrol point
        sf::Vector2f targetPoint = patrolPoints[currentPatrolIndex];
        moveTo(targetPoint, deltaTime);

        // Check if reached patrol point
        if (std::abs(position.x - targetPoint.x) < 5.f && std::abs(position.y - targetPoint.y) < 5.f) {
            currentPatrolIndex++;
        }
    } else {
        // Loop back to the first patrol point
        currentPatrolIndex = 0;
    }
}

// Detect player logic
void Enemy::detectPlayer(const Player& player) {
    if (isPlayerInLineOfSight(player)) {
        currentState = EnemyState::Alerted;
    }
}

// Logic to advance toward the player if they are hiding or out of sight
void Enemy::advanceTowardPlayer(float deltaTime) {
    // Move toward the player's last known position
    moveTo(player.getPosition(), deltaTime);
}

// Check if the player is in the enemy's line of sight
bool Enemy::isPlayerInLineOfSight(const Player& player) {
    // Example logic: check if the player is within a certain range
    float detectionRange = 500.f;  // Example detection range
    sf::Vector2f playerPos = player.getPosition();

    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return distance <= detectionRange;
}

// Engage player: attack or advance depending on range
void Enemy::engagePlayer(const Player& player) {
    if (currentState == EnemyState::Alerted) {
        if (isPlayerInLineOfSight(player)) {
            fireWeapon(player);
        } else {
            advanceTowardPlayer(0.5f);  // Adjust deltaTime for smooth movement
        }
    }
}

// Firing weapon at the player
void Enemy::fireWeapon(const Player& player) {
    if (ammo > 0) {
        // Fire at the player (you can add more logic for accuracy, etc.)
        // Example: reduce player's health
        player.applyDamage(damage);
        ammo--;
    } else {
        reloadWeapon();
    }
}

// Reload the weapon when out of ammo
void Enemy::reloadWeapon() {
    currentState = EnemyState::Reloading;
    // Add some logic for reloading time
    ammo = 10;  // Example ammo reload capacity
    currentState = EnemyState::Attacking;  // Resume attacking after reload
}

// Taking cover after being under fire
void Enemy::takeCover() {
    currentState = EnemyState::TakingCover;
    // Logic to find cover (could be a nearby position or object)
    // Move toward the cover position
}

// Melee attack when the player is in close range
void Enemy::meleeAttack(Player& player) {
    if (currentState == EnemyState::MeleeAttack) {
        // Apply melee damage to the player
        player.applyDamage(damage * 2);  // Example: melee does more damage
    }
}

// Search for the player after losing sight
void Enemy::searchForPlayer(float deltaTime) {
    // Logic to search the area for the player
    // If player is not found after a set time, go back to patrolling
    currentState = EnemyState::Patrolling;
}

// Move the enemy
void Enemy::move(float deltaTime) {
    // Use velocity and deltaTime to move the enemy sprite
    position += velocity * deltaTime;
    enemySprite.setPosition(position);
}

// Rendering the enemy
void Enemy::render(sf::RenderWindow& window) {
    window.draw(enemySprite);
}

// Handle enemy death
void Enemy::die() {
    alive = false;
    currentState = EnemyState::Dead;
    playDeathAnimation();
}

// Play the death animation (can be expanded based on enemy type)
void Enemy::playDeathAnimation() {
    // Logic for playing different death animations
    // Example: falling over, disintegration, etc.
}

// Private helper function to move to a specific point
void Enemy::moveTo(const sf::Vector2f& targetPoint, float deltaTime) {
    sf::Vector2f direction = targetPoint - position;
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude > 0.1f) {
        sf::Vector2f normalizedDirection = direction / magnitude;
        position += normalizedDirection * 100.f * deltaTime;  // 100.f is the enemy speed
        enemySprite.setPosition(position);
    }
}

