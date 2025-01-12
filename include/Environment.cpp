//
// Created by Leland Sion on 2024-12-04.
//

#include "Environment.h"


Environment::Environment() {}

// Change the vector to store shared pointers

// Modify addPlatform to allocate dynamically and store a shared pointer
void Environment::addPlatform(const sf::Vector2f& position, const std::string& texturePath, const sf::FloatRect& customBounds) {
    auto platform = std::make_shared<Platform>(position.x, position.y, texturePath, customBounds);
    platforms.push_back(platform);
    platformHitBoxes.push_back(platform->getBounds());
}

const std::vector<std::shared_ptr<Platform>>& Environment::getPlatforms() const {
    return platforms;
}

const std::vector<sf::FloatRect> Environment::getPlatformHitBoxes() const {
    return platformHitBoxes;
}

void Environment::update(float deltaTime) {
    for (auto& platform : platforms) {
        platform->update(deltaTime);
    }
}


void Environment::render(sf::RenderWindow& window) {
    // When iterating over platforms, dereference the shared pointer
    for (const auto& platform : platforms) {
        platform->render(window); // Use '->' instead of '.'
    }
}

