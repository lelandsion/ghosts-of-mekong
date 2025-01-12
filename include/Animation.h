//
// Created by Leland Sion on 2025-01-03.
//

#ifndef VIETNAMMARINE2_ANIMATION_H
#define VIETNAMMARINE2_ANIMATION_H

#include <SFML/Graphics.hpp>


class Animation {
public:
    Animation();

    void initialize(sf::Texture& texture, sf::Vector2i frameSize, int frameCount, float duration);
    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite); // Just updates the `setTextureRect`
    bool isFinished() const;
    void reset();

private:
    sf::Texture* texture; // Pointer to the texture
    sf::Vector2i frameSize;
    int frameCount;
    float duration;
    float elapsedTime;
    int currentFrame;
};


#endif //VIETNAMMARINE2_ANIMATION_H
