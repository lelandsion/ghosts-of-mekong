//
// Created by Leland Sion on 2024-12-04.
//

#ifndef VIETNAMMARINE2_PLATFORM_H
#define VIETNAMMARINE2_PLATFORM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
class Platform {
public:
    // Constructor for sprite-based platform
    Platform(float x, float y, const std::string& texturePath = "", const sf::FloatRect& customBounds = {});

    // Constructor for custom-shaped platforms using convex points
    Platform(const std::vector<sf::Vector2f>& points, const std::string& texturePath = "");

    const sf::FloatRect& getBounds() const; // Get platform bounds for collision detection
    void render(sf::RenderWindow& window) const; // Render platform to the screen
    void update(float deltaTime); // Update the platform (optional, for animations or dynamic platforms)

private:
    sf::Sprite sprite; // Visual representation of the platform
    sf::Texture texture; // Texture for the sprite
    sf::ConvexShape convexShape; // For custom-shaped platforms
    sf::FloatRect bounds; // Collision bounds for the platform
    bool hasTexture; // Whether the platform uses a texture
    bool isConvex; // Whether the platform uses a convex shape
    bool canHit; // Whether or not the platform will collide with projectiles
};

#endif //VIETNAMMARINE2_PLATFORM_H
