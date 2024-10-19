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

#ifndef VIETNAM_MARINE_2_PLAYER_H
#define VIETNAM_MARINE_2_PLAYER_H
#pragma once

// Includes to be added:
/*
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Weapon.h"
#include "PowerUp.h"
*/

class Player {
public:

    // Health states
    enum class HealthState {
        Happy,
        RoughedUp,
        Wounded,
        Dying
    };

    // Add states for shooting, being hit, healing etc.

    // Constructors
    Player();
    Player(const std::string &texturePath, sf::Vector2f startPosition, float initialSpeed, int initialHealth);
    Player(const Player &other);
    Player(Player &&other) noexcept;

    // Destructor
    ~Player();

    // Rendering
    void render(sf::RenderWindow &window);

    // Input handling
    void handleInput();

    // Update player state
    void update(float deltaTime);

    // Hitbox
    sf::FloatRect getHitbox() const;
    sf::FloatRect getFeetHitbox() const;

    // Health and health state
    int getHealth() const;
    void setHealth(int newHealth);
    HealthState getHealthState() const;
    void setHealthState(HealthState newState);jo
    bool isAlive() const;

    // Inventory actions
    void addWeapon(std::shared_ptr<Weapon> weapon);
    void switchWeapon(int index);
    void fireCurrentWeapon();

    // Score
    int getLevelScore() const;
    void addToLevelScore(int points);
    void resetLevelScore();
    int getGrossScore() const;
    void addToGrossScore(int points);

private:
    // Rendering
    sf::Sprite playerSprite;        // Player sprite for rendering
    sf::Texture playerTexture;      // Texture for the player sprite
    sf::IntRect animationFrame;     // Rectangle defining current animation frame

    // Movement
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void jump();
    void duck();

    // Position and attributes
    sf::Vector2f position;          // Player position
    sf::Vector2f velocity;          // Player movement velocity
    float speed;                    // Movement speed
    float jumpHeight;               // Height for jumping

    // Player state
    int health;                     // Current health of the player
    int maxHealth;                  // Maximum health of the player
    bool isAlive;                   // Whether the player is alive
    bool isJumping;                 // Whether the player is currently jumping
    bool isFalling;                 // Whether the player is falling
    bool isDucking;                 // Whether the player is ducking

    // Hitboxes
    void updateHitboxes();
    sf::FloatRect hitbox;           // Main hitbox for the player
    sf::FloatRect feetHitbox;       // Smaller hitbox for ground detection

    // Inventory and weapons
    std::vector<std::shared_ptr<Weapon>> weapons; // List of player's weapons
    std::vector<PowerUp> powerUps;                // List of power-ups
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
