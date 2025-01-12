//
// Created by Leland Sion on 2024-10-15.
//

// handle reloading

#include "Enemy.h"
#include <cmath>  // For distance calculations
#include "iostream"

// Constructor
Enemy::Enemy(EnemyType type, EnemyClass enemyClass, EnemyFaction faction, int health, int damage, int ammo)
        : type(type), enemyClass(enemyClass), faction(faction), health(health), damage(damage), ammo(ammo), alive(true), currentState(EnemyState::Patrolling), currentPatrolIndex(0) {
    // Load the appropriate texture for the enemy based on the type
    // Example: loading texture based on type

    enemySprite.setTexture(enemyTexture);
    enemySprite.setPosition(position);  // Position initialized from GameObject
}

Enemy::Enemy(EnemyType type, EnemyClass enemyClass, sf::Vector2f startPosition, float initialSpeed, int initialHealth)
        : position(startPosition), velocity(0.f, 0.f), speed(initialSpeed), jumpHeight(300.f),
          maxHealth(initialHealth), health(initialHealth), alive(true), isJumping(false), isFalling(true),
          isDucking(false),
          currentState(EnemyState::Patrolling),
          enemyAction(PlayerAction::None),
          gravity(981.f), maxFallSpeed(600.f),
          stateDelay(0.1f),frameSize(78, 65), deathFrameSize(59,110), frameTime(0.1f), elapsedTime(0.f), currentFrame(0, 0),
          torsoOffset(0.f, 0.f), headOffset(0.f, -13.f), armsOffset(-11.f, -4.f), leftArmsOffset(-1.f, -4.f), legsOffset(-1.f,  13.f),// Default animation setup
          attackCooldownTimer(0), attackCooldown(1), attackRange(400), meleeRange(50), fovDistance(430),  attackDuration(2), attackDurationTimer(0), alertTimer(0), alertDuration(1),
          currentPatrolIndex(0)
{
    // TODO: move the playertexture loading from files into the initialize player/sprite function

    // Load textures
    if (!torsoTexture.loadFromFile("../assets/enemy/enemy_torso.png")) {
        std::cerr << "Failed to load torso texture\n";
    }
    if (!headTexture.loadFromFile("../assets/enemy/enemy_head.png")) {
        std::cerr << "Failed to load head texture\n";
    }
    if (!armsTexture.loadFromFile("../assets/enemy/enemy_arm.png")) {
        std::cerr << "Failed to load arms texture\n";
    }
    /* if (!leftArmsTexture.loadFromFile("../assets/enemy/enemy_arm.png")) {
        std::cerr << "Failed to load arms texture\n";
    }*/
    if (!legsTexture.loadFromFile("../assets/enemy/enemy_legs_sheet.png")) {
        std::cerr << "Failed to load legs texture\n";
    }

    // Initialize sprites
    torsoSprite.setTexture(torsoTexture);
    headSprite.setTexture(headTexture);
    armsSprite.setTexture(armsTexture);
    //leftArmsSprite.setTexture(armsTexture);
    legsSprite.setTexture(legsTexture);

    // Initialize frames for animation
    legsFrameRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
    deathFrameRect = sf::IntRect(0, 0, deathFrameSize.x, deathFrameSize.y);

    // Align sprites initiall
    initializeSprite(torsoSprite, torsoTexture, torsoOffset);
    initializeSprite(headSprite, headTexture, headOffset);
    initializeSprite(armsSprite, armsTexture, armsOffset);
    initializeSprite(leftArmsSprite, leftArmsTexture, armsOffset);
    initializeSprite(legsSprite, legsTexture, legsOffset, true);

    updateHitboxes();
}

void Enemy::initializeSprite(sf::Sprite &sprite, const sf::Texture &texture, const sf::Vector2f &offset, bool isAnimated) {
    // set the texture of the sprite
    sprite.setTexture(texture);

    // *** remove later
    // If the sprite is animated (like legs), set the initial frame
    if (isAnimated) {
        sf::IntRect initialFrame(0, 0, frameSize.x, frameSize.y);
        sprite.setTextureRect(initialFrame);
    }

    // shoulder sprite initialization, these are the offsets from the swivel point to the visual texture
    sf::Vector2f shoulderPositionInTexture = {20.f, 25.f}; // Adjust based on the sprite
    sf::Vector2f leftShoulderPositionInTexture = {32.f, 25.f}; // Adjust based on the sprite
    sf::Vector2f headPositionInTexture = {9.f, 23.f};
    sf::Vector2f legsPositionInTexture = {25, 17.f};


    if (&sprite == &armsSprite ) {
        // Set origin to the shoulder position in the sprite's texture
        sprite.setOrigin(shoulderPositionInTexture.x, shoulderPositionInTexture.y);
    }
    else if (&sprite == &leftArmsSprite) {
        sprite.setOrigin(leftShoulderPositionInTexture.x, leftShoulderPositionInTexture.y);
    }
    else if (&sprite == &headSprite) {
        // Default origin is the center
        sprite.setOrigin(headPositionInTexture.x, headPositionInTexture.y);
    }
    else if (&sprite == &legsSprite) {
        // Default origin is the center
        sprite.setOrigin(legsPositionInTexture.x, legsPositionInTexture.y);
    }
    else {
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    }

    // Position the sprite relative to the player
    sprite.setPosition(position + offset);
}

// handles movement and physics
void Enemy::updatePhysics(float deltaTime) {
    // Move the player to the required position
    position += velocity * deltaTime;

    // Apply gravity only if the player is not on the ground, check if you need the is falling and
    // isJumping this can be done with the same boolean atm
    if (isFalling) {
        velocity.y += gravity * deltaTime;
        // Clamp falling speed to prevent excessive velocity
        if (velocity.y > maxFallSpeed) {
            velocity.y = maxFallSpeed;
        }

    } else {
        // If grounded, ensure vertical velocity is zero
        velocity.y = 0.f;
    }

    // **** check if you need another call here ****
    updateHitboxes();
}

void Enemy::updateEnvironmentInteraction(float deltaTime, const Environment& environment) {
    isOnGround = false;

    // Iterate over all platforms in the environment
    for (const auto& platform : environment.getPlatforms()) {
        const auto& platformBounds = platform->getBounds();

        // Debug: Print platform bounds
        std::cout << "Checking platform at: "
                  << "X: " << platformBounds.left
                  << ", Y: " << platformBounds.top
                  << ", Width: " << platformBounds.width
                  << ", Height: " << platformBounds.height << std::endl;

        // Check if player's feet are intersecting the platform
        if (feetHitbox.intersects(platformBounds)) {
            std::cout << "Collision detected with platform at: "
                      << "X: " << platformBounds.left
                      << ", Y: " << platformBounds.top << std::endl;

            // Align player to the platform's top and stop downward velocity
            float feetOffset = feetHitbox.top + feetHitbox.height - position.y;

            // Align the player so the bottom of the feet hitbox touches the platform's top
            position.y = platformBounds.top - feetOffset + 0.1f;

            velocity.y = 0.f; // Stop vertical movement
            isOnGround = true;

            isFalling = false;
            isJumping = false;

            // the animation state for jumping and for falling is in the updateAnimation function
            break; // Exit loop after resolving the first collision
        }
    }

    // Apply gravity if not on any platform
    if (!isOnGround) {
        isFalling = true;
    }

    // Debug: Report if the player is on the ground or falling
    if (isOnGround) {
        std::cout << "Player is on the ground." << std::endl;
    } else {
        std::cout << "Player is falling." << std::endl;
    }

    // Future: Implement deathzone for out-of-bounds areas
    /*
    if (position.y > environment.getDeathZone()) {
        isAlive = false; // Mark player as dead
    }
    */

}

// Holds the variables that have the information about the animation frame
// Make an animation manager, consider having this function be standardized for any sprite
void Enemy::updateAnimation(float deltaTime) {
    std::cout << "updateAnimation is being called." << std::endl;
    int totalFrames = 0;
    elapsedTime += deltaTime;

    // Determine the current row of the sprite sheet based on the player's state
    switch (currentState) {
        case EnemyState::Idle:
            if (!isJumping && !isFalling) {
                currentFrame.y = 0; // Idle animation row
                legsFrameRect.top = 1 * frameSize.y; // Idle row for legs
                totalFrames = 1;    // Total frames for the idle animation
            }
            break;
        case EnemyState::Pursuing:
            //if (!isJumping && !isFalling) {
                currentFrame.y = 1; // Running animation row
                legsFrameRect.top = 1 * frameSize.y; // Running row for legs
                totalFrames = 11;    // Total frames for the running animation
           // }  // Total frames for the running animation
            std::cout << "EnemyState is pursuing in the animation is being called." << std::endl;
            break;
        case EnemyState::Patrolling:
            if (!isJumping && !isFalling) {
                currentFrame.y = 1; // Running animation row
                legsFrameRect.top = 1 * frameSize.y; // Running row for legs
                totalFrames = 11;    // Total frames for the running animation
            }  // Total frames for the running animation
            break;
        case EnemyState::Attacking:
            if (!isJumping && !isFalling) {
                currentFrame.y = 0; // Running animation row
                legsFrameRect.top = 0 * frameSize.y; // Running row for legs
                totalFrames = 3;    // Total frames for the running animation
            }  // Total frames for the running animation
            break;
        case EnemyState::Dead:
            if (!isJumping && !isFalling) {
                totalFrames = 12;    // Total frames for the running animation
            }  // Total frames for the running animation
            break;
        /*case EnemyState::Jumping:
            currentFrame.y = 2; // Assuming the third row (index 2) is for jumping animation
            legsFrameRect.top = 2 * frameSize.y; // Jumping row for legs
            totalFrames = 8;    // Total frames for the jumping animation*/
    }

    // Check if the falling state is necessary and whether or not the boolean jumping and states are necessary together

    // Start jump animation if needed
    /*if (enemyState == EnemyState::Jumping && !jumpAnimationStarted) {
        jumpAnimationStarted = true;  // Start jump animation
        currentFrame.x = 0;           // Reset to the first frame
        legsFrameRect.left = 0;       // Reset texture to first frame
    }*/

    // Reset the jump animation when grounded
    /*if (isOnGround && jumpAnimationStarted) {
        jumpAnimationStarted = false;  // Reset the animation flag
        currentFrame.x = 0;            // Reset animation to first frame
        legsFrameRect.left = 0;
    }*/

    // Update the frame of the animation
    if (elapsedTime > frameTime) {
        elapsedTime = 0.f;
        // For jumping animations stop at the last frame
        std::cout << "The elapsed time is larger than the frameTime for the animation check." << std::endl;

        if (currentState == EnemyState::Jumping) {
            // Increment the frame index only if it is not at the last frame for jumping

            if (currentFrame.x < totalFrames - 1) {
                currentFrame.x++;
                legsFrameRect.left += frameSize.x;
            }
            std::cout << "The enemy state is Jumping for the animation check. " << std::endl;
        }
        else if (currentState == EnemyState::Dead) {
            // Increment the frame index only if it is not at the last frame for jumping
            std::cout << "The enemy state is dead for the animation check. " << std::endl;
            if (currentFrame.x < totalFrames - 1) {
                currentFrame.x++;
                deathFrameRect.left += deathFrameSize.x;
                std::cout << "The current frame is being incremented for the death animation." << std::endl;
            }
        }
            // For walking animations proceed normally
       else {
            currentFrame.x++;
            std::cout << "The current frame is being incremented. " << std::endl;
            legsFrameRect.left += frameSize.x;

            // Reset to the first frame if it exceeds the total frames for the animation
            if (currentFrame.x >= totalFrames) {
                currentFrame.x = 0;
                legsFrameRect.left = 0; // Reset legs animation frame
            }
        }

        // Update the texture rectangles to the new frame

        legsFrameRect.left = currentFrame.x * frameSize.x;
    }

    // if the player is moving in a direction make sure that the legs are pointing in that direction
    if (velocity.x < 0.f) {
        // Moving left
        std::cout << "The Enemy is moving left. " << std::endl;
        legsSprite.setScale(-1.f, 1.f); // Flip horizontally
    } else if (velocity.x > 0.f) {
        // Moving right
        std::cout << "The Enemy is moving right. " << std::endl;
        legsSprite.setScale(1.f, 1.f); // Default scale
    }

    // Apply the updated texture rectangles
    legsSprite.setTextureRect(legsFrameRect);
    deathSprite.setTextureRect(deathFrameRect);

    // debugging
    std::cout << "Legs Frame Rect: Left=" << legsFrameRect.left
              << ", Top=" << legsFrameRect.top
              << ", Width=" << legsFrameRect.width
              << ", Height=" << legsFrameRect.height << std::endl;
}

// Funciton that will aim the weapon and sprites of the enemy to a given pointer position,
// ** have a function that handles the position that is aimed at
void Enemy::updateAim(const sf::Vector2f &pointerPosition) {
    sf::Vector2f torsoPosition = position + torsoOffset; // Anchor point for the torso

    // Flip the head and torso to point in the direction that the mouse is in either forward or backward
    isFlipped = pointerPosition.x < torsoPosition.x;

    // Flip the torso and head
    torsoSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    headSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    armsSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    leftArmsSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    deathSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);

    sf::Vector2f adjustedArmsOffset = armsOffset;
    if (isFlipped) {
        adjustedArmsOffset.x = -armsOffset.x; // Invert the x-offset for flipping
    }

    sf::Vector2f leftAdjustedArmsOffset = leftArmsOffset;
    if (isFlipped) {
        leftAdjustedArmsOffset.x = -leftArmsOffset.x; // Invert the x-offset for flipping
    }

    sf::Vector2f adjustedHeadOffset = headOffset;
    if (isFlipped) {
        adjustedHeadOffset.x = -adjustedHeadOffset.x; // Flip the arms offset
    }

    // Calculate the angle between the player's position and the mouse
    sf::Vector2f swivelPoint = position + adjustedArmsOffset;
    sf::Vector2f leftSwivelPoint = position + leftAdjustedArmsOffset;
    sf::Vector2f headSwivelPoint = position + adjustedHeadOffset;

    // Update the position of the arms sprite
    armsSprite.setPosition(swivelPoint);
    leftArmsSprite.setPosition(leftSwivelPoint);
    headSprite.setPosition(headSwivelPoint);

    // Calculate the direction vector and angle
    sf::Vector2f headDirectionToMouse = pointerPosition - swivelPoint;
    sf::Vector2f leftDirectionToMouse = pointerPosition - leftSwivelPoint;
    sf::Vector2f directionToMouse = pointerPosition - headSwivelPoint;
    // Define angle and head angle

    float angle = atan2(directionToMouse.y, directionToMouse.x) * 180.f / M_PI;
    float headAngle = atan2(headDirectionToMouse.y, headDirectionToMouse.x) * 180.f / M_PI;
    float leftArmAngle = atan2(headDirectionToMouse.y, headDirectionToMouse.x) * 180.f / M_PI;

    float minHeadAngle = -60.f; // Minimum allowed angle for head
    float maxHeadAngle = 30.f;

    if (isFlipped) {
        // Mirror the angle for the head
        headAngle += 180.f;
        angle += 180.f;
        leftArmAngle += 180.f;

        // Normalize headAngle to [-180, 180]
        while (headAngle > 180.f) headAngle -= 360.f;
        while (headAngle < -180.f) headAngle += 360.f;

        // Set the flipped clamping range
        minHeadAngle = -30.f;
        maxHeadAngle = 60.f;
    }

    // Aim the equipped weapon
    // Apply recoil to aiming angle
    float recoilOffset = currentWeapon->getCurrentRecoil();
    angle += recoilOffset;
    leftArmAngle += recoilOffset;
    currentWeapon->aim(angle, position + adjustedArmsOffset, isFlipped);

    float clampedHeadAngle = std::max(minHeadAngle, std::min(headAngle, maxHeadAngle));

    // Rotate the arms and head towards the mouse
    armsSprite.setRotation(angle); // Arms follow full range
    leftArmsSprite.setRotation(leftArmAngle);
    headSprite.setRotation(clampedHeadAngle); // Head is limited

    // handle aim of weapons:
    currentWeapon->aim(angle, position + adjustedArmsOffset, isFlipped);
}

void Enemy::updateHitboxes() {
    // Update positions of each body part relative to the player base position
    torsoSprite.setPosition(position + torsoOffset);
    headSprite.setPosition(position + headOffset);
    armsSprite.setPosition(position + armsOffset);
    leftArmsSprite.setPosition(position + armsOffset);
    legsSprite.setPosition(position + legsOffset);

    sf::FloatRect headBounds = headSprite.getGlobalBounds();
    sf::FloatRect torsoBounds = torsoSprite.getGlobalBounds();
    sf::FloatRect armsBounds = armsSprite.getGlobalBounds();
    // sf::FloatRect leftArmsBounds = armsSprite.getGlobalBounds(); // Right now both the left arm and the right arms have the same location and dimensions.
    sf::FloatRect legsBounds = legsSprite.getGlobalBounds();

    headHitbox = sf::FloatRect(
            headSprite.getPosition().x -10,
            headSprite.getPosition().y -20,
            headBounds.width -10,
            headBounds.height -10
    );

    torsoHitbox = sf::FloatRect(
            torsoSprite.getPosition().x -15,
            torsoSprite.getPosition().y -15,
            torsoBounds.width - 10,
            torsoBounds.height - 20
    );

    legsHitbox = sf::FloatRect(
            legsSprite.getPosition().x - 20,
            legsSprite.getPosition().y - 7,
            legsBounds.width - 50,
            legsBounds.height - 10
    );

    // FeetHitbox is already updated, maybe move it here

    // Find the bounding rectangle that encapsulates all body parts
    float left = std::min({torsoBounds.left, headBounds.left, armsBounds.left, legsBounds.left});
    float top = std::min({torsoBounds.top, headBounds.top, armsBounds.top, legsBounds.top});
    float right = std::max({torsoBounds.left + torsoBounds.width, headBounds.left + headBounds.width,
                            armsBounds.left + armsBounds.width, legsBounds.left + legsBounds.width});
    float bottom = std::max({torsoBounds.top + torsoBounds.height, headBounds.top + headBounds.height,
                             armsBounds.top + armsBounds.height, legsBounds.top + legsBounds.height});

    // Update the main hitbox to encompass all body parts
    hitbox = sf::FloatRect(left, top, right - left, bottom - top);

    std::cout << " position " << position.x << position.y << std::endl;

    // Update feet hitbox for ground detection
    feetHitbox = sf::FloatRect(
            hitbox.left,                               // Same x-position as the main hitbox
            hitbox.top + hitbox.height - 5.f,         // Bottom edge of the hitbox minus a small height
            hitbox.width,                             // Same width as the main hitbox
            5.f                                       // Small height for ground detection
    );
}

void Enemy::updateWeapons(float deltaTime) {
   currentWeapon->update(deltaTime, position, isFlipped);
}

void Enemy::updateAi(float deltaTime, Player& player) {
    switch (currentState) {
        case EnemyState::Idle:
            handleIdleState(deltaTime, player);
            break;

        case EnemyState::Patrolling:
            handlePatrollingState(deltaTime, player);
            break;

        case EnemyState::Pursuing:
            handlePursuingState(deltaTime, player);
            break;

        case EnemyState::Attacking:
            handleAttackingState(deltaTime, player);
            break;

        case EnemyState::Cooldown:
            handleCooldownState(deltaTime,player);
            break;
    }
}

void Enemy::handleIdleState(float deltaTime, const Player& player) {
    // Example: Transition to Pursuing if the player is detected
    if (detectPlayer(player)) {
        currentState = EnemyState::Pursuing;
    }
}

float Enemy::distanceTo(const sf::Vector2f& targetPoint) const {
    float dx = targetPoint.x - position.x;
    float dy = targetPoint.y - position.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Enemy::drawPatrolPoints(sf::RenderWindow& window) const {
    for (const auto& point : patrolPoints) {
        sf::CircleShape patrolPointShape(5.f); // Create a small circle with radius 5
        patrolPointShape.setFillColor(sf::Color::Green); // Set color for visibility
        patrolPointShape.setPosition(point.x - patrolPointShape.getRadius(), point.y - patrolPointShape.getRadius()); // Center the shape
        window.draw(patrolPointShape); // Draw the shape
    }
}

void Enemy::handlePatrollingState(float deltaTime, const Player& player) {
    if (patrolPoints.empty()) {
        return; // No patrol points defined
    }

    sf::Vector2f targetPoint = patrolPoints[currentPatrolIndex];
    sf::Vector2f offset = {0,-9};
    aimPointer = {patrolPoints[currentPatrolIndex].x, currentWeapon->getPosition().y + offset.y};
    updateAim(aimPointer);
    moveTo(targetPoint, deltaTime); // Move towards the current patrol point

    std::cout << "Current Patrol index" << currentPatrolIndex << std::endl;
    // Check if reached the patrol point
    if (distanceTo(targetPoint) < 70.f) { // Small threshold

        currentPatrolIndex = (currentPatrolIndex + 1) % patrolPoints.size(); // Loop to next point
        std::cout << "Patrol point reached." << std::endl;
    }

    // Detect the player during patrolling
    if (detectPlayer(player)) {
        std::cout << "Player detected! " << std::endl;
        currentState = EnemyState::Pursuing;
    }
}

sf::Vector2f normalizeVector(const sf::Vector2f& vector) {
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0) {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return sf::Vector2f(0.f, 0.f); // Return zero vector if the length is zero
}

bool Enemy::detectPlayer(const Player& player) {
    sf::Vector2f directionToPlayer = player.getPosition() - position; // Use enemy position for distance
    float distance = std::sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);

    if (distance > fovDistance) {
        return false; // Player is out of detection range
    }

// Normalize direction for FOV checks (optional, if you need directional logic)
    sf::Vector2f normalizedDirection = {directionToPlayer.x / distance, directionToPlayer.y / distance};
    sf::Vector2f normalizedAimDirection = {aimPointer.x - position.x, aimPointer.y - position.y};
    float aimLength = std::sqrt(normalizedAimDirection.x * normalizedAimDirection.x + normalizedAimDirection.y * normalizedAimDirection.y);
    normalizedAimDirection.x /= aimLength;
    normalizedAimDirection.y /= aimLength;

// Check if player is within the FOV angle
    float dotProduct = normalizedDirection.x * normalizedAimDirection.x + normalizedDirection.y * normalizedAimDirection.y;
    float angle = std::acos(dotProduct) * 180.f / M_PI;

    if (angle > fovAngle / 2.f) {
        return false; // Player is outside the FOV
    }

    return true;
}

void Enemy::handlePursuingState(float deltaTime, const Player& player) {
    moveTo(player.getPosition(), deltaTime);

    // Check if within attack range
    if (distanceTo(player.getPosition()) <= attackRange) {
        currentState = EnemyState::Attacking;
    }

    // If the player moves out of FOV, return to patrolling
    // implement a cooldown
    /*if (!detectPlayer(player)) {
        currentState = EnemyState::Patrolling;
    }*/
}

void Enemy::attackPlayer(Player& player, float deltaTime) {


    // Determine attack type
    if (currentWeapon) { // Ranged attack
        if (currentWeapon->isOutOfAmmo()) {
            reloadWeapon();
            return; // Cannot attack while reloading
        }

        // Aim at the player
        sf::Vector2f directionToPlayer = player.getPosition() - position;
        float distance = std::sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
        directionToPlayer /= distance; // Normalize direction

        currentWeapon->fire(directionToPlayer, position, position + weaponOffset, isFlipped);
        // Trigger attack animation
        currentState = EnemyState::Attacking;

    } else { // Melee attack
        if (distanceTo(player.getPosition()) <= meleeRange) {
            player.applyDamage(meleeDamage);
            currentState = EnemyState::Attacking;
        }
    }
}

void Enemy::handleAttackingState(float deltaTime, Player& player) {
    velocity.x = 0;
    attackDurationTimer += deltaTime;

    aimAtPlayer(player.getPosition()); // Aim at the player
    attackPlayer(player, deltaTime);  // Fire or melee the player

    // If the player moves out of range, abort attacking and go back to pursuing
    if (distanceTo(player.getPosition()) > attackRange)
    {
        currentState = EnemyState::Pursuing; // Switch back to running/walking animation
        // Reset the duration so next time we enter Attacking, it starts fresh
        attackDurationTimer = 0.f;
    }

    if (attackDurationTimer >= attackDuration)
    {
        attackDurationTimer = 0.f;
        currentState= EnemyState::Cooldown;
    }
}

void Enemy::handleAlertedState(float deltaTime, const Player& player)
{
    // Aim at the player (to simulate reacting to the threat)
    aimAtPlayer(player.getPosition());

    // Increment the alert timer
    alertTimer += deltaTime;

    // If the alert delay has passed, transition to Attacking
    if (alertTimer >= alertDuration)
    {
        alertTimer = 0.f; // Reset for future alerts
        currentState = EnemyState::Attacking;
    }
}

void Enemy::handleCooldownState(float deltaTime, Player &player) {
    // If the player walked out of range, maybe we revert to Pursing or Idle
    // or you can keep them in AttackCooldown forcibly until the end of the cooldown
    if (distanceTo(player.getPosition()) > attackRange) {
        attackCooldownTimer = 0.f; // Reset for next time
        currentState = EnemyState::Pursuing;
        return;
    }

    // Count up
    attackCooldownTimer += deltaTime;

    if (attackCooldownTimer >= attackCooldown) {
        // Done cooling down => back to Attacking (start next burst)
        attackCooldownTimer = 0.f;
        currentState = EnemyState::Attacking;
    }
}

void Enemy::returnToPatrol() {
    currentState = EnemyState::Patrolling;
}

void Enemy::moveLeft(float deltaTime) {
    velocity.x = -speed; // Move left
}

void Enemy::moveRight(float deltaTime) {
    velocity.x = speed;  // Move right
}

void Enemy::jump() {
    if (!isJumping && !isFalling) {
        velocity.y = -jumpHeight;  // Jump up (negative y-axis)
        isJumping = true;
        isFalling = true;
    }
}

void Enemy::duck() {
    isDucking = true;
}

void Enemy::fireCurrentWeapon(const sf::Vector2<float> &direction, const sf::Vector2<float> &swivelPoint) {
    sf::Vector2f adjustedArmsOffset = armsOffset;
    if (isFlipped) {
        adjustedArmsOffset.x = -armsOffset.x; // Invert the x-offset for flipping
    }
    currentWeapon->fire(direction, position, position + adjustedArmsOffset, isFlipped);
}

void Enemy::applyDamage(float amount) {
    if (!alive) {
        return;
    }
    if (amount > 0) {
        health -= static_cast<int>(amount);
        if (health <= 0) {
            health = 0;
            alive = false;
            //playerHealthState = PlayerHealthState::Dead;
        } else if (health < maxHealth * 0.25f) {
            //playerHealthState = PlayerHealthState::Dying;
        } else if (health < maxHealth * 0.75f) {
            //playerHealthState = PlayerHealthState::RoughedUp;
        } else {
            //playerHealthState = PlayerHealthState::Happy;
        }
    }
}

void Enemy::handleDeath() {
    alive = false;
    velocity.x = 0;
    currentFrame = {0,0};
    currentState = EnemyState::Dead;
    // Hide existing sprites
    torsoSprite.setColor(sf::Color(255, 255, 255, 0)); // Make transparent
    headSprite.setColor(sf::Color(255, 255, 255, 0));
    armsSprite.setColor(sf::Color(255, 255, 255, 0));
    legsSprite.setColor(sf::Color(255, 255, 255, 0));

    // Load the death animation sheet
    if (!deathTexture.loadFromFile("../assets/enemy/death_animation.png")) {
        std::cerr << "Failed to load death animation texture\n";
    }
    deathSprite.setTexture(deathTexture);

    // Set initial frame for death animation
    deathSprite.setTextureRect(deathFrameRect);
    sf::Vector2f offset = {-17,-43};
    deathSprite.setPosition(position + offset); // Position where the enemy was
    // play death animation
    // delete the enemy

    // debugging:
    std::cout << "Enemy has died." << std::endl;
}

int Enemy::getHealth() const {
    return health;
}

// Health State Management
EnemyHealthState Enemy::getHealthState() const {
    return enemyHealthState;
}

void Enemy::setHealth(int newHealth) {
    if (newHealth < 0) {
        health = 0;
        alive = false;
        //setHealthState(PlayerHealthState::Dying);  // Set state to Dying
    } else if (newHealth > maxHealth) {
        health = maxHealth;
    } else {
        health = newHealth;
    }

    // Update health state based on current health
    if (health >= maxHealth * 0.75f) {
        //setHealthState(PlayerHealthState::Happy);
    } else if (health >= maxHealth * 0.25f) {
        //setHealthState(PlayerHealthState::RoughedUp);
    } else if (health >= 1) {
        //setHealthState(PlayerHealthState::Dying);
    } else {
        //setHealthState(PlayerHealthState::Dead);
    }
}

void Enemy::addWeapon(std::shared_ptr<Weapon> &weapon) {
    currentWeapon = weapon;
}

sf::FloatRect Enemy::getHitbox() const {
    return hitbox;
}

sf::FloatRect Enemy::getHeadHitBox() const {
    return headHitbox;
}

sf::FloatRect Enemy::getTorsoHitBox() const {
    return torsoHitbox;
}

sf::FloatRect Enemy::getLegsHitbox() const {
    return legsHitbox;
}

sf::FloatRect Enemy::getFeetHitbox() const {
    return feetHitbox;
}

void Enemy::setfovDistance(float newFovDistance) {
    fovDistance = newFovDistance;
}

// Getters
EnemyType Enemy::getType() const {
    return type;
}

EnemyClass Enemy::getClass() const {
    return enemyClass;
}

EnemyFaction Enemy::getFaction() const {
    return faction;
}

bool Enemy::isAlive() const {
    return alive;
}

EnemyState Enemy::getCurrentState() const {
    return currentState;
}

void Enemy::applyDamage(int damageValue) {
    if (!alive) {
        return;
    }
    health -= damageValue;

    // Detect the player
    currentState = EnemyState::Pursuing;
    std::cout << "Damage is being applied to an enemy. Damage value: " << damageValue << std::endl;
    if (health <= 0) {
        handleDeath();
    }
}

void Enemy::applyStatusEffect(StatusEffect effect, float duration) {
    statusEffectManager.applyStatusEffect(effect, duration);
}

void Enemy::setPatrolRoute(const std::vector<sf::Vector2f>& newPatrolPoints) {
    patrolPoints = newPatrolPoints;
}


// Logic to advance toward the player if they are hiding or out of sight
void Enemy::advanceTowardPlayer(const Player& player, float deltaTime) {
    // Move toward the player's current position
    moveTo(player.getPosition(), deltaTime);
    currentState = EnemyState::Pursuing;
}

// Firing weapon at the player
void Enemy::fireWeapon(const Player& player) {/*
    if (ammo > 0) {
        // Fire at the player (you can add more logic for accuracy, etc.)
        // Example: reduce player's health
        player.applyDamage(damage);
        ammo--;
    } else {
        reloadWeapon();
    }*/
}



// Reload the weapon when out of ammo
void Enemy::reloadWeapon() {
    currentState = EnemyState::Reloading;
    // Add some logic for reloading time
    ammo = 10;  // Example ammo reload capacity
    currentState = EnemyState::Attacking;  // Resume attacking after reload
}

// Taking cover after being under fire
void Enemy::takeCover() {
    currentState = EnemyState::TakingCover;
    // Logic to find cover (could be a nearby position or object)
    // Move toward the cover position
}

// Melee attack when the player is in close range
void Enemy::meleeAttack(Player& player) {
    if (currentState == EnemyState::MeleeAttack) {
        // Apply melee damage to the player
        player.applyDamage(damage * 2);  // Example: melee does more damage
    }
}

// Search for the player after losing sight
void Enemy::searchForPlayer(float deltaTime) {
    // Logic to search the area for the player
    // If player is not found after a set time, go back to patrolling
    currentState = EnemyState::Patrolling;
}

void Enemy::aimAtPlayer(const sf::Vector2f& playerPosition) {
    aimPointer = playerPosition;
    updateAim(playerPosition);
}

/* Update the logic.
// Move the enemy
void Enemy::move(float deltaTime) {
    // Use velocity and deltaTime to move the enemy sprite
    position += velocity * deltaTime;
    enemySprite.setPosition(position);
}
*/

// Rendering the enemy
void Enemy::render(sf::RenderWindow& window) {
    if (currentState == EnemyState::Dead) {
        window.draw(deathSprite);
    }
    else {
        window.draw(enemySprite);
        // render the parts of the player
        window.draw(leftArmsSprite); // the left arms first
        window.draw(torsoSprite); // Then torso
        window.draw(legsSprite);  // Draw legs first (background layer)
        window.draw(headSprite);  // Then head
        window.draw(armsSprite);  // Then right arms on top
        if (currentWeapon != nullptr) {
            currentWeapon->render(window, position, isFlipped);
        }
    }

    // Debugging ---------------------------------------

    // Draw feetHitbox for debugging
    sf::RectangleShape feetDebug(sf::Vector2f(feetHitbox.width, feetHitbox.height));
    feetDebug.setPosition(feetHitbox.left, feetHitbox.top);
    feetDebug.setFillColor(sf::Color::Transparent);
    feetDebug.setOutlineColor(sf::Color::Red);
    feetDebug.setOutlineThickness(1.f);
    //window.draw(feetDebug); // comment out this out to hide the feet hitbox

    sf::RectangleShape hitBoxDebug(sf::Vector2f(hitbox.width, hitbox.height));
    hitBoxDebug.setPosition(hitbox.left, hitbox.top);
    hitBoxDebug.setFillColor(sf::Color::Transparent);
    hitBoxDebug.setOutlineColor(sf::Color::Red);
    hitBoxDebug.setOutlineThickness(1.f);
    //window.draw(hitBoxDebug); // comment out this out to hide the feet hitbox

    sf::RectangleShape headHitboxDebug(sf::Vector2f(headHitbox.width, headHitbox.height));
    headHitboxDebug.setPosition(headHitbox.left, headHitbox.top);
    headHitboxDebug.setFillColor(sf::Color::Transparent);
    headHitboxDebug.setOutlineColor(sf::Color::Red);
    headHitboxDebug.setOutlineThickness(1.f);
    //window.draw(headHitboxDebug); // comment out this out to hide the feet hitbox

    sf::RectangleShape torsoHitBoxDebug(sf::Vector2f(torsoHitbox.width, torsoHitbox.height));
    torsoHitBoxDebug.setPosition(torsoHitbox.left, torsoHitbox.top);
    torsoHitBoxDebug.setFillColor(sf::Color::Transparent);
    torsoHitBoxDebug.setOutlineColor(sf::Color::Red);
    torsoHitBoxDebug.setOutlineThickness(1.f);
    //window.draw( torsoHitBoxDebug); // comment out this out to hide the feet hitbox

    sf::RectangleShape legsHitBoxDebug(sf::Vector2f(legsHitbox.width, legsHitbox.height));
    legsHitBoxDebug.setPosition(legsHitbox.left, legsHitbox.top);
    legsHitBoxDebug.setFillColor(sf::Color::Transparent);
    legsHitBoxDebug.setOutlineColor(sf::Color::Red);
    legsHitBoxDebug.setOutlineThickness(1.f);
    //window.draw( legsHitBoxDebug);

    // Debug dot for the swivel point of right arm
    sf::CircleShape rightArmDebug(1.f); // Radius of the circler
    rightArmDebug.setFillColor(sf::Color::Red); // Distinct color for visibility
    rightArmDebug.setPosition(position + armsOffset); // Swivel point calculation
    //window.draw(rightArmDebug);

    // Debug dot for the swivel point of the left arm
    sf::CircleShape leftArmDebug(1.f);                    // Radius of circle
    leftArmDebug.setFillColor(sf::Color::Red);            // Make it red for visibility
    leftArmDebug.setPosition(position + leftArmsOffset);       // Use the sprite's current world position
    //window.draw(leftArmDebug);

    // Debug dot for the swivel point of the head
    sf::CircleShape headDebug(1.f);                    // Radius of circle
    headDebug.setFillColor(sf::Color::Red);            // Make it red for visibility
    headDebug.setPosition(position + headOffset);       // Use the sprite's current world position
    //window.draw(headDebug);
}

void Enemy::setWeaponAmmo(int newAmmo) {
    if (currentWeapon != nullptr) {
        currentWeapon->setAmmo(newAmmo);
    }
}

std::shared_ptr<Weapon> Enemy::getCurrentWeapon() const {
    return currentWeapon;
}

std::vector<std::shared_ptr<Projectile>> Enemy::getAllProjectiles() const {
    std::vector<std::shared_ptr<Projectile>> allProjectiles;
    if (currentWeapon != nullptr) {
        const auto& weaponProjectiles = currentWeapon->getProjectiles();
        allProjectiles.insert(allProjectiles.end(), weaponProjectiles.begin(), weaponProjectiles.end());
    }

    return allProjectiles;
}

// Play the death animation (can be expanded based on enemy type)
void Enemy::playDeathAnimation() {
    // Logic for playing different death animations
    // Example: falling over, disintegration, etc.
}

// Private helper function to move to a specific point
void Enemy::moveTo(const sf::Vector2f& targetPoint, float deltaTime) {
    float distanceX = targetPoint.x - position.x;

    if (distanceX > 0.1f) {
        // Move right
        moveRight(deltaTime);
    } else if (distanceX < -0.1f) {
        // Move left
        moveLeft(deltaTime);
    } else {
        // Stop horizontal movement when close enough
        velocity.x = 0.f;
    }

    // Jumping logic (if needed, e.g., to reach a platform)
    /*if (shouldJump()) { // Implement shouldJump logic if required
        jump();
    }*/

    // Gravity effect
    if (!isJumping) {
        velocity.y += gravity * deltaTime; // Apply gravity
    }

    // Update position
    position += velocity * deltaTime;
    enemySprite.setPosition(position);

    // Reset velocity for next frame (if needed)
    if (std::abs(velocity.x) > 0.f && std::abs(distanceX) < 0.1f) {
        velocity.x = 0.f;
    }
}

