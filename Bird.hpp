#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>

namespace FlappyBirdEngine {
    class Bird {
    public:
        Bird(gameDataRef data);
        void draw();
        void animate(float dt);
        void update(float dt);
        void tap();

        const sf::Sprite& getSprite() const;

    private:
        gameDataRef _data;
        sf::Sprite _birdSprite;

        std::vector<sf::Texture> _animationFrames;
        unsigned int _animationIt;
        sf::Clock _clock;
        sf::Clock _movementClock;
        int _birdState;
        float _angle;
    };
}