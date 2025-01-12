//
// Created by Leland Sion on 2024-10-09.
//
//
// add shells to the weapon firing animations
// add a method that adds visuals to the hitboxes etc. add a jumping animation, and an in air animation,
// think about whether you want in air movement
// clean up the rendering pipeline
// and implement the walking animation
// update teh move, copy constructors to follow the main constructors
// align all animations, make sure that there is a jumping animation and the right animations play at their right time
// align teh walking speed with the animation, modify the jumping height for testing or looks etc.
#include "Player.h"
#include "iostream"

Player::Player()
    : position(100.f, 300.f), velocity(0.f, 0.f), speed(200.f), jumpHeight(300.f),
      maxHealth(100), health(100), isAlive(true), isJumping(false), isFalling(true),
      isDucking(false), playerHealthState(PlayerHealthState::Happy), playerState(PlayerState::Idle),
      playerMovementDirection(PlayerMovementDirection::None), levelScore(0), grossScore(0),
      kills(0), headshots(0), deaths(0), gravity(981.f), maxFallSpeed(600.f), currentWeaponIndex(0) {

    if (!playerTexture.loadFromFile("assets/player1.png")) {
        std::cout << "Player texture not found.";
    }
    playerSprite.setTexture(playerTexture);
    frameRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
    legsFrameRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
    playerSprite.setTextureRect(frameRect);
    playerSprite.setPosition(position);
    playerSprite.setPosition(position);
    updateHitboxes();
}

Player::Player(sf::Vector2f startPosition, float initialSpeed, int initialHealth)
        : position(startPosition), velocity(0.f, 0.f), speed(initialSpeed), jumpHeight(300.f),
          maxHealth(initialHealth), health(initialHealth), isAlive(true), isJumping(false), isFalling(true),
          isDucking(false), playerHealthState(PlayerHealthState::Happy), playerMovementDirection(PlayerMovementDirection::Right),
          playerAction(PlayerAction::None), levelScore(0), grossScore(0),
          kills(0), headshots(0), deaths(0), gravity(981.f), maxFallSpeed(600.f), currentWeaponIndex(0),
          stateDelay(0.1f),frameSize(116, 116), deathFrameSize(94,101), frameTime(0.1f), elapsedTime(0.f), currentFrame(0, 0),
          torsoOffset(0.f, 0.f), headOffset(0.f, -13.f), armsOffset(-11.f, -4.f), leftArmsOffset(-1.f, -4.f), legsOffset(0.f,  25.f)// Default animation setup

{
    // TODO: move the playertexture loading from files into the initialize player/sprite function

    // Load textures
    if (!torsoTexture.loadFromFile("../assets/player/torso.png")) {
        std::cerr << "Failed to load torso texture\n";
    }
    if (!headTexture.loadFromFile("../assets/player/player1_head2.png")) {
        std::cerr << "Failed to load head texture\n";
    }
    if (!armsTexture.loadFromFile("../assets/player/player1_arms_right.png")) {
        std::cerr << "Failed to load arms texture\n";
    }
    if (!leftArmsTexture.loadFromFile("../assets/player/player1_arms_left.png")) {
        std::cerr << "Failed to load arms texture\n";
    }
    if (!legsTexture.loadFromFile("../assets/player/legs_spritesheet.png")) {
        std::cerr << "Failed to load legs texture\n";
    }

    // Initialize sprites
    torsoSprite.setTexture(torsoTexture);
    headSprite.setTexture(headTexture);
    armsSprite.setTexture(armsTexture);
    leftArmsSprite.setTexture(armsTexture);
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

Player::Player(const Player &other)
        : position(other.position), velocity(other.velocity), speed(other.speed), jumpHeight(other.jumpHeight),
          maxHealth(other.maxHealth), health(other.health), isAlive(other.isAlive), isJumping(other.isJumping),
          isFalling(other.isFalling), isDucking(other.isDucking), playerHealthState(other.playerHealthState),
          playerState(other.playerState), playerMovementDirection(other.playerMovementDirection),
          playerAction(other.playerAction), playerWeaponState(other.playerWeaponState),
          playerArmorType(other.playerArmorType), playerInventoryType(other.playerInventoryType),
          playerClass(other.playerClass), levelScore(other.levelScore), grossScore(other.grossScore),
          kills(other.kills), headshots(other.headshots), deaths(other.deaths),
          gravity(other.gravity), maxFallSpeed(other.maxFallSpeed), currentWeaponIndex(other.currentWeaponIndex) {

    playerTexture = other.playerTexture;
    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(other.playerSprite.getPosition());
    updateHitboxes();
}

Player::Player(Player &&other) noexcept
        : position(std::move(other.position)), velocity(std::move(other.velocity)), speed(other.speed),
          jumpHeight(other.jumpHeight), maxHealth(other.maxHealth), health(other.health),
          isAlive(other.isAlive), isJumping(other.isJumping), isFalling(other.isFalling),
          isDucking(other.isDucking), playerHealthState(std::move(other.playerHealthState)),
          playerState(std::move(other.playerState)), playerMovementDirection(std::move(other.playerMovementDirection)),
          playerAction(std::move(other.playerAction)), playerWeaponState(std::move(other.playerWeaponState)),
          playerArmorType(std::move(other.playerArmorType)), playerInventoryType(std::move(other.playerInventoryType)),
          playerClass(std::move(other.playerClass)), levelScore(other.levelScore), grossScore(other.grossScore),
          kills(other.kills), headshots(other.headshots), deaths(other.deaths),
          gravity(other.gravity), maxFallSpeed(other.maxFallSpeed), currentWeaponIndex(other.currentWeaponIndex) {

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

// Initialize sprite
void Player::initializeSprite(sf::Sprite &sprite, const sf::Texture &texture, const sf::Vector2f &offset, bool isAnimated) {
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
    sf::Vector2f headPositionInTexture = {9.f, 17.f};

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
    else {
        sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    }

    // Position the sprite relative to the player
    sprite.setPosition(position + offset);
}

// Render all parts of the player
void Player::render(sf::RenderWindow &window) {

    if (!isAlive) {
        window.draw(deathSprite);
    }
    else {
        // render the parts of the player
        window.draw(leftArmsSprite); // the left arms first
        window.draw(torsoSprite); // Then torso
        window.draw(legsSprite);  // Draw legs first (background layer)
        window.draw(headSprite);  // Then head
        if (currentWeaponIndex >= 0 && currentWeaponIndex < weapons.size() && weapons[currentWeaponIndex] != nullptr) { // then the weapon
            // the projectile renderings could be attached to the level maybe
            // weapons[currentWeaponIndex]->renderProjectiles(window);
            weapons[currentWeaponIndex]->render(window, position, isFlipped);
        }
        window.draw(armsSprite);  // Then right arms on top
    }

    // Debugging ---------------------------------------

    // Draw feetHitbox for debugging
    sf::RectangleShape feetDebug(sf::Vector2f(feetHitbox.width, feetHitbox.height));
    feetDebug.setPosition(feetHitbox.left, feetHitbox.top);
    feetDebug.setFillColor(sf::Color::Transparent);
    feetDebug.setOutlineColor(sf::Color::Red);
    feetDebug.setOutlineThickness(1.f);
    //window.draw(feetDebug); // comment out this out to hide the feet hitbox

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
    // window.draw(headDebug);

    // Debugging (optional): Visualize the hitboxes
    sf::RectangleShape torsoDebugShape(sf::Vector2f(torsoHitbox.width, torsoHitbox.height));
    torsoDebugShape.setPosition(torsoHitbox.left, torsoHitbox.top);
    torsoDebugShape.setFillColor(sf::Color::Transparent);
    torsoDebugShape.setOutlineColor(sf::Color::Blue); // Different color for torso
    torsoDebugShape.setOutlineThickness(1.f);
    //window.draw(torsoDebugShape);

// Debugging: Visualize the head hitbox
    sf::RectangleShape headDebugShape(sf::Vector2f(headHitbox.width, headHitbox.height));
    headDebugShape.setPosition(headHitbox.left, headHitbox.top);
    headDebugShape.setFillColor(sf::Color::Transparent);
    headDebugShape.setOutlineColor(sf::Color::Green); // Different color for head
    headDebugShape.setOutlineThickness(1.f);
    //window.draw(headDebugShape);

// Debugging: Visualize the legs hitbox
    sf::RectangleShape legsDebugShape(sf::Vector2f(legsHitbox.width, legsHitbox.height));
    legsDebugShape.setPosition(legsHitbox.left, legsHitbox.top);
    legsDebugShape.setFillColor(sf::Color::Transparent);
    legsDebugShape.setOutlineColor(sf::Color::Yellow); // Different color for legs
    legsDebugShape.setOutlineThickness(1.f);
    //window.draw(legsDebugShape);
}

// Consider making it possible to have generalizable keybindings
// *** make sure to check whether the weapon is valid before attempting to equip.
// Input Handling
void Player::handleInput(float deltaTime, const sf::RenderWindow &window) {
    bool isMoving = false;
    // Reset horizontal velocity to 0
    velocity.x = 0.f;

    // Handle movement
    // Consider having boolean statements in place of the if statements for more flexibility
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveLeft(1.f);  // Move left
        playerMovementDirection = PlayerMovementDirection::Left;
        if (playerState != PlayerState::Falling && playerState != PlayerState::Jumping) {
            playerState = PlayerState::Running;
            isMoving = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveRight(1.f);  // Move right
        playerMovementDirection = PlayerMovementDirection::Right;
        if (playerState != PlayerState::Falling && playerState != PlayerState::Jumping) {
            playerState = PlayerState::Running;
            isMoving = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!isJumping && !isFalling) {
            velocity.y -= jumpHeight;
            isJumping = true;
            isFalling = true;
            playerState = PlayerState::Jumping;
            isMoving = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        duck();
        isMoving = true;
        playerState = PlayerState::Crouching;
    }
    // Have a delay between changing to idle
    if (!isMoving) {
        idleDelayTimer += deltaTime;
        if (idleDelayTimer >= 0.2f) {
            playerState = PlayerState::Idle;
        }
    } else {
        idleDelayTimer = 0.f; // Reset idle timer when moving
    }

    // maybe make the if statements boolean values for more flexibility
    // incorporate a check that looks if their is an equipped weapon available
    // Handle weapon switching (e.g., pressing keys 1, 2, 3, ...)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        equipWeapon(0); // Equip the first weapon
        std::cout << "Weapon index is 0. \n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        equipWeapon(-1); // Equip the second weapon
        currentWeaponIndex = -1;
        std::cout << "Weapon index is 1. \n" << currentWeaponIndex;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        equipWeapon(2); // Equip the third weapon
        std::cout << "Weapon index is 2. \n";
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        equipWeapon(3); // Equip the fourth weapon
        std::cout << "Weapon index is 3.\n";
    }

    // handling firing/attacking
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    fireDelayTimer += deltaTime;
    if (isMousePressed && !weapons.empty() && currentWeaponIndex >= 0 && currentWeaponIndex < weapons.size()) {
        // Calculate the aim direction
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Get mouse position in screen coords
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition); // Convert to world coords
        sf::Vector2f direction = mouseWorldPosition - (position + headOffset); // Direction vector from player to mouse
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (magnitude != 0) direction /= magnitude; // Normalize the direction vector

        // Fire the weapon
        // Fireode logic is put here instead of in the weapon since mouses can be held and would result in many funciton calls
        // Change the swivel point to be accurate,
        // Default automatic fire behaviour:

        if (currentWeapon && currentWeapon->getFireMode() == FireMode::SingleFire && !mousePressed && currentWeapon->checkCanFire() && currentWeapon->getAmmo() > 0) {
            fireCurrentWeapon(direction, position + armsOffset);


        } else if (currentWeapon && currentWeapon->getFireMode() == FireMode::Automatic && currentWeapon->checkCanFire() && currentWeapon->getAmmo() > 0 && fireDelayTimer >= currentWeapon->getFireDelay()) {
            fireCurrentWeapon(direction, position + armsOffset);
            fireDelayTimer = 0;
        }
        mousePressed = isMousePressed;
    }

}

// handles movement and physics
void Player::updatePhysics(float deltaTime) {
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

void Player::updateEnvironmentInteraction(float deltaTime, const Environment& environment) {
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
// Make an animation manager
void Player::updateAnimation(float deltaTime) {
    int totalFrames = 0;
    elapsedTime += deltaTime;

    // Determine the current row of the sprite sheet based on the player's state
    switch (playerState) {
        case PlayerState::Idle:
            if (!isJumping && !isFalling) {
                currentFrame.y = 1; // Idle animation row
                legsFrameRect.top = 1 * frameSize.y; // Idle row for legs
                totalFrames = 5;    // Total frames for the idle animation
            }
            break;
        case PlayerState::Running:
            if (!isJumping && !isFalling) {
                currentFrame.y = 0; // Running animation row
                legsFrameRect.top = 0 * frameSize.y; // Running row for legs
                totalFrames = 8;    // Total frames for the running animation
            }  // Total frames for the running animation
            break;
        case PlayerState::Jumping:
            currentFrame.y = 2; // Assuming the third row (index 2) is for jumping animation
            legsFrameRect.top = 2 * frameSize.y; // Jumping row for legs
            totalFrames = 8;    // Total frames for the jumping animation
            break;
        case PlayerState::Falling:
            currentFrame.y = 2; // Assuming the third row (index 2) is for jumping animation
            legsFrameRect.top = 2 * frameSize.y; // Jumping row for legs
            totalFrames = 8;    // Total frames for the jumping animation
        case PlayerState::Dead:
            if (!isJumping && !isFalling) {
                totalFrames = 12;    // Total frames for the running animation
            }  // Total frames for the running animation
            break;
    }

    // Check if the falling state is necessary and whether or not the boolean jumping and states are necessary together

    // Start jump animation if needed
    if (playerState == PlayerState::Jumping && !jumpAnimationStarted) {
        jumpAnimationStarted = true;  // Start jump animation
        currentFrame.x = 0;           // Reset to the first frame
        legsFrameRect.left = 0;       // Reset texture to first frame
    }

    if (playerState == PlayerState::Falling && !jumpAnimationStarted) {
        jumpAnimationStarted = true;  // Falling can also trigger animation if needed
    }

    // Reset the jump animation when grounded
    if (isOnGround && jumpAnimationStarted) {
        jumpAnimationStarted = false;  // Reset the animation flag
        currentFrame.x = 0;            // Reset animation to first frame
        legsFrameRect.left = 0;
    }

    // Update the frame of the animation
    if (elapsedTime > frameTime) {
        elapsedTime = 0.f;
        // For jumping animations stop at the last frame
        if (playerState == PlayerState::Jumping || playerState == PlayerState::Falling) {
            // Increment the frame index only if it is not at the last frame for jumping
            if (currentFrame.x < totalFrames - 1) {
                currentFrame.x++;
                legsFrameRect.left += frameSize.x;
            }
        }
        else if (playerState == PlayerState::Dead) {
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
        legsSprite.setScale(-1.f, 1.f); // Flip horizontally
    } else if (velocity.x > 0.f) {
        // Moving right
        legsSprite.setScale(1.f, 1.f); // Default scale
    }

    // Apply the updated texture rectangles
    legsSprite.setTextureRect(legsFrameRect);
    //deathSpriate.setTextureRect(deathFrameRect);

    // debugging
    std::cout << "Legs Frame Rect: Left=" << legsFrameRect.left
              << ", Top=" << legsFrameRect.top
              << ", Width=" << legsFrameRect.width
              << ", Height=" << legsFrameRect.height << std::endl;
}

// Handle the aim of player sprites like head and arms towards the mouse, includes handling for weapon aiming
void Player::updateMouseAim(const sf::Vector2i &mousePosition, const sf::RenderWindow &window) {
    sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition);
    sf::Vector2f torsoPosition = position + torsoOffset; // Anchor point for the torso

    // Flip the head and torso to point in the direction that the mouse is in either forward or backward
    isFlipped = mouseWorldPosition.x < torsoPosition.x;

    // Flip the torso and head
    torsoSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    headSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    armsSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    leftArmsSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);

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
    sf::Vector2f headDirectionToMouse = mouseWorldPosition - swivelPoint;
    sf::Vector2f leftDirectionToMouse = mouseWorldPosition - leftSwivelPoint;
    sf::Vector2f directionToMouse = mouseWorldPosition - headSwivelPoint;
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
    if (!weapons.empty() && currentWeaponIndex >= 0 && currentWeaponIndex < weapons.size()) {
        // Apply recoil to aiming angle
        float recoilOffset = weapons[currentWeaponIndex]->getCurrentRecoil();
        angle += recoilOffset;
        leftArmAngle += recoilOffset;
        weapons[currentWeaponIndex]->aim(angle, position + adjustedArmsOffset, isFlipped);
    }

    float clampedHeadAngle = std::max(minHeadAngle, std::min(headAngle, maxHeadAngle));

    // Rotate the arms and head towards the mouse
    armsSprite.setRotation(angle); // Arms follow full range
    leftArmsSprite.setRotation(leftArmAngle);
    headSprite.setRotation(clampedHeadAngle); // Head is limited

    // handle aim of weapons:
    if (!weapons.empty() && currentWeaponIndex >= 0 && currentWeaponIndex < weapons.size()) {
        weapons[currentWeaponIndex]->aim(angle, position + adjustedArmsOffset, isFlipped);
    }
}

// Hitbox Management and updating positions
// consider using alpha channel for hitboxes
void Player::updateHitboxes() {
    // Update positions of each body part relative to the player base position
    torsoSprite.setPosition(position + torsoOffset);
    headSprite.setPosition(position + headOffset);
    armsSprite.setPosition(position + armsOffset);
    leftArmsSprite.setPosition(position + armsOffset);
    legsSprite.setPosition(position + legsOffset);

    sf::FloatRect torsoBounds = torsoSprite.getGlobalBounds();
    sf::FloatRect headBounds = headSprite.getGlobalBounds();
    sf::FloatRect armsBounds = armsSprite.getGlobalBounds();
    // sf::FloatRect leftArmsBounds = armsSprite.getGlobalBounds(); // Right now both the left arm and the right arms have the same location and dimensions.
    sf::FloatRect legsBounds = legsSprite.getGlobalBounds();

    headHitbox = sf::FloatRect(
            headSprite.getPosition().x -10,
            headSprite.getPosition().y -15,
            headBounds.width -10,
            headBounds.height -10
    );

    torsoHitbox = sf::FloatRect(
            torsoSprite.getPosition().x -15,
            torsoSprite.getPosition().y -10,
            torsoBounds.width - 10,
            torsoBounds.height - 10
    );

    legsHitbox = sf::FloatRect(
            legsSprite.getPosition().x - 25,
            legsSprite.getPosition().y - 7,
            legsBounds.width - 60,
            legsBounds.height - 50
    );

    // Find the bounding rectangle that encapsulates all body parts
    float left = std::min({torsoBounds.left, headBounds.left, armsBounds.left, legsBounds.left});
    float top = std::min({torsoBounds.top, headBounds.top, armsBounds.top, legsBounds.top});
    float right = std::max({torsoBounds.left + torsoBounds.width, headBounds.left + headBounds.width,
                            armsBounds.left + armsBounds.width, legsBounds.left + legsBounds.width});
    float bottom = std::max({torsoBounds.top + torsoBounds.height, headBounds.top + headBounds.height,
                             armsBounds.top + armsBounds.height, legsBounds.top + legsBounds.height});

    // Update the main hitbox to encompass all body parts
    hitbox = sf::FloatRect(left, top, right - left, bottom - top);


    // Update feet hitbox for ground detection
    feetHitbox = sf::FloatRect(
            hitbox.left,                               // Same x-position as the main hitbox
            hitbox.top + hitbox.height - 5.f,         // Bottom edge of the hitbox minus a small height
            hitbox.width,                             // Same width as the main hitbox
            5.f                                       // Small height for ground detection
    );


}

void Player::updateWeapons(float deltaTime) {
    for (auto& weapon : weapons) {
        if (weapon) {
            weapon->update(deltaTime, position, isFlipped);
        }
    }
}

// Update Player's State
void Player::updateStatusEffects(float deltaTime) {
    // Update active status effects
    statusManager.update(deltaTime);

    // Apply effects based on active statuses
    if (statusManager.hasStatusEffect(StatusEffect::Burning)) {
        applyDamage(5.f * deltaTime); // Example: lose health over time
    }
    if (statusManager.hasStatusEffect(StatusEffect::Regeneration)) {
        setHealth(getHealth() + 3.f * deltaTime); // Example: heal over time
    }
    // ...
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

void Player::fireCurrentWeapon(const sf::Vector2<float> &direction, const sf::Vector2<float> &swivelPoint) {
    sf::Vector2f adjustedArmsOffset = armsOffset;
    if (isFlipped) {
        adjustedArmsOffset.x = -armsOffset.x; // Invert the x-offset for flipping
    }
    weapons[currentWeaponIndex]->fire(direction, position, position + adjustedArmsOffset, isFlipped);
}

std::vector<std::shared_ptr<Weapon>> Player::getWeapons() {
    return weapons;
}

std::vector<std::shared_ptr<Projectile>> Player::getAllProjectiles() const {
    std::vector<std::shared_ptr<Projectile>> allProjectiles;

    for (const auto& weapon : weapons) {
        if (weapon) {
            const auto& weaponProjectiles = weapon->getProjectiles();
            allProjectiles.insert(allProjectiles.end(), weaponProjectiles.begin(), weaponProjectiles.end());
        }
    }

    return allProjectiles;
}

void Player::applyDamage(float amount) {
    std::cout << "Damage is being applied to the player. " << amount << std::endl;
    if (amount > 0) {
        health -= static_cast<int>(amount);
        if (health <= 0) {
            health = 0;
            isAlive = false;
            playerHealthState = PlayerHealthState::Dead;
            playerState = PlayerState::Dead;
            handleDeath();
        } else if (health < maxHealth * 0.25f) {
            playerHealthState = PlayerHealthState::Dying;
        } else if (health < maxHealth * 0.75f) {
            playerHealthState = PlayerHealthState::RoughedUp;
        } else {
            playerHealthState = PlayerHealthState::Happy;
        }
    }
}

// Handle the death of the player
void Player::handleDeath() {
    if (!isAlive) {

        // Deduct points or apply penalties
        levelScore -= 50; // Example penalty
        if (levelScore < 0) {
            levelScore = 0; // Ensure score doesn't go negative
        }

        isAlive = false;
        velocity.x = 0;
        currentFrame = {0, 0};

        // Hide existing sprites
        torsoSprite.setColor(sf::Color(255, 255, 255, 0)); // Make transparent
        headSprite.setColor(sf::Color(255, 255, 255, 0));
        armsSprite.setColor(sf::Color(255, 255, 255, 0));
        legsSprite.setColor(sf::Color(255, 255, 255, 0));

        // Load the death animation sheet
        if (!deathTexture.loadFromFile("../assets/player/grave_stone.png")) {
            std::cerr << "Failed to load death animation texture\n";
        }
        deathSprite.setTexture(deathTexture);

        // Set initial frame for death animation
        //deathSprite.setTextureRect(deathFrameRect);
        //sf::Vector2f offset = {-17, -52};
        sf::Vector2f offset = {-17, -10};
        deathSprite.setPosition(position + offset); // Position where the enemy was
        // play death animation
        // delete the enemy

        // debugging:
        std::cout << "Player has died!" << std::endl;
    }
}

// Health Management
int Player::getHealth() const {
    return health;
}

// Health State Management
PlayerHealthState Player::getHealthState() const {
    return playerHealthState;
}

void Player::setHealthState(PlayerHealthState newState) {
    playerHealthState = newState;
}

void Player::setHealth(int newHealth) {
    if (newHealth < 0) {
        health = 0;
        isAlive = false;
        setHealthState(PlayerHealthState::Dying);  // Set state to Dying
    } else if (newHealth > maxHealth) {
        health = maxHealth;
    } else {
        health = newHealth;
    }

    // Update health state based on current health
    if (health >= maxHealth * 0.75f) {
        setHealthState(PlayerHealthState::Happy);
    } else if (health >= maxHealth * 0.25f) {
        setHealthState(PlayerHealthState::RoughedUp);
    } else if (health >= 1) {
        setHealthState(PlayerHealthState::Dying);
    } else {
        setHealthState(PlayerHealthState::Dead);
    }
}

bool Player::checkAlive() const {
    return isAlive;
}

sf::Vector2f Player::getPosition() const {
    return position;
}

sf::Vector2f Player::getVelocity() const {
    return velocity;
}


// Movement State Management
PlayerMovementDirection Player::getMovementDirection() const {
    return playerMovementDirection;
}

void Player::setMovementDirection(PlayerMovementDirection newState) {
    playerMovementDirection = newState;
}

// Action State Management
PlayerAction Player::getActionState() const {
    return playerAction;
}

void Player::setActionState(PlayerAction newState) {
    playerAction = newState;
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

    // cdonsider auto equipping it
}

// make sure that all the currentWeaopon is always initialized
void Player::equipWeapon(int index) {
    if (index >= 0 && index < weapons.size()) {
        currentWeaponIndex = index;
        currentWeapon = weapons[index];
    } else {
        currentWeapon = nullptr;
    }
}

void Player::setWeaponAmmo(int weaponIndex, int newAmmo) {
    if (weaponIndex >= 0 && weaponIndex < weapons.size() && weapons[weaponIndex] != nullptr) {
        weapons[weaponIndex]->setAmmo(newAmmo);
    } else {
        std::cerr << "Invalid weapon index or weapon does not exist.\n";
    }
}

int Player::getCurrentWeaponIndex() {
    return currentWeaponIndex;
}

sf::FloatRect Player::getHitbox() const {
    return hitbox;
}

sf::FloatRect Player::getHeadHitBox() const {
    return headHitbox;
}

sf::FloatRect Player::getTorsoHitBox() const {
    return torsoHitbox;
}

sf::FloatRect Player::getLegsHitbox() const {
    return legsHitbox;
}

sf::FloatRect Player::getFeetHitbox() const {
    return feetHitbox;
}
