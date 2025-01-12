//
// Created by Leland Sion on 2024-10-15.
//

#include "GameObject.h"

// Default Constructor
//
// Created by Leland Sion on 2024-10-15.
//

// Constructor
GameObject::GameObject()
        : position(0.f, 0.f), velocity(0.f) {
    // Initialize the position and velocity
}

// Destructor
GameObject::~GameObject() {
    // Perform any cleanup if necessary
}

// Update the object's state (default behavior)
void GameObject::update() {
    // Example: Move the sprite based on velocity
    sprite.setPosition(position);
}

// Render the object to the window
void GameObject::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Set the object's position
void GameObject::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(position); // Sync the sprite's position
}