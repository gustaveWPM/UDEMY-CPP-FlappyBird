#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace FlappyBirdEngine {
    splashState::splashState(gameDataRef data) : _data(data) {}

    void splashState::init() {
        _data->assetManager.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assetManager.getTexture("Splash State Background"));
    }

    void splashState::handleInput() {
        sf::Event event;

        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type)
                _data->window.close();
        }
    }

    void splashState::update(float dt) {
        if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
            _data->stateMachine.addState(StateRef(new mainMenuState(_data)));
    }

    void splashState::draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.display();
    }
}