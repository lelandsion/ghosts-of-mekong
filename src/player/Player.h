//
// Created by Leland Sion on 2024-10-09.
//
// Class: Player
// Description: Represents the player character in the Vietnam Marine game.
// The Player class manages player attributes, actions, and interactions within the game world,
// including health, position, controls, and gameplay mechanics such as attacking and movement.
//
// Usage:
// Player player;
// player.setPosition(100, 200);
// player.update(); // Call this in the game loop to update player state
// player.render(window); // Draw the player character to the window
//
// Notes:
// - The Player class may be extended to accommodate different player types,
//   such as special abilities or character classes.
// - Ensure that player controls and interactions are responsive and intuitive
//   for an enhanced gameplay experience.
// TODO: Add ability to change the keybindings
#ifndef VIETNAM_MARINE_2_PLAYER_H
#define VIETNAM_MARINE_2_PLAYER_H
#pragma once

// Includes to be added:

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "PlayerEnums.h"
#include "../weapon/Weapon.h"
#include "../powerup/PowerUpTypeEnums.h"
#include "../status_effect/StatusEffect.h"
#include "../../include/Environment.h"

class Player {
public:

    // Constructors
    Player();

    Player(sf::Vector2f startPosition, float initialSpeed, int initialHealth);
    Player(const Player &other);
    Player(Player &&other) noexcept;

    // Destructor
    ~Player();

    // Rendering
    void initializeSprite(sf::Sprite &sprite, const sf::Texture &texture, const sf::Vector2f &offset, bool isAnimated = false);
    void render(sf::RenderWindow &window);

    // Input handling
    void handleInput(float deltaTime, const sf::RenderWindow &window);

    void updatePhysics(float deltaTime);
    void updateEnvironmentInteraction(float deltaTime, const Environment& environment);
    void updateAnimation(float deltaTime);
    void updateMouseAim(const sf::Vector2i &mousePosition, const sf::RenderWindow &window);
    void updateWeapons(float deltaTime);

    // Hitbox
    sf::FloatRect getHitbox() const;
    sf::FloatRect getHeadHitBox() const;
    sf::FloatRect getTorsoHitBox() const;
    sf::FloatRect getLegsHitbox() const;
    sf::FloatRect getFeetHitbox() const;

    // Health
    int getHealth() const;
    void setHealth(int newHealth);
    bool checkAlive() const;

    // Location, physics
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    // Player states
    PlayerHealthState getHealthState() const;
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
    void addWeapon(std::shared_ptr<Weapon> weapon);
    void equipWeapon(int index);
    void fireCurrentWeapon(const sf::Vector2<float> &direction, const sf::Vector2<float> &swivelPoint);
    void setWeaponAmmo(int weaponIndex, int newAmmo);
    int getCurrentWeaponIndex();
    std::vector<std::shared_ptr<Weapon>> getWeapons();
    std::vector<std::shared_ptr<Projectile>> getAllProjectiles() const;

    // Score
    int getLevelScore() const;
    void addToLevelScore(int points);
    void resetLevelScore();
    int getGrossScore() const;
    void addToGrossScore(int points);

private:
    // Rendering
    sf::Sprite playerSprite;        // Player sprite for rendering ** to be deleted **
    sf::Texture playerTexture;      // Texture for the player sprite this will be a sheet
    sf::Sprite deathSprite;        // Player sprite for rendering ** to be deleted **
    sf::Texture deathTexture;      // Texture for the player sprite this will be a sheet

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

    // stateDelay
    sf::Clock animationClock;        // Clock to track elapsed time
    float idleDelayTimer;
    float stateDelay;
    float fireDelayTimer;
    float fireDelay;

    // Animations
    sf::Vector2i currentFrame;       // Current frame of the animation (x, y index in the sprite sheet)
    sf::Vector2i frameSize;          // Size of each frame in the sprite sheet
    sf::Vector2i deathFrameSize;          // Size of each frame in the sprite sheet

    float frameTime;                 // Time per frame (seconds)
    float elapsedTime;               // Accumulator for frame switching
    sf::IntRect frameRect;           // rectangle for the current frame and displaying the sprite
    sf::IntRect deathFrameRect;           // rectangle for the current frame and displaying the sprite
    sf::IntRect legsFrameRect;       // rectangle for the current frame for the legs and displaying for the legs
    bool jumpAnimationStarted;           // Flag for when the jumping animation has started or not
    bool isFlipped;

    // Movement
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void jump();
    void duck();

    // Physics and attributes
    sf::Vector2f velocity;          // Player movement velocity
    float speed;                    // Movement speed
    float jumpHeight;               // Height for jumping

    bool isJumping;                 // Whether the player is currently jumping
    bool isFalling;                 // Whether the player is falling check this
    bool isDucking;                 // Whether the player is ducking
    bool isOnGround;                // Whether the player is onGround
    bool mousePressed;              // Whether the mouse is being held

    // Health
    int health;                     // Current health of the player
    int maxHealth;                  // Maximum health of the player
    bool isAlive;                   // Whether the player is alive

    // States
    PlayerState playerState;
    PlayerHealthState playerHealthState;
    PlayerMovementDirection playerMovementDirection;
    PlayerAction playerAction;
    PlayerWeaponState playerWeaponState;
    PlayerArmorType playerArmorType;
    PlayerInventoryType playerInventoryType;
    PlayerClass playerClass;

    // Status effects
    StatusEffectManager statusManager;

    // Hitboxes
    void updateHitboxes();
    sf::FloatRect hitbox;           // Main hitbox for the player
    sf::FloatRect headHitbox;           // Main hitbox for the player
    sf::FloatRect torsoHitbox;           // Main hitbox for the player
    sf::FloatRect legsHitbox;           // Main hitbox for the player
    sf::FloatRect feetHitbox;       // Smaller hitbox for ground detection

    // Inventory and weapons
    std::vector<std::shared_ptr<Weapon>> weapons; // List of player's weapons
    std::shared_ptr<Weapon> currentWeapon = nullptr;
    // std::vector<PowerUp> powerUps;                // List of power-ups
    int currentWeaponIndex;                       // Index of currently selected weapon

    // Player stats
    int levelScore;                 // Score for the current level
    int grossScore;                 // Cumulative score across levels
    int kills;                      // Total number of kills
    int headshots;                  // Total number of headshots
    int deaths;                     // Total number of deaths

    // Physics
    float gravity;                  // Gravity affecting the player
    float maxFallSpeed;             // Maximum falling speed
};


#endif //VIETNAM_MARINE_2_PLAYER_H
