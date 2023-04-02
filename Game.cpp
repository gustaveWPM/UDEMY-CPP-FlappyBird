#include "Game.hpp"
#include "SplashState.hpp"

namespace FlappyBirdEngine {
    Game::Game(int width, int height, std::string title) {
        _data->window.create(
            sf::VideoMode(width, height),
            title,
            sf::Style::Close | sf::Style::Titlebar
        );
        _data->stateMachine.addState(StateRef(new splashState(_data)));
        run();
    }

    void Game::run() {
        float newTime, frameTime, interpolation;

        float currentTime = _clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (_data->window.isOpen()) {
            _data->stateMachine.processStateChanges();
            newTime = _clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if (frameTime > 0.25f)
                frameTime = 0.25f;
            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= dt) {
                _data->stateMachine.getActiveState()->handleInput();
                _data->stateMachine.getActiveState()->update(dt);
                accumulator -= dt;
            }
            interpolation = accumulator / dt;
            _data->stateMachine.getActiveState()->draw(interpolation);
        }
    }
}