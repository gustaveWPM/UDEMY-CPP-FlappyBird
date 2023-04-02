#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace FlappyBirdEngine {
    class mainMenuState : public State {
    public:
        mainMenuState(gameDataRef data);

        void init();

        void handleInput();
        void update(float dt);
        void draw(float dt);

    private:
        gameDataRef _data;

        sf::Sprite _background;
        sf::Sprite _title;
        sf::Sprite _playButton;
    };
}