//
// Created by Leland Sion on 2024-10-15.
//
// Class: GameObject
// Description: Represents a generic object in the Vietnam Marine game.
// The GameObject class serves as a base for all interactive and non-interactive
// elements within the game world, including players, enemies, items, and environmental
// features. It provides properties and methods common to all game objects,
// such as position, size, and rendering functionality.
//
// Usage:
// GameObject enemy;
// enemy.setPosition(100, 200);
// enemy.render(window);
//
// Notes:
// - This class may be extended for specific object types, such as Player or Enemy.
// - Ensure that derived classes implement their specific behaviors and attributes.
#ifndef VIETNAM_MARINE_GAMEOBJECT_H
#define VIETNAM_MARINE_GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject();  // Constructor
    virtual ~GameObject(); // Destructor

    virtual void update(); // Update the object's state
    virtual void render(sf::RenderWindow& window); // Render the object to the window
    sf::FloatRect getHitbox() const;
    void setPosition(float x, float y); // Set the object's position

protected:
    sf::Vector2f position; // Position of the object
    sf::Sprite sprite; // Sprite representing the object
    sf::Texture texture; // Texture for the object's sprite
    float velocity; // speed of the game object
    int health;
};

#endif // VIETNAM_MARINE_GAMEOBJECT_H
