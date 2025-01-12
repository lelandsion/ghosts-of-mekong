//
// Created by Leland Sion on 2024-12-04.
//

// TODO: Implement a death zone in out of bounds areas

#ifndef VIETNAMMARINE2_ENVIRONMENT_H
#define VIETNAMMARINE2_ENVIRONMENT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <Platform.h>

class Environment {
public:
    Environment(); // Constructor
    // Get all platforms in environment:
    const std::vector<std::shared_ptr<Platform>>& getPlatforms() const; // Return a reference to all platforms

    const std::vector<sf::FloatRect> getPlatformHitBoxes() const; // Stores all static object hitboxes

    // Add a platform to the environment
    void addPlatform(const sf::Vector2f& position, const std::string& texturePath, const sf::FloatRect& customBounds = {});

    // Update environment elements (if necessary)
    void update(float deltaTime);

    // Render all platforms and elements
    void render(sf::RenderWindow& window);

private:
    // Store all platforms as rectangles
    std::vector<std::shared_ptr<Platform>> platforms;
    std::vector<sf::FloatRect> platformHitBoxes; // Stores all static object hitboxes

};

#endif //VIETNAMMARINE2_ENVIRONMENT_H
