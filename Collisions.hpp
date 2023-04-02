#pragma once

#include <SFML/Graphics.hpp>

namespace FlappyBirdEngine {
    class Collisions {
    public:
        Collisions() = default;
        bool checkSpriteCollision(sf::Sprite& sprite1, sf::Sprite& sprite2);
        bool checkSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2, float scaleX, float scaleY);
    };
}