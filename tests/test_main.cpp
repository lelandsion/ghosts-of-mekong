//
// Created by Leland Sion on 2024-12-04.
//

#include <SFML/Graphics.hpp>
#include "player/Player.h"
#include "enemy/Enemy.h"
#include "enemy/EnemyClassEnum.h"
#include "enemy/EnemyFactionEnum.h"
#include "../include/CollisionManager.h"
#include "TestLevel.h" // Include the test level
#include "iostream"

// consider adding a directory for effects
int main() {

    // Create a window for testing
    int windowSizeX = 1000;
    int windowSizeY = 600;
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Test Level");
    window.setFramerateLimit(60); // Set the frame limit

    // Create a view for the camera moving with the player
    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
    window.setView(view);


    // Add a player for testing
    Player player( {700.f, 200.f}, 200.f, 300);

    // Create some weapons
    // ** make and m4 and give it to the player
    std::shared_ptr<Weapon> ak47 = std::make_shared<Weapon>("../assets/weapon/ak47.png", "AK-47", 0.2f, 20.f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);
    std::shared_ptr<Weapon> hands = std::make_shared<Weapon>("", "", 0.2f, 0.5f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);
    //std::shared_ptr<Weapon> m4 = std::make_shared<Weapon>("../assets/weapon/ak47.png", "AK-47", 0.2f, 0.5f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);

    // Add weapons to the player
    player.addWeapon(ak47);
    player.addWeapon(hands);
    player.equipWeapon(1);
    player.equipWeapon(0);
    player.setWeaponAmmo(0, 50);

    // Add a few enemies
    std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>(
            EnemyType::VietnamArmySoldier,
            EnemyClass::Ranged,
            sf::Vector2f(10.f, 50.f),
            50.f, 100
    );

    std::vector<sf::Vector2f> enemy1PatrolPoints;
    sf::Vector2f patrolLeft = {500,400};
    sf::Vector2f patrolRight = {10,400};
    enemy1PatrolPoints.push_back(patrolLeft);
    enemy1PatrolPoints.push_back(patrolRight);
    enemy1->setPatrolRoute(enemy1PatrolPoints);

    // Add weapons to enemies
    std::shared_ptr<Weapon> enemyAk47 = std::make_shared<Weapon>("../assets/weapon/ak47.png", "AK-47", 0.2f, 20.f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);
    enemy1->addWeapon(enemyAk47);

    std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>(
            EnemyType::VietnamArmySoldier,
            EnemyClass::Ranged,
            sf::Vector2f(100.f, -70.f),
            50.f, 100
    );

    std::vector<sf::Vector2f> enemy2PatrolPoints;
    sf::Vector2f enemy2PatrolLeft = {500,85};
    sf::Vector2f enemy2PatrolRight = {10,85};
    enemy2PatrolPoints.push_back(enemy2PatrolLeft);
    enemy2PatrolPoints.push_back(enemy2PatrolRight);
    enemy2->setPatrolRoute(enemy2PatrolPoints);

    // Add weapons to enemies
    std::shared_ptr<Weapon> enemy2Ak47 = std::make_shared<Weapon>("../assets/weapon/ak47.png", "AK-47", 0.2f, 20.f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);
    enemy2->addWeapon(enemy2Ak47);

    std::shared_ptr<Enemy> enemy3 = std::make_shared<Enemy>(
            EnemyType::VietnamArmySoldier,
            EnemyClass::Ranged,
            sf::Vector2f(2400.f, 100.f),
            50.f, 100
    );

    std::vector<sf::Vector2f> enemy3PatrolPoints;
    sf::Vector2f enemy3PatrolLeft = {2400,240};
    sf::Vector2f enemy3PatrolRight = {2000,240};
    enemy3PatrolPoints.push_back(enemy3PatrolLeft);
    enemy3PatrolPoints.push_back(enemy3PatrolRight);
    enemy3->setPatrolRoute(enemy3PatrolPoints);

    // Add weapons to enemies
    std::shared_ptr<Weapon> enemy3Ak47 = std::make_shared<Weapon>("../assets/weapon/ak47.png", "AK-47", 0.2f, 20.f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);
    enemy3->addWeapon(enemy3Ak47);

    std::shared_ptr<Enemy> enemy4 = std::make_shared<Enemy>(
            EnemyType::VietnamArmySoldier,
            EnemyClass::Ranged,
            sf::Vector2f(2700.f, 100.f),
            50.f, 100
    );

    std::vector<sf::Vector2f> enemy4PatrolPoints;
    sf::Vector2f enemy4PatrolLeft = {2400,240};
    sf::Vector2f enemy4PatrolRight = {2000,240};
    enemy4PatrolPoints.push_back(enemy4PatrolLeft);
    enemy4PatrolPoints.push_back(enemy4PatrolRight);
    enemy4->setPatrolRoute(enemy4PatrolPoints);

    // Add weapons to enemies
    std::shared_ptr<Weapon> enemy4Ak47 = std::make_shared<Weapon>("../assets/weapon/ak47.png", "AK-47", 0.2f, 20.f, "../assets/weapon/bullet_AK47.png", 30, 500, FireMode::Automatic);
    enemy4->addWeapon(enemy4Ak47);

    // Now store that same pointer in your vector
    std::vector<std::shared_ptr<Enemy>> enemies;
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    enemies.push_back(enemy4);

    // Create the testLevel
    Environment testLevel = createTestLevel();
    std::vector<sf::FloatRect> platformsHitBoxes = testLevel.getPlatformHitBoxes();
    // create a vector of all the platform hitboxes in the the environemnt

    // Create the clock timer
    sf::Clock clock;

    // Create a collision manager
    CollisionManager collisionManager;

    // Create a background and set it as a repeated picture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../assets/level/test_background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    /*backgroundTexture.setRepeated(true);
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

   *//* // Scale or position it as needed
    backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );*//*

    backgroundSprite.setTextureRect(sf::IntRect(0, 0, 5000, 5000));
    backgroundSprite.setPosition(-500,-500);
    */

    // Variables for scrolling
    // do a shader for the3 passive scrolling
    sf::Vector2f passiveScrollSpeed(6.f, 0.f);
    sf::Vector2f backgroundOffset;

    const int gridWidth = 5; // Number of background sprites horizontally
    const int gridHeight = 5; // Number of background sprites vertically
    std::vector<sf::Sprite> backgrounds;

    // Create a grid of sprites for the backgroudn scrolling

    // Initial offset for parallax layers
    sf::Vector2f gridStartPosition(-2000.f, -1500.f);

// Create a grid of sprites for the background scrolling
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            sf::Sprite sprite(backgroundTexture);
            sprite.setPosition(
                    gridStartPosition.x + i * backgroundTexture.getSize().x,
                    gridStartPosition.y + j * backgroundTexture.getSize().y
            );
            backgrounds.push_back(sprite);
        }
    }


    // Main test loop
    while (window.isOpen()) {
        sf::Event event;

        // Event handling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Center of the view is the player, the view will move with the player
        sf::Vector2f center = player.getPosition();
        view.setCenter(center);

        // Apply the view to the window
        window.setView(view);

        // Mouse position
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Check collisions
        collisionManager.checkCollisions(player, enemies, platformsHitBoxes);

        // Handle clock and update
        float deltaTime = clock.restart().asSeconds();
        // Update player put these in a function ***
        if (player.checkAlive()) {
            player.handleInput(deltaTime, window);
        }
        player.updatePhysics(deltaTime);
        player.updateEnvironmentInteraction(deltaTime, testLevel);
        player.updateAnimation(deltaTime);
        player.updateMouseAim(mousePosition, window);

        // Update the player weapons
        player.updateWeapons(deltaTime);
        // The player also updates the weapons

        // Update the projectiles
        // Remember to think about how the projectiles should still persist even if switched to another weapon
        // Handle the deletion of projectiles in the weapon.update function
        for (auto& weapon : player.getWeapons()) {
            if (weapon) {
                // this will also take the vector of all the enemies and all the environments for hit detection
                weapon->updateProjectiles(deltaTime);
            }
        }

        for (auto& enemy : enemies) {
            enemy->updatePhysics(deltaTime);                          // Update physics for the enemy
            enemy->updateEnvironmentInteraction(deltaTime, testLevel); // Handle interaction with the environment
            enemy->updateAnimation(deltaTime);                        // Update animations based on state
            enemy->updateAi(deltaTime, player);                       // Update AI behavior relative to the player
            if(enemy->getCurrentWeapon()) {
                enemy->updateWeapons(deltaTime);
                enemy->getCurrentWeapon()->updateProjectiles(deltaTime);
            }
        }

        //Parallax background effect
        sf::Vector2f playerVelocity = player.getVelocity(); // Get player's velocity


        // Update background positions
        for (auto& bg : backgrounds) {
            // Combine passive scrolling and player velocity
            bg.move(
                    (passiveScrollSpeed.x + playerVelocity.x * 0.4) * deltaTime,
                    (passiveScrollSpeed.y + playerVelocity.y * 0.4) * deltaTime
            );

            // Ensure proper alignment and reposition horizontally
            // Reposition horizontally if it moves out of bounds
            // Wrap horizontally
            if (bg.getPosition().x + backgroundTexture.getSize().x < gridStartPosition.x) {
                bg.setPosition(
                        bg.getPosition().x + gridWidth * backgroundTexture.getSize().x,
                        bg.getPosition().y
                );
            } else if (bg.getPosition().x > gridStartPosition.x + gridWidth * backgroundTexture.getSize().x) {
                bg.setPosition(
                        bg.getPosition().x - gridWidth * backgroundTexture.getSize().x,
                        bg.getPosition().y
                );
            }

            // Wrap vertically
            if (bg.getPosition().y + backgroundTexture.getSize().y < gridStartPosition.y) {
                bg.setPosition(
                        bg.getPosition().x,
                        bg.getPosition().y + gridHeight * backgroundTexture.getSize().y
                );
            } else if (bg.getPosition().y > gridStartPosition.y + gridHeight * backgroundTexture.getSize().y) {
                bg.setPosition(
                        bg.getPosition().x,
                        bg.getPosition().y - gridHeight * backgroundTexture.getSize().y
                );
            }
        }

        /*//Parallax background effect
        sf::Vector2f playerVelocity = player.getVelocity(); // Get player's velocity
        backgroundOffset.x -= (passiveScrollSpeed.x + playerVelocity.x) * deltaTime * 0.4f; // Background scrolls at half speed
        backgroundOffset.y -= (passiveScrollSpeed.y + playerVelocity.y) * deltaTime * 0.4f;

        // Update the texture rectangle to create the scrolling effect
        backgroundSprite.setTextureRect(sf::IntRect(
                static_cast<int>(backgroundOffset.x),
                static_cast<int>(backgroundOffset.y),
                5000,
                5000
                ));*/

        // Render test level
        window.clear();
        // Draw the background first;
        for (const auto& bg : backgrounds) {
            window.draw(bg);
        }
        //window.draw(backgroundSprite);
        // Then the environment
        testLevel.render(window);
        // Then the player and objects

        // Render the player and his projectiles
        player.render(window);
        // Weapon is also rendered by the player
        // Render the projectiles
        for (auto& weapon : player.getWeapons()) {
            if (weapon) {
                weapon->renderProjectiles(window);
            }
        }

        // Render the enemy and his projectiles
        for (auto& enemy : enemies) {
            enemy->render(window);
            // Weapon rendering is done by the enemy
            // Render the projectiles for the enemhy
            if (enemy->getCurrentWeapon()) {
                enemy->getCurrentWeapon()->renderProjectiles(window);
            }
        }


        // Debugging:
        /*for (auto& enemy : enemies) {
            enemy->drawPatrolPoints(window);
        }*/


        // Diplay the window
        window.display();

        // Debug:
        if (auto currentWeapon = player.getWeapons()[player.getCurrentWeaponIndex()]) {
            std::cout << "Current ammo for: " << currentWeapon->getName()
                      << ": " << currentWeapon->getAmmo() << std::endl;
        } else {
            std::cout << "No weapon equipped!" << std::endl;
        }/*
        std::cout << "Enemy health: " << enemy->getHealth() << std::endl;
        std::cout << "Player health: " << player.getHealth() << std::endl;
       if (enemy->getCurrentState() == EnemyState::Pursuing) {
            std::cout << "The enemy is pursuing the player. " << std::endl;
        }
        else if (enemy->getCurrentState() == EnemyState::Attacking) {
            std::cout << "The enemy is Attacking the player. " << std::endl;
        }
        else if (enemy->getCurrentState() == EnemyState::Alerted) {
            std::cout << "The enemy is alerted to the player. " << std::endl;
        }
        else if (enemy->getCurrentState() == EnemyState::Patrolling) {
            std::cout << "The enemy is patrolling. " << std::endl;
        }
        else if (enemy->getCurrentState() == EnemyState::Idle) {
            std::cout << "The enemy is idle. " << std::endl;
        }
        else if (enemy->getCurrentState() == EnemyState::Searching) {
            std::cout << "The enemy is Searching. " << std::endl;
        }
        else if (enemy->getCurrentState() == EnemyState::Dead) {
            std::cout << "The enemy is Dead. " << std::endl;
        }*/
    }

    return 0;
}