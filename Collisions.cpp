#include "Collisions.hpp"

namespace FlappyBirdEngine {
    bool Collisions::checkSpriteCollision(sf::Sprite& sprite1, sf::Sprite& sprite2) {
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        if (rect1.intersects(rect2))
            return true;
        return false;
    }

    bool Collisions::checkSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2, float scale1, float scale2) {
        sprite1.setScale(scale1, scale1);
        sprite2.setScale(scale2, scale2);
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        if (rect1.intersects(rect2))
            return true;
        return false;
    }
}