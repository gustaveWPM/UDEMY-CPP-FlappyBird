#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace FlappyBirdEngine {
    class splashState : public State
    {
    public:
        splashState(gameDataRef data);

        void init();

        void handleInput();
        void update(float dt);
        void draw(float dt);

    private:
        gameDataRef _data;

        sf::Clock _clock;
        sf::Sprite _background;
    };
}