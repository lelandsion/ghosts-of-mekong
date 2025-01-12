//
// Created by Leland Sion on 2024-10-15.
//
// Class: Enemy
// Description: Represents an enemy character in the Vietnam Marine game.
// The Enemy class inherits from GameObject and defines specific behaviors,
// properties, and attributes related to enemy characters, including
// movement patterns, health, attack methods, and AI behaviors.
//
// Usage:
// Enemy enemy;
// enemy.setPosition(200, 300);
// enemy.update(); // Call this in the game loop to update enemy behavior
// enemy.render(window); // Draw the enemy to the screen
//
// Notes:
// - This class may be extended for different types of enemies, each with
//   unique behaviors and attributes.
// - Consider implementing an AI system to control enemy actions based on
//   game state or player interactions.

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "../../include/GameObject.h"
#include "EnemyTypeEnum.h"
#include "EnemyClassEnum.h"
#include "EnemyFactionEnum.h"
#include "../status_effect/StatusEffect.h"  // For applying status effects
#include "../player/Player.h"         // Shared functionality like health, position
#include <vector>

class Player;

// Enemy states for behavior management
enum class EnemyState {
    Idle,              // Enemy is idle
    Patrolling,        // Enemy is patrolling an area
    Alerted,           // Enemy has detected the player and is on high alert
    Pursuing,
    Attacking,         // Enemy is actively attacking the player
    Cooldown,          // Enemy is pausing between attacks
    TakingCover,       // Enemy is seeking cover
    Reloading,         // Enemy is reloading after emptying ammo
    MeleeAttack,       // Enemy is in melee attack range
    Searching,         // Searching for player after losing sight
    Jumping,
    Dead               // Enemy is dead
};

enum class EnemyHealthState {
    Happy,             // Full health or near full health
    RoughedUp,         // Health is below 75% but above 25%
    Dying,             // Health is below 25% s
    Dead               // Enemy is dead
};

class Enemy : public GameObject {
public:

    // Constructors
    Enemy(EnemyType type, EnemyClass enemyClass, EnemyFaction faction, int health, int damage, int ammo);

    Enemy(EnemyType type, EnemyClass enemyClass, sf::Vector2f startPosition, float initialSpeed, int initialHealth);

    // Rendering and initialization
    void initializeSprite(sf::Sprite &sprite, const sf::Texture &texture, const sf::Vector2f &offset, bool isAnimated = false);
    void render(sf::RenderWindow &window);

    // Update
    void updatePhysics(float deltaTime);
    void updateEnvironmentInteraction(float deltaTime, const Environment& environment);
    void updateAnimation(float deltaTime);
    void updateWeapons(float deltaTime);
    void updateAim(const sf::Vector2f &pointerPosition);
    // Update AI
    void updateAi(float deltaTime, Player& player);
    void handleIdleState(float deltaTime, const Player& player);
    float distanceTo(const sf::Vector2f& targetPoint) const;
    void drawPatrolPoints(sf::RenderWindow& window) const;
    void handlePatrollingState(float deltaTime, const Player& player);
    void handlePursuingState(float deltaTime, const Player& player);
    void handleAttackingState(float deltaTime, Player& player);
    void handleCooldownState(float deltaTime, Player &player);
    void handleAlertedState(float deltaTime, const Player& player);
    void returnToPatrol();
    bool detectPlayer(const Player& player);

    // Hitbox
    sf::FloatRect getHitbox() const;
    sf::FloatRect getHeadHitBox() const;
    sf::FloatRect getTorsoHitBox() const;
    sf::FloatRect getLegsHitbox() const;
    sf::FloatRect getFeetHitbox() const;

    // FOV
    float fovDistance = 200.f;
    float fovAngle = 90.f;
    float currentFacingAngle = 0.f;
    void setfovDistance(float fovDistance);

    // Health
    int getHealth() const;
    void setHealth(int newHealth);

    // Enemy states
    EnemyHealthState getHealthState() const;
    void setHealthState(PlayerHealthState newState);
    PlayerMovementDirection getMovementDirection() const;
    void setMovementDirection(PlayerMovementDirection newState);
    PlayerAction getActionState() const;
    void setActionState(PlayerAction newState);

    // Status effects
    // void applyStatusEffect(StatusEffect effect, float duration, bool stackable = true);
    void updateStatusEffects(float deltaTime);
    // bool hasStatusEffect(StatusEffect effect) const;
    // void removeStatusEffect(StatusEffect effect);

    // Integrate status effects into health, and actions
    void applyDamage(float amount);
    void handleDeath();

    // Weapons and inventory
    void addWeapon(std::shared_ptr<Weapon> &weapon);
    void fireCurrentWeapon(const sf::Vector2<float> &direction, const sf::Vector2<float> &swivelPoint);
    void setWeaponAmmo(int newAmmo);
    std::shared_ptr<Weapon> getCurrentWeapon() const;
    std::vector<std::shared_ptr<Projectile>> getAllProjectiles() const;

    // Getters
    EnemyType getType() const;
    EnemyClass getClass() const;
    EnemyFaction getFaction() const;
    bool isAlive() const;
    EnemyState getCurrentState() const;

    // Setters
    void applyDamage(int damage);
    void applyStatusEffect(StatusEffect effect, float duration);
    void setPatrolRoute(const std::vector<sf::Vector2f>& patrolPoints);  // Set patrol route

    // Core Enemy Logic
    //void detectPlayer(const Player& player);      // Detect the player within a certain range
    void advanceTowardPlayer(const Player& player, float deltaTime);  // Move toward the player if out of sight
    void takeCover();                             // Enemy takes cover if under fire or near explosion
    void reloadWeapon();                          // Reload after firing all ammo
    void fireWeapon(const Player& player);        // Fire weapon at the player
    void meleeAttack(Player& player);             // Melee attack when close to the player
    void attackPlayer(Player& player, float deltaTime);
    void searchForPlayer(float deltaTime);        // Search for the player if lost sight
    void aimAtPlayer(const sf::Vector2f& playerPosition);

    // Logic/behavior stats
    float attackRange;                            // The range in which the enemy will attack the player
    float attackCooldown;                         // The cooldown between attacks e.g. bursts of fire,
    float attackCooldownTimer;
    float attackDuration;                         // The duration of one attack
    float attackDurationTimer;
    float meleeRange;
    float alertDuration;                          // How long the enemy stays in the Alerted state
    float alertTimer;

    // Death and destruction
    void die();                                   // Handle enemy death
    void playDeathAnimation();                    // Play appropriate death animation

private:

    // Attributes
    EnemyType type;
    EnemyClass enemyClass;
    EnemyFaction faction;

    sf::Sprite  enemySprite;        // Player sprite for rendering ** to be deleted **
    sf::Texture enemyTexture;      // Texture for the player sprite this will be a sheet
    sf::Sprite  deathSprite;        // Player sprite for rendering ** to be deleted **
    sf::Texture deathTexture;      // Texture for the death animation

    sf::Sprite torsoSprite;
    sf::Sprite headSprite;
    sf::Sprite armsSprite;
    sf::Sprite leftArmsSprite;
    sf::Sprite legsSprite;

    sf::Texture torsoTexture;
    sf::Texture headTexture;
    sf::Texture armsTexture;
    sf::Texture leftArmsTexture;
    sf::Texture legsTexture;

    sf::Vector2f position;       // Base position
    sf::Vector2f torsoOffset;    // Offset for the torso
    sf::Vector2f headOffset;     // Offset for the head
    sf::Vector2f armsOffset;     // Offset for the arms
    sf::Vector2f leftArmsOffset;     // Offset for the arms
    sf::Vector2f legsOffset;     // Offset for the legs
    sf::Vector2f weaponOffset;     // Offset for the legs

    // Aim pointer
    sf::Vector2f aimPointer;          // A location that represents where the enemy is looking at/aiming at

    // stateDelay
    sf::Clock animationClock;        // Clock to track elapsed time
    float idleDelayTimer;
    float stateDelay;
    float fireDelayTimer;
    float fireDelay;
    EnemyState currentState;

    // Animations
    sf::Vector2i currentFrame;       // Current frame of the animation (x, y index in the sprite sheet)
    sf::Vector2i frameSize;          // Size of each frame in the sprite sheet
    sf::Vector2i deathFrameSize;          // Size of each frame in the sprite sheet


    float frameTime;                 // Time per frame (seconds)
    float elapsedTime;               // Accumulator for frame switching
    sf::IntRect deathFrameRect;           // rectangle for the current frame and displaying the sprite
    sf::IntRect legsFrameRect;       // rectangle for the current frame for the legs and displaying for the legs
    bool jumpAnimationStarted;           // Flag for when the jumping animation has started or not
    bool isFlipped;

    int damage;
    int meleeDamage;
    int ammo;

    // Movement
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void jump();
    void duck();

    // Physics and attributes
    sf::Vector2f velocity;
    float speed;
    float jumpHeight;

    bool isJumping;
    bool isFalling;
    bool isDucking;
    bool isOnGround;
    bool mousePressed;

    // Health
    int health;
    int maxHealth;
    bool alive;

    // States
    EnemyHealthState enemyHealthState;
    PlayerMovementDirection enemyMovementDirection;
    PlayerAction enemyAction;

    // Status effects
    StatusEffectManager statusManager;

    // Hitboxes
    void updateHitboxes();
    sf::FloatRect hitbox;
    sf::FloatRect headHitbox;
    sf::FloatRect torsoHitbox;
    sf::FloatRect legsHitbox;
    sf::FloatRect feetHitbox;

    // Inventory and weapons
    std::shared_ptr<Weapon> currentWeapon = nullptr;
    // std::vector<PowerUp> powerUps;

    // Patrol:
    std::vector<sf::Vector2f> patrolPoints;
    int currentPatrolIndex;

    // Status Effect Management
    StatusEffectManager statusEffectManager;

    // Private helper methods
    void moveTo(const sf::Vector2f& targetPoint, float deltaTime);

    // Physics
    float gravity;                  // Gravity affecting the player
    float maxFallSpeed;             // Maximum falling speed
};

#endif // ENEMY_H
