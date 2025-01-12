//
// Created by Leland Sion on 2024-12-30.
//

#include "CollisionManager.h"
#include <iostream>

// Add a projectile
void CollisionManager::addProjectile(std::shared_ptr<Projectile> projectile) {
    projectiles.push_back(projectile);
}

// Add an enemy
void CollisionManager::addEnemy(std::shared_ptr<Enemy> enemy) {
    enemies.push_back(enemy);
}

// Set the player (optional)
void CollisionManager::setPlayer(std::shared_ptr<Player> player) {
    this->player = player;
}

std::vector<std::shared_ptr<Projectile>> CollisionManager::getAllProjectiles(const Player& player, const std::vector<std::shared_ptr<Enemy>>& enemies) {
    std::vector<std::shared_ptr<Projectile>> allProjectiles;

    // Get all projectiles from the player
    const auto playerProjectiles = player.getAllProjectiles();
    allProjectiles.insert(allProjectiles.end(), playerProjectiles.begin(), playerProjectiles.end());

    // Get all projectiles from each enemy
    for (const auto& enemy : enemies) {
        const auto enemyProjectiles = enemy->getAllProjectiles();
        allProjectiles.insert(allProjectiles.end(), enemyProjectiles.begin(), enemyProjectiles.end());
    }

    return allProjectiles;
}

bool lineIntersectsLine(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2) {
    auto cross = [](const sf::Vector2f& a, const sf::Vector2f& b) {
        return a.x * b.y - a.y * b.x;
    };

    sf::Vector2f r = p2 - p1;
    sf::Vector2f s = q2 - q1;

    float denominator = cross(r, s);

    // Lines are parallel if denominator is 0
    if (denominator == 0) {
        return false;
    }

    sf::Vector2f qp = q1 - p1;

    float t = cross(qp, s) / denominator;
    float u = cross(qp, r) / denominator;

    // Check if t and u are within [0, 1] to confirm intersection
    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}

bool lineIntersectsRect(const sf::Vector2f& start, const sf::Vector2f& end, const sf::FloatRect& rect) {
    sf::Vector2f topLeft(rect.left, rect.top);
    sf::Vector2f topRight(rect.left + rect.width, rect.top);
    sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);
    sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);

    // Check intersection with all four edges of the rectangle
    return lineIntersectsLine(start, end, topLeft, topRight) ||
           lineIntersectsLine(start, end, topRight, bottomRight) ||
           lineIntersectsLine(start, end, bottomRight, bottomLeft) ||
           lineIntersectsLine(start, end, bottomLeft, topLeft);
}

// Check for collisions
void CollisionManager::checkCollisions(Player &player, std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<sf::FloatRect> &platformHitBoxes) {
    // Retrieve all active projectiles from the player's weapons
    std::vector<std::shared_ptr<Projectile>> projectiles = getAllProjectiles(player, enemies);

    // Handle collisions between projectiles and enemies
    for (auto& projectile : projectiles) {
        for (auto& enemy : enemies) {
            if (!enemy->isAlive()) {
               continue;
            }
            if (!projectile->isMarkedForRemoval()) {

                if (lineIntersectsRect(projectile->getTipStart(), projectile->getTipEnd(),((enemy->getHeadHitBox())))) {
                    projectile->markForRemoval();
                    projectile->setImpactType(ImpactType::Enemy);
                    enemy->applyDamage(projectile->getDamage());
                    std::cout << "Projectile collided with enemy head. " << std::endl;
                    break;
                }
                if (lineIntersectsRect(projectile->getTipStart(), projectile->getTipEnd(),(enemy->getTorsoHitBox()))) {
                    projectile->markForRemoval();
                    projectile->setImpactType(ImpactType::Enemy);
                    enemy->applyDamage(projectile->getDamage());
                    std::cout << "Projectile collided with enemy torso. " << std::endl;
                    break;
                }
                if (lineIntersectsRect(projectile->getTipStart(), projectile->getTipEnd(),(enemy->getLegsHitbox()))) {
                    projectile->markForRemoval();
                    projectile->setImpactType(ImpactType::Enemy);
                    enemy->applyDamage(projectile->getDamage());
                    std::cout << "Projectile collided with enemy legs. "<< std::endl;
                    break;
                }
            }
        }
    }


    // Handle collisions between projectiles and environments
    for (auto& projectile : projectiles) {
        for (const auto& hitbox : platformHitBoxes) {
            if (lineIntersectsRect(projectile->getTipStart(), projectile->getTipEnd(), hitbox)) {
                projectile->markForRemoval();
                projectile->setImpactType(ImpactType::Environment);
                std::cout << "Projectile collided with environment.  "<< std::endl;
            }
        }
    }

    // (Optional) Handle collisions between projectiles and the player
    for (auto& projectile : projectiles) {
        if (lineIntersectsRect(projectile->getTipStart(), projectile->getTipEnd(),(player.getHeadHitBox()))) {
            if (!projectile->isMarkedForRemoval()) {
                projectile->setImpactType(ImpactType::Enemy);
                player.applyDamage(projectile->getDamage());
                projectile->markForRemoval();
                std::cout << "Projectile collided with player Head. " << std::endl;

            }
            break;
        }
        if (projectile->getHitBox().intersects(player.getTorsoHitBox())) {
            if (!projectile->isMarkedForRemoval()) {
                projectile->setImpactType(ImpactType::Enemy);
                player.applyDamage(projectile->getDamage());
                projectile->markForRemoval();
                std::cout << "Projectile collided with player Torso. " << std::endl;
            }
            break;
        }
        if (projectile->getHitBox().intersects(player.getLegsHitbox())) {
            if (!projectile->isMarkedForRemoval()) {
                projectile->setImpactType(ImpactType::Enemy);
                player.applyDamage(projectile->getDamage());
                projectile->markForRemoval();
                std::cout << "Projectile collided with player legs. " << std::endl;
            }
            break;
        }
    }
}

void CollisionManager::createImpactEffect(const sf::Texture& texture, const sf::Vector2f& position, float angle, int frameCount, float frameTime) {
    Impact impact;
    impact.sprite.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();
    int frameWidth = textureSize.x / frameCount; // Assuming horizontal sprite sheet
    int frameHeight = textureSize.y;

    impact.frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    impact.sprite.setTextureRect(impact.frameRect);

    sf::Vector2f offset(frameWidth / 2.f, frameHeight / 2.f);
    impact.sprite.setPosition(position - offset);
    impact.sprite.setRotation(angle);

    impact.frameCount = frameCount;
    impact.frameTime = frameTime;
    impact.elapsedTime = 0.f;
    impact.duration = frameCount * frameTime;

    impacts.push_back(impact);
}

void CollisionManager::renderImpacts(sf::RenderWindow& window, float deltaTime) {
    for (auto it = impacts.begin(); it != impacts.end();) {
        it->elapsedTime += deltaTime;

        int currentFrame = static_cast<int>(it->elapsedTime / it->frameTime);
        if (currentFrame < it->frameCount) {
            it->frameRect.left = currentFrame * it->frameRect.width;
            it->sprite.setTextureRect(it->frameRect);

            window.draw(it->sprite);

            ++it;
        } else {
            it = impacts.erase(it);
        }
    }
}

// Remove objects marked for removal
void CollisionManager::cleanup() {
    projectiles.erase(
            std::remove_if(projectiles.begin(), projectiles.end(),
                           [](const std::shared_ptr<Projectile>& projectile) {
                               return projectile->isMarkedForRemoval();
                           }),
            projectiles.end());

    enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                           [](const std::shared_ptr<Enemy>& enemy) {
                               return enemy->isAlive();
                           }),
            enemies.end());
}