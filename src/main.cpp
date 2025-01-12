//
// Created by Leland Sion on 2024-12-01.
//
#include <SFML/Graphics.hpp>
#include "player/Player.h"
#include "../levels/MainMenu.h"
#include "../levels/level1.h"

int main() {
    int windowSizeX = 800;
    int windowSizeY = 600;

    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Player Test Level");

    // Set frame limit for smoother gameplay
    window.setFramerateLimit(60);

    // Create a player
    Player player( {100.f, 200.f}, 200.f, 100);
    // Start with a m4

    // Create the test level environment
    Environment level1 = createLevel1();

    sf::Clock clock;  // To measure deltaTime

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;

        // Event handling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate deltaTime
        float deltaTime = clock.restart().asSeconds();

        // Handle player input
        player.handleInput();

        // Update player physics
        player.updatePhysics(deltaTime);

        // Update player interactions with the environment
        player.updateEnvironmentInteraction(deltaTime, level1);

        // Update player animation
        player.updateAnimation(deltaTime);

        // Render everything
        window.clear();
        level1.render(window); // Render the environment
        player.render(window);   // Render the player
        window.display();
    }

    return 0;
}