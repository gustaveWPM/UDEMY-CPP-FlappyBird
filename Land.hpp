#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace FlappyBirdEngine {
    class Land {
    public:
        Land(gameDataRef data);
        void moveLand(float dt);
        void drawLand();

        const std::vector<sf::Sprite>& getSprites() const;

    private:
        gameDataRef _data;
        std::vector<sf::Sprite> _landSprites;
    };
}