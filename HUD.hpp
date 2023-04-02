#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace FlappyBirdEngine {
    class HUD {
    public:
        HUD(gameDataRef data);
        void draw();
        void updateScore(int score);

    private:
        gameDataRef _data;
        sf::Text _scoreText;
    };
}