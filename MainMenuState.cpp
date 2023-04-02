#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace FlappyBirdEngine {
    mainMenuState::mainMenuState(gameDataRef data) : _data(data) {}

    void mainMenuState::init() {
        _data->assetManager.loadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assetManager.loadTexture("Game Title", GAME_TITLE_FILEPATH);
        _data->assetManager.loadTexture("Play Button", PLAY_BUTTON_FILEPATH);
        _background.setTexture(_data->assetManager.getTexture("Main Menu Background"));
        _title.setTexture(_data->assetManager.getTexture("Game Title"));
        _playButton.setTexture(_data->assetManager.getTexture("Play Button"));
        _title.setPosition(
            (SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2),
            _title.getGlobalBounds().height / 2
        );

        _playButton.setPosition(
                (SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
                (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2)
        );
    }

    void mainMenuState::handleInput() {
        sf::Event event;

        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type)
                _data->window.close();
            else if (_data->inputManager.isSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
                _data->stateMachine.addState(StateRef(new gameState(_data)), true);
        }
    }

    void mainMenuState::update(float dt) {}

    void mainMenuState::draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_title);
        _data->window.draw(_playButton);
        _data->window.display();
    }
}