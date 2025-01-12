//
// Created by Leland Sion on 2024-10-16.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "../include/animation.h"

enum class ProjectileType {
    Bullet,
    Rocket,
    HeatSeekingRocket,
    Laser,
    Special
};

enum class ImpactType {
    Enemy,
    Player,
    Environment,
    vehicle,
    Object,
    Water
};

class Projectile {
public:
    Projectile(const std::shared_ptr<sf::Texture>& texture, const std::shared_ptr<sf::Texture>& newImpactTexture, const std::shared_ptr<sf::Texture>& newEnemyImpactTexture, const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed, int damage, ProjectileType type);

    // Update the projectile position
    void update(float deltaTime);

    // Check for collisions
    bool checkCollision(const sf::FloatRect& target);

    void markForRemoval();
    void setImpactType(ImpactType impactType);

    // Render the projectile
    void render(sf::RenderWindow& window) const;

    // Get the type of the projectile
    ProjectileType getType() const;

    sf::FloatRect getHitBox() const;
    sf::Vector2f getTipStart() const;
    sf::Vector2f getTipEnd() const;


    int getDamage() const;

    bool isMarkedForRemoval() const;

    bool checkIsFinished();

private:

    sf::Sprite projectileSprite; // Visual representation of the projectile
    sf::Sprite impactSprite;
    std::shared_ptr<sf::Texture> projectileTexture;
    std::shared_ptr<sf::Texture> impactTexture;
    std::shared_ptr<sf::Texture> enemyImpactTexture;
    sf::Vector2f position;
    sf::Vector2f direction;
    ProjectileType type;

    sf::FloatRect hitBox;
    sf::Vector2f tipStart;
    sf::Vector2f tipEnd;

    // Animation:
    float hitAnimationTime;
    float elapsedTime;
    float totalElapsedTime;
    float frameTime;
    sf::Vector2i currentFrame;       // Current frame of the animation (x, y index in the sprite sheet)
    sf::Vector2i frameSize;
    sf::IntRect projectileFrame;
    Animation impactEnemyAnimation;      // Animation for hitting an enemy
    Animation impactEnvironmentAnimation;// Animation for hitting the environment
    Animation impactVehicleAnimation;    // Animation for hitting a vehicle

    ImpactType impactType;

    float speed;
    float hitRadius;
    float damageRadius;          // for explosions
    bool isCollided;
    bool isFinished;
    int damage;
};

#endif // PROJECTILE_H
