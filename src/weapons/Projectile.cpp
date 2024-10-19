//
// Created by Leland Sion on 2024-10-16.
//

#include "Projectile.h"
#include <iostream>

// Constructor
Projectile::Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& direction, int speed, int damage, ProjectileType type)
        : position(startPosition), direction(direction), speed(speed), damage(damage), type(type) {}

// Update projectile's position based on speed and direction
void Projectile::update(float deltaTime) {
    position += direction * static_cast<float>(speed) * deltaTime;
}

// Check collision
bool Projectile::checkCollision(const sf::FloatRect& target) {
    sf::FloatRect projectileBounds = projectileSprite.getGlobalBounds();
    return projectileBounds.intersects(target);
}

// Render the projectile
void Projectile::render(sf::RenderWindow& window) const {
    window.draw(projectileSprite);
}

// Get the projectile type
ProjectileType Projectile::getType() const {
    return type;
}

