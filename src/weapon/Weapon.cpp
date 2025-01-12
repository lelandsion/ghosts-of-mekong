//
// Created by Leland Sion on 2024-10-16.
//

// TODO: add shells to the weapon firing animations
#include "Weapon.h"
#include <iostream>

// Constructor
Weapon::Weapon(const std::string& texturePath, const std::string& weaponName, float fireDelay, int damage, const std::string& projectileTexturePath, int maxAmmo, float projectileSpeed ,FireMode fireMode)
        : name(weaponName), ammo(maxAmmo), maxAmmo(maxAmmo), projectileSpeed(projectileSpeed), fireDelay(fireDelay), damage(damage), offset(-1.f,-5.f), fireMode(fireMode), timeSinceLastFire(0), canFire(true), currentRecoilAngle(0), recoilAngle(5.f), isReloading(false) {
    // Initialize weapon Sprite
    if (!weaponTexture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture for weapon: " << weaponName << std::endl;
    } else {
        std::cout << "Successfully bound texture to weapon sprite." << std::endl;
        weaponSprite.setTexture(weaponTexture);
    }
    if (!projectileTexture.loadFromFile(projectileTexturePath)) {
        std::cerr << "Failed to load projectile texture!" << std::endl;
        return;
    } else {
        std::cout << "Successfully bound texture for projectile." << std::endl;
    }
    // temporary:
    if (!projectileImpactTexture.loadFromFile("../assets/weapon/bullet_impact.png")) {
        std::cerr << "Failed to load projectileImpact texture!" << std::endl;
        return;
    } else {
        std::cout << "Successfully bound projectileImpactTexture for projectile." << std::endl;
    }
    if (!projectileEnemyImpactTexture.loadFromFile("../assets/weapon/bullet_enemy_impact.png")) {
        std::cerr << "Failed to load enemy projectileImpact texture!" << std::endl;
        return;
    } else {
        std::cout << "Successfully bound enemy projectileImpactTexture for projectile." << std::endl;
    }


    // temporary:
    bulletSpeed = 6000;
    recoilAngle = 5.f;
    recoilDuration = fireDelay;
    recoilTimer = 0;


    // Initialize muzzle Flash Sprite
    if (!muzzleFlashTexture.loadFromFile("../assets/weapon/muzzle_flash_AK47.png")) {
        std::cerr << "Failed to load muzzle flash texture" << std::endl;
    } else {
        muzzleFlashSprite.setTexture(muzzleFlashTexture);
    }

    // Set the origin of the sprite:
    // three parts of the location: the position = the swivel point which has the offset of the sprite, the origin which is the offset of the sprite from the swivel point,
    // add initializtion of the positions and origin here, of the sprites once then update the position in the update method
    // put all the rendering of the sprites in the render method where teh positions and origins are already set.
    // The origins are set once, the positions will update with the player,
    // centralize this logic somewhere
    sf::Vector2f weaponSpriteOffset = {20.f, 25.f}; // Adjust based on the sprite
    sf::Vector2f muzzleFlashSpriteOffset = {-48.f, 68.f}; // Adjust based on the sprite
    weaponSprite.setOrigin(weaponSpriteOffset);
    muzzleFlashSprite.setOrigin(muzzleFlashSpriteOffset);

    // may not need this initialization
    spawnPosition = {0,0};

    // put this in the constructor maybe
    muzzleFlashFrame = sf::IntRect(0, 0, 116, 116);
    muzzleFlashSprite.setTextureRect(muzzleFlashFrame);
}

// Copy constructor
Weapon::Weapon(const Weapon& other) {
    copyFrom(other);
}

// Move constructor
Weapon::Weapon(Weapon&& other) {
    moveFrom(std::move(other));
}

// Destructor
Weapon::~Weapon() {
    free();
}

// Copy assignment operator
Weapon& Weapon::operator=(const Weapon& other) {
    if (this != &other) {
        free();  // Free current resources
        copyFrom(other);
    }
    return *this;
}

// Move assignment operator
Weapon& Weapon::operator=(Weapon&& other) {
    if (this != &other) {
    free();  // Free current resources
    moveFrom(std::move(other));
    }
    return *this;
}


// Helper function to copy resources
void Weapon::copyFrom(const Weapon& other) {
    name = other.name;
    ammo = other.ammo;
    maxAmmo = other.maxAmmo;
    damage = other.damage;
    fireMode = other.fireMode;
    weaponCategory = other.weaponCategory;
    weaponType = other.weaponType;

    // Copy SFML objects
    fireSound = other.fireSound;
    reloadSound = other.reloadSound;
    emptyClipSound = other.emptyClipSound;
    weaponSprite = other.weaponSprite;
    weaponTexture = other.weaponTexture;
    weaponFrame = other.weaponFrame;
}

// Helper function to move resources
void Weapon::moveFrom(Weapon&& other) {
name = std::move(other.name);
ammo = other.ammo;
maxAmmo = other.maxAmmo;
damage = other.damage;
fireMode = other.fireMode;
weaponCategory = other.weaponCategory;
weaponType = other.weaponType;

// Move SFML objects
fireSound = std::move(other.fireSound);
reloadSound = std::move(other.reloadSound);
emptyClipSound = std::move(other.emptyClipSound);
weaponSprite = std::move(other.weaponSprite);
weaponTexture = std::move(other.weaponTexture);
weaponFrame = std::move(other.weaponFrame);

// Invalidate the other weapon's state
other.ammo = 0;
other.maxAmmo = 0;
}

// Update animations and timers for weapons, muzzle flashes and reloads
void Weapon::update(float deltaTime, const sf::Vector2f& playerPosition, bool isFlipped) {

    // make this not necessary
    this->isFlipped = isFlipped;

    // Update fire readiness
    timeSinceLastFire += deltaTime;
    if (timeSinceLastFire >= fireDelay) {
        canFire = true;  // Weapon is ready to fire again
        timeSinceLastFire = 0;
    }

    // Update muzzle flash animation
    if (isMuzzleFlashVisible) {
        muzzleFlashElapsedTime += deltaTime;

        if (muzzleFlashElapsedTime >= muzzleFlashFrameTime) {
            muzzleFlashElapsedTime = 0.f;
            currentMuzzleFlashFrame++;

            if (currentMuzzleFlashFrame >= 2) { // Number of frames in the animation
                isMuzzleFlashVisible = false; // End animation
                currentMuzzleFlashFrame = 0; // resetting the animation for automatic fire
            } else {
                muzzleFlashFrame.left = currentMuzzleFlashFrame * muzzleFlashFrame.width;
                muzzleFlashSprite.setTextureRect(muzzleFlashFrame);
            }
        }
    }

    // Update projectile spawn position
    sf::Vector2f muzzleOffset(70.f, 25.f); // Offset values depend on your sprite

    if (isFlipped) {
        muzzleOffset = {70.f, 25.f};
    }

    sf::Transform transform = weaponSprite.getTransform();
    spawnPosition = transform.transformPoint(muzzleOffset);

    // Update projectiles

    // update recoil:
    // Handle recoil recovery
    if (currentRecoilAngle != 0.f) {
        float recoverySpeed = recoilAngle / recoilDuration; // Rate of recovery per second

        if (currentRecoilAngle > 0.f) {
            currentRecoilAngle -= recoverySpeed * deltaTime;
            if (currentRecoilAngle < 0.f) currentRecoilAngle = 0.f; // Snap to 0 if overshooting
        } else if (currentRecoilAngle < 0.f) {
            currentRecoilAngle += recoverySpeed * deltaTime;
            if (currentRecoilAngle > 0.f) currentRecoilAngle = 0.f; // Snap to 0 if overshooting
        }
    }
}

// Render the weapon
// ** centralize the logic for the locations of the sprites, their origine and their position
// move the position updating into weapon.update
void Weapon::render(sf::RenderWindow& window, const sf::Vector2f& playerPosition, bool isFlipped) {
    // Calculate weapon position relative to the player
    sf::Vector2f weaponPosition = playerPosition + offset;
    sf::Vector2f muzzleFlashPosition = weaponPosition + muzzleFlashOffset;

    // Flip the weapon sprite horizontally if needed
    weaponSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    weaponSprite.setPosition(weaponPosition);
    window.draw(weaponSprite);


    // Render muzzleFlash
    if (isMuzzleFlashVisible) {

        //muzzleFlashSprite.setPosition(muzzleFlashStaticPosition);
        // Aim the weapon sprite
        muzzleFlashSprite.setPosition(muzzleFlashStaticOrigin);
        // Flip the weapon sprite if the player is facing left
        muzzleFlashSprite.setScale(isMuzzleFlashFlipped ? -1.f : 1.f, 1.f);
        // Rotate the weapon sprite to match the aiming angled
        muzzleFlashSprite.setRotation(muzzleFlashStaticAngle);

        if (isFlipped) {
            muzzleFlashSprite.move(-offset.x, offset.y); // Adjust position for flipped sprite
        } else {
            muzzleFlashSprite.move(offset.x, offset.y);  // Default offset
        }

        window.draw(muzzleFlashSprite);
    }

    // have any debug circles here
    sf::CircleShape weaponDebug(1.f);                    // Radius of circle
    weaponDebug.setFillColor(sf::Color::Red);            // Make it red for visibility
    weaponDebug.setPosition(weaponPosition);       // Use the sprite's current world position
    //window.draw(weaponDebug);
}

// Aim the weapon using an angle
void Weapon::aim(float angle, const sf::Vector2f &origin, bool isFlipped) {

    // Aim the weapon sprite
    weaponSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
    // Rotate the weapon sprite to match the aiming angle
    weaponSprite.setRotation(angle);

    // check if you need this:
    muzzleFlashAngle = angle;

    if (isFlipped) {
        weaponSprite.move(-offset.x, offset.y); // Adjust position for flipped sprite
    } else {
        weaponSprite.move(offset.x, offset.y);  // Default offset
    }
}

// Free resources (if needed)
void Weapon::free() {
    // Cleanup of dynamically allocated resources if necessary
    // SFML handles most resources automatically, so this is generally empty
}

sf::Vector2f Weapon::getPosition() const {
    return weaponSprite.getPosition();
}


// Getter for name
std::string Weapon::getName() const {
    return name;
}

// Getter for ammo
int Weapon::getAmmo() const {
    return ammo;
}

// Check if the weapon is out of ammo
bool Weapon::isOutOfAmmo() const {
    return ammo <= 0;
}

void Weapon::setAmmo(int newAmmo) {
    if (newAmmo >= 0 && newAmmo <= maxAmmo) {
        ammo = newAmmo;
    } else if (newAmmo > maxAmmo) {
        ammo = maxAmmo; // Clamp to maxAmmo
    } else {
        ammo = 0; // Prevent negative ammo
    }
}

std::vector<std::shared_ptr<Projectile>>& Weapon::getProjectiles() {
    return projectiles;
}

float Weapon::getCurrentRecoil () const {
    return currentRecoilAngle;
}

// Check if the weapon is reloading
bool Weapon::checkReloading() const {
    return isReloading;
}


bool Weapon::checkCanFire() const {
    return canFire;
}

FireMode Weapon::getFireMode() const {
    return fireMode;
}

float Weapon::getFireDelay() const {
    return fireDelay;
}

void Weapon::setFireMode(FireMode mode) { fireMode = mode; }

void Weapon::setCanFire(bool value) { canFire = value; }

// Reload the weapon
void Weapon::reload() {
    if (!isReloading && ammo < maxAmmo) {
        isReloading = true;
        reloadSound.play();  // Play reload sound
        ammo = maxAmmo;      // Reset ammo (add delay logic if necessary)
    }
}

// look into implementing hte swivel point and the tip of the barrel where the projectile should spawn from
// Add recoil and shells and smoke and flash that lights up the player, and bullet ricochets/impacts
// Fire the weapon
void Weapon::fire(const sf::Vector2f& direction, const sf::Vector2f& playerPosition, const sf::Vector2f &origin, bool isFlipped) {

    if (ammo > 0 && !isReloading && canFire) {
        ammo--;
        canFire = false;
        // Create a projectile and add it to the list in the weapon
        auto projectile = std::make_shared<Projectile>(std::make_shared<sf::Texture>(projectileTexture), std::make_shared<sf::Texture>(projectileImpactTexture), std::make_shared<sf::Texture>(projectileEnemyImpactTexture), spawnPosition, direction, bulletSpeed, damage, projectileType);
        projectiles.push_back(projectile);

        // Show muzzle flash
        isMuzzleFlashVisible = true;

        // set the position of the muzzle flash
        sf::Vector2f weaponPosition = playerPosition + offset;
        muzzleFlashStaticPosition = weaponPosition;
        isMuzzleFlashFlipped = isFlipped;

        muzzleFlashStaticOrigin = origin;
        muzzleFlashStaticAngle = muzzleFlashAngle;

        // Aim the muzzle flash sprite **** move this to the render method or smth
        /*uzzleFlashSprite.setPosition(origin);
        // Flip the weapon sprite if the player is facing left
        muzzleFlashSprite.setScale(isFlipped ? -1.f : 1.f, 1.f);
        // Rotate the weapon sprite to match the aiming angle
        muzzleFlashSprite.setRotation(angle);*/

        if (isFlipped) {
            muzzleFlashSprite.move(-offset.x, offset.y); // Adjust position for flipped sprite
        } else {
            muzzleFlashSprite.move(offset.x, offset.y);  // Default offset
        }

        // update the muzzle flash animation
        muzzleFlashElapsedTime = 0.f;
        currentMuzzleFlashFrame = 0; // Reset to the first frame
        muzzleFlashFrame.left = 0;   // Reset the texture rect to the first frame
        muzzleFlashSprite.setTextureRect(muzzleFlashFrame);

        // recoil:
        recoilTimer = 0.f;
        isRecoiling = true;

        if (isFlipped) {
            currentRecoilAngle += recoilAngle;
        } else {
            currentRecoilAngle -= recoilAngle;
        }

        fireSound.play(); // Play fire sound
    } else if (ammo <= 0) {
        emptyClipSound.play(); // Play empty clip sound
        canFire = false;
    }
}

// Update projectiles
// maybe move this to the collision manager
void Weapon::updateProjectiles(float deltaTime) {

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        // Check if the projectile is finished
        if ((*it)->checkIsFinished()) {
            std::cout << "Removing projectile at position ("<< std::endl;
            it = projectiles.erase(it); // Remove and get the next iterator
        } else {
            // Update the projectile if it's not finished
            (*it)->update(deltaTime);
            ++it; // Move to the next projectile
        }
    }
}

// Render projectiles
void Weapon::renderProjectiles(sf::RenderWindow& window) {
    for (const auto& projectile : projectiles) {
        projectile->render(window);
    }
}