//
// Created by Leland Sion on 2025-01-03.
//

#include "Animation.h"

#include "Animation.h"

Animation::Animation()
        : texture(nullptr), frameSize(0, 0), frameCount(0), duration(0.f), elapsedTime(0.f), currentFrame(0) {}

void Animation::initialize(sf::Texture& texture, sf::Vector2i frameSize, int frameCount, float duration) {
    this->texture = &texture;
    this->frameSize = frameSize;
    this->frameCount = frameCount;
    this->duration = duration;
    this->elapsedTime = 0.f;
    this->currentFrame = 0;
}

void Animation::update(float deltaTime) {
    elapsedTime += deltaTime;
    float timePerFrame = duration / frameCount;

    if (elapsedTime >= timePerFrame) {
        elapsedTime -= timePerFrame;
        currentFrame++;
        if (currentFrame >= frameCount) {
            currentFrame = 0; // Loop animation
        }
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) {
    int framesPerRow = texture->getSize().x / frameSize.x;
    int x = (currentFrame % framesPerRow) * frameSize.x;
    int y = (currentFrame / framesPerRow) * frameSize.y;

    sprite.setTexture(*texture); // Only set once
    sprite.setTextureRect(sf::IntRect(x, y, frameSize.x, frameSize.y));
}

bool Animation::isFinished() const {
    return currentFrame >= frameCount - 1 && elapsedTime >= ((duration / frameCount) - 0.012);
}

void Animation::reset() {
    elapsedTime = 0.f;
    currentFrame = 0;
}