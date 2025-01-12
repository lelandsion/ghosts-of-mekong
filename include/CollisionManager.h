//
// Created by Leland Sion on 2024-12-30.
//

#ifndef VIETNAMMARINE2_COLLISIONMANAGER_H
#define VIETNAMMARINE2_COLLISIONMANAGER_H

#include <vector>
#include "../src/weapon/Projectile.h"
#include "../src/enemy/Enemy.h"
#include "../src/player/Player.h" // Include if players are involved in collisions


class CollisionManager {
public:
    // Add objects to be managed
    void addProjectile(std::shared_ptr<Projectile> projectile);
    void addEnemy(std::shared_ptr<Enemy> enemy);
    void setPlayer(std::shared_ptr<Player> player);
    std::vector<std::shared_ptr<Projectile>> getAllProjectiles(const Player& player, const std::vector<std::shared_ptr<Enemy>>& enemies);

    // Perform collision checks
    void checkCollisions(Player &player, std::vector<std::shared_ptr<Enemy>> &enemies, std::vector<sf::FloatRect> &platformsHitBoxes);
    void createImpactEffect(const sf::Texture& texture, const sf::Vector2f& position, float angle, int frameCount, float frameTime);
    void renderImpacts(sf::RenderWindow& window, float deltaTime);

    // Remove objects marked for removal
    void cleanup();

private:
    struct Impact {
        sf::Sprite sprite;
        float duration;       // Total duration of the effect
        float elapsedTime;    // Time elapsed since the effect started
        sf::IntRect frameRect; // Current frame rectangle for animation
        int frameCount;       // Total number of frames
        float frameTime;      // Time each frame is displayed
    };

    std::vector<Impact> impacts; // List of active impact effects
    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Player> player = nullptr; // Optional if player is part of collisions
};


#endif //VIETNAMMARINE2_COLLISIONMANAGER_H
