//
// Created by Leland Sion on 2024-10-09.
//
#include "../include/Player.h"

Player::Player()
    : position(100.f, 300.f), velocity(0.f, 0.f), speed(200.f), jumpHeight(300.f),
      maxHealth(100), health(100), isAlive(true), isJumping(false), isFalling(true),
      isDucking(false), currentHealthState(HealthState::Happy), currentMovementState(MovementState::Standing),
      currentActionState(ActionState::Idle), levelScore(0), grossScore(0),
      kills(0), headshots(0), deaths(0), gravity(981.f), maxFallSpeed(600.f), currentWeaponIndex(0) {

    if (!playerTexture.loadFromFile("assets/player.png")) {
        // Handle error (e.g., log it)
    }
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(position);
    updateHitboxes();
}

Player::Player(const std::string &texturePath, sf::Vector2f startPosition, float initialSpeed, int initialHealth)
    : position(startPosition), velocity(0.f, 0.f), speed(initialSpeed), jumpHeight(300.f),
      maxHealth(initialHealth), health(initialHealth), isAlive(true), isJumping(false), isFalling(true),
      isDucking(false), currentHealthState(HealthState::Happy), currentMovementState(MovementState::Standing),
      currentActionState(ActionState::Idle), levelScore(0), grossScore(0),
      kills(0), headshots(0), deaths(0), gravity(981.f), maxFallSpeed(600.f), currentWeaponIndex(0) {

    if (!playerTexture.loadFromFile(texturePath)) {
        // Handle error
    }
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(position);
    updateHitboxes();
}

Player::Player(const Player &other)
    : position(other.position), velocity(other.velocity), speed(other.speed), jumpHeight(other.jumpHeight),
      maxHealth(other.maxHealth), health(other.health), isAlive(other.isAlive), isJumping(other.isJumping),
      isFalling(other.isFalling), isDucking(other.isDucking), currentHealthState(other.currentHealthState),
      currentMovementState(other.currentMovementState), currentActionState(other.currentActionState),
      levelScore(other.levelScore), grossScore(other.grossScore), kills(other.kills), headshots(other.headshots),
      deaths(other.deaths), gravity(other.gravity), maxFallSpeed(other.maxFallSpeed), currentWeaponIndex(other.currentWeaponIndex) {

    playerTexture = other.playerTexture;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(other.playerSprite.getPosition());
    updateHitboxes();
}

Player::Player(Player &&other) noexcept
    : position(std::move(other.position)), velocity(std::move(other.velocity)), speed(other.speed), jumpHeight(other.jumpHeight),
    maxHealth(other.maxHealth), health(other.health), isAlive(other.isAlive), isJumping(other.isJumping),
    isFalling(other.isFalling), isDucking(other.isDucking), currentHealthState(other.currentHealthState),
    currentMovementState(other.currentMovementState), currentActionState(other.currentActionState),
    levelScore(other.levelScore), grossScore(other.grossScore), kills(other.kills), headshots(other.headshots),
    deaths(other.deaths), gravity(other.gravity), maxFallSpeed(other.maxFallSpeed), currentWeaponIndex(other.currentWeaponIndex) {

    playerTexture = std::move(other.playerTexture);
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(std::move(other.playerSprite.getPosition()));
    other.health = 0;
    other.isAlive = false;
    other.velocity = {0.f, 0.f};
    updateHitboxes();
}

Player::~Player() {
    // Destructor to handle cleanup if necessary
}

// Input Handling

void Player::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveLeft(1.f);  // Use private movement method
        setMovementState(MovementState::Walking);  // Set state to Walking
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveRight(1.f);  // Use private movement method
        setMovementState(MovementState::Walking);  // Set state to Walking
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        jump();  // Use private method for jumping
        setMovementState(MovementState::Jumping);  // Set state to Jumping
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        duck();  // Use private method for ducking
        setMovementState(MovementState::Ducking);  // Set state to Ducking
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        fireCurrentWeapon();  // Use public method to fire weapon
        setActionState(ActionState::Shooting);  // Set state to Shooting
    }
}

// Update Player's State

void Player::update(float deltaTime) {
    // Update player position based on velocity
    playerSprite.move(velocity * deltaTime);
    updateHitboxes();

    // Update movement state based on vertical velocity
    if (velocity.y > 0.f) {
        setMovementState(MovementState::Falling);  // Set state to Falling
    } else if (velocity.y == 0.f && isAlive) {
        setMovementState(MovementState::Standing);  // Set state to Standing
    }
}

// Render Player

void Player::render(sf::RenderWindow &window) {
    window.draw(playerSprite);
}

// Movement and Actions

void Player::moveLeft(float deltaTime) {
    velocity.x = -speed; // Move left
}

void Player::moveRight(float deltaTime) {
    velocity.x = speed;  // Move right
}

void Player::jump() {
    if (!isJumping && !isFalling) {
        velocity.y = -jumpHeight;  // Jump up (negative y-axis)
        isJumping = true;
        isFalling = true;
    }
}

void Player::duck() {
    isDucking = true;
}

// Health Management

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int newHealth) {
    if (newHealth < 0) {
        health = 0;
        isAlive = false;
        setHealthState(HealthState::Dying);  // Set state to Dying
    } else if (newHealth > maxHealth) {
        health = maxHealth;
    } else {
        health = newHealth;
    }

    // Update health state based on current health
    if (health == maxHealth) {
        setHealthState(HealthState::Happy);
    } else if (health >= maxHealth * 0.75f) {
        setHealthState(HealthState::RoughedUp);
    } else if (health >= maxHealth * 0.25f) {
        setHealthState(HealthState::Wounded);
    } else {
        setHealthState(HealthState::Dying);
    }
}

// Health State Management

Player::HealthState Player::getHealthState() const {
    return currentHealthState;
}

void Player::setHealthState(HealthState newState) {
    currentHealthState = newState;
}

// Movement State Management

Player::MovementState Player::getMovementState() const {
    return currentMovementState;
}

void Player::setMovementState(MovementState newState) {
    currentMovementState = newState;
}

// Action State Management

Player::ActionState Player::getActionState() const {
    return currentActionState;
}

void Player::setActionState(ActionState newState) {
    currentActionState = newState;
}

// Score Management

int Player::getLevelScore() const {
    return levelScore;
}

void Player::addToLevelScore(int points) {
    levelScore += points;
}

void Player::resetLevelScore() {
    levelScore = 0;
}

int Player::getGrossScore() const {
    return grossScore;
}

void Player::addToGrossScore(int points) {
    grossScore += points;
}

// Inventory Management

void Player::addWeapon(std::shared_ptr<Weapon> weapon) {
    weapons.push_back(weapon);
}

void Player::switchWeapon(int index) {
    if (index >= 0 && index < weapons.size()) {
        currentWeaponIndex = index;
    }
}

void Player::fireCurrentWeapon() {
    if (!weapons.empty()) {
        weapons[currentWeaponIndex]->fire();
    }
}

// Hitbox Management

void Player::updateHitboxes() {
    hitbox = playerSprite.getGlobalBounds();

    // Update feet hitbox for ground detection
    feetHitbox = sf::FloatRect(
            playerSprite.getPosition().x,
            playerSprite.getPosition().y + playerSprite.getGlobalBounds().height - 5.f,
            playerSprite.getGlobalBounds().width, 5.f
    );
}

sf::FloatRect Player::getHitbox() const {
    return hitbox;
}

sf::FloatRect Player::getFeetHitbox() const {
    return feetHitbox;
}
