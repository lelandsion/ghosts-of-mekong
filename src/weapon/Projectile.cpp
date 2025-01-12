//
// Created by Leland Sion on 2024-10-16.
//

#include "Projectile.h"
#include <iostream>

// Constructor
Projectile::Projectile(const std::shared_ptr<sf::Texture>& texture, const std::shared_ptr<sf::Texture>& newImpactTexture, const std::shared_ptr<sf::Texture>& newEnemyImpactTexture, const sf::Vector2f& startPosition, const sf::Vector2f& direction, float speed, int damage, ProjectileType type)
        : projectileTexture(texture), impactTexture(newImpactTexture), enemyImpactTexture(newEnemyImpactTexture), impactType(ImpactType::Environment), position(startPosition), direction(direction), speed(speed), damage(damage), type(type), frameTime(0.02f), hitAnimationTime(0.2), elapsedTime(0), currentFrame(0,0), frameSize(64,65),  projectileFrame(){
    // Default bullet weapon sprite initialization
    projectileSprite.setTexture(*texture);
    //impactSprite.setTexture(*impactTexture);
    projectileSprite.setPosition(position);
    projectileFrame = sf::IntRect(0, 0, frameSize.x, frameSize.y); // Set to the first frame
    impactSprite.setTextureRect(projectileFrame);

    impactEnemyAnimation.initialize(*newEnemyImpactTexture, {50, 50}, 6, 0.6f);        // Example frame size and frame count
    impactEnvironmentAnimation.initialize(*newImpactTexture, {64, 65}, 7, 0.2f);
    // impactVehicleAnimation.initialize(impactVehicleTexture, {32, 32}, 6, 0.6f);

    //set the angle of the projectile:
    float angle = std::atan2(direction.y, direction.x) * 180.f / M_PI;
    projectileSprite.setRotation(angle);
    impactSprite.setRotation(angle);
    impactSprite.setOrigin(-30,32); // Offset for visual alignment
}


// Update projectile's position based on speed and direction, Update the animation of the projectile
void Projectile::update(float deltaTime) {
    if (isCollided) {
        switch (impactType) {
            case ImpactType::Enemy:
                std::cout << " The impact type is enemy." << std::endl;
                impactEnemyAnimation.update(deltaTime);
                impactEnemyAnimation.applyToSprite(impactSprite);
                isFinished = impactEnemyAnimation.isFinished();
                break;
            case ImpactType::Environment:
                std::cout << " The impact type is environment." << std::endl;
                impactEnvironmentAnimation.update(deltaTime);
                impactEnvironmentAnimation.applyToSprite(impactSprite);
                isFinished = impactEnvironmentAnimation.isFinished();
                break;
           /* case ImpactType::Vehicle:
                impactVehicleAnimation.update(deltaTime);
                impactVehicleAnimation.applyToSprite(impactSprite);
                isFinished = impactVehicleAnimation.isFinished();
                break;*/
        }



        return;
    }

    // update hitBox:
    // Adjusted length of the line for collision detection
    float length = 100.f; // Length of the line (adjust as needed)
    float forwardOffset = 200.f; // Push the line forward along the direction

    // Calculate the forward offset
    sf::Vector2f forward = direction * forwardOffset;
    sf::Vector2f offset = direction * length;

    // Shift the line segment forward
    tipStart = position + forward;       // Move the start point forward
    tipEnd = position + forward - offset;

    // Set position
    position += direction * static_cast<float>(speed) * deltaTime;
    projectileSprite.setPosition(position);
    impactSprite.setPosition(position);
}

// Check collision
bool Projectile::checkCollision(const sf::FloatRect& target) {
    sf::FloatRect projectileBounds = projectileSprite.getGlobalBounds();
    return projectileBounds.intersects(target);
}

void Projectile::markForRemoval() {
    isCollided = true;
}

void Projectile::setImpactType(ImpactType newImpactType) {
    impactType = newImpactType;
    std::cout << "The impact type is being set." << std::endl;
}


/*void Projectile::setImpactType(ImpactType newImpactType) {
    impactType = newImpactType;
}*/

// Render the projectile
void Projectile::render(sf::RenderWindow& window) const {
    if(isCollided) {
        window.draw(impactSprite);
    }
    else {
        window.draw(projectileSprite);
    }

    // Debugging:
    sf::FloatRect hitbox = hitBox;
    sf::RectangleShape debugHitbox(sf::Vector2f(hitbox.width, hitbox.height));
    debugHitbox.setPosition(hitbox.left, hitbox.top);

    // Set the outline color and thickness for visibility
    debugHitbox.setFillColor(sf::Color::Transparent); // No fill, just outline
    debugHitbox.setOutlineColor(sf::Color::Red);      // Make it red for debug
    debugHitbox.setOutlineThickness(1.f);

    // Draw the debug hitbox
    //window.draw(debugHitbox);
    std::cout << "Projectile position: " << position.x << ", " << position.y << std::endl;

    std::cout << "Projectile sprite scale: ("
              << projectileSprite.getScale().x << ", "
              << projectileSprite.getScale().y << ")" << std::endl;

    sf::VertexArray line(sf::Lines, 2);
    line[0].position = tipStart;
    line[0].color = sf::Color::Red;
    line[1].position = tipEnd;
    line[1].color = sf::Color::Red;
    //window.draw(line);
}

// Get the projectile type
ProjectileType Projectile::getType() const {
    return type;
}

sf::FloatRect Projectile::getHitBox() const {
    return hitBox;
}

sf::Vector2f Projectile::getTipStart() const {
    return tipStart;
}

sf::Vector2f Projectile::getTipEnd() const {
    return tipEnd;
}

int Projectile::getDamage() const {
    return damage;
}

bool Projectile::isMarkedForRemoval() const {
    return isCollided;
}


bool Projectile::checkIsFinished() {
    return isFinished;
}

