//
// Created by Leland Sion on 2024-12-04.
//

#include "Platform.h"
#include <iostream>

// Sprite-Based Constructor
Platform::Platform(float x, float y, const std::string& texturePath, const sf::FloatRect& customBounds)
        : hasTexture(false), isConvex(false) {
    if (!texturePath.empty()) {
        if (texture.loadFromFile(texturePath)) {
            sprite.setTexture(texture);
            std::cout << "Texture successfully bound to sprite \n";
            hasTexture = true;
            std::cout << "Texture successfully loaded for sprite platform at position ("
                      << x << ", " << y << ").\n";
        } else {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
    }

    // Set sprite position
    sprite.setPosition(x, y);

    // Set bounds: Use the provided custom bounds or default to sprite bounds
    if (customBounds != sf::FloatRect{}) {
        bounds = customBounds;
    } else {
        bounds = sprite.getGlobalBounds();
    }
}

// Convex Shape Constructor
Platform::Platform(const std::vector<sf::Vector2f>& points, const std::string& texturePath)
        : hasTexture(false), isConvex(true) {
    convexShape.setPointCount(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        convexShape.setPoint(i, points[i]);
    }

    if (!texturePath.empty()) {
        if (texture.loadFromFile(texturePath)) {
            convexShape.setTexture(&texture);
            hasTexture = true;
            std::cout << "Texture successfully loaded for convex platform with "
                      << points.size() << " points.\n";
        } else {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
    }

    bounds = convexShape.getGlobalBounds();
}

// Get platform bounds
const sf::FloatRect& Platform::getBounds() const {
    return bounds;
}

// Render the platform
void Platform::render(sf::RenderWindow& window) const {
    if (isConvex) {
        std::cout << "Rendering convex platform with bounds: "
                  << convexShape.getGlobalBounds().left << ", "
                  << convexShape.getGlobalBounds().top << "\n";
        window.draw(convexShape);
    } else {

        window.draw(sprite);
        std::cout << "Rendering sprite platform with bounds: "
                                      << sprite.getGlobalBounds().left << ", "
                                      << sprite.getGlobalBounds().top << "\n";

    }

    // Debugging red hitbox around the platforms

    // Create a rectangle shape for the hitbox
    sf::RectangleShape debugBox(sf::Vector2f(bounds.width, bounds.height));
    debugBox.setPosition(bounds.left, bounds.top);

    // Set debug styling
    debugBox.setFillColor(sf::Color::Transparent);    // No fill, just outline
    debugBox.setOutlineColor(sf::Color::Red);         // Red outline for visibility
    debugBox.setOutlineThickness(1.f);

    // Draw the debug box
    //window.draw(debugBox);
}

// Optional update for dynamic behavior
void Platform::update(float deltaTime) {
    // Add animation or movement logic if needed
}