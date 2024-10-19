//
// Created by Leland Sion on 2024-10-16.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

enum class ProjectileType {
    Bullet,
    Rocket,
    HeatSeekingRocket,
    Laser,
    Special
};

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, int speed, int damage, ProjectileType type);

    // Update the projectile position
    void update(float deltaTime);

    // Check for collisions
    bool checkCollision(const sf::FloatRect& target);

    // Render the projectile
    void render(sf::RenderWindow& window) const;

    // Get the type of the projectile
    ProjectileType getType() const;

private:
    sf::Sprite projectileSprite; // Visual representation of the projectile
    sf::Sprite hitSprite;
    sf::Vector2f position;
    sf::Vector2f direction;

    ProjectileType type;

    float speed;
    float hitRadius;
    float damageRadius;          // for explosions
    int damage;
};

#endif // PROJECTILE_H
