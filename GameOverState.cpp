#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <fstream>

namespace FlappyBirdEngine {
    gameOverState::gameOverState(gameDataRef data, int score) : _data(data), _score(score) {}

    void gameOverState::init() {
        std::ifstream readFile;
        readFile.open(HIGHSCORE_PATH);

        if (readFile.is_open()) {
            while (!readFile.eof()) {
                readFile >> _highScore;
            }
        } else
            _highScore = 0;
        readFile.close();

        std::ofstream writeFile(HIGHSCORE_PATH);
        if (writeFile.is_open()) {
            if (_score > _highScore) {
                _highScore = _score;
            }
            writeFile << _highScore;
        }
        writeFile.close();

        _data->assetManager.loadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
        _data->assetManager.loadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
        _data->assetManager.loadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        _data->assetManager.loadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
        _data->assetManager.loadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
        _data->assetManager.loadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
        _data->assetManager.loadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);
        _background.setTexture(_data->assetManager.getTexture("Game Over Background"));
        _gameOverTitle.setTexture(_data->assetManager.getTexture("Game Over Title"));
        _gameOverBody.setTexture(_data->assetManager.getTexture("Game Over Body"));
        _retryButton.setTexture(_data->assetManager.getTexture("Play Button"));

        if (_score >= PLATINUM_MEDAL_SCORE)
            _medal.setTexture(_data->assetManager.getTexture("Platinum Medal"));
        else if (_score >= GOLD_MEDAL_SCORE)
            _medal.setTexture(_data->assetManager.getTexture("Gold Medal"));
        else if (_score >= SILVER_MEDAL_SCORE)
            _medal.setTexture(_data->assetManager.getTexture("Silver Medal"));
        else
            _medal.setTexture(_data->assetManager.getTexture("Bronze Medal"));

        _medal.setPosition(175, 465);

        _gameOverBody.setPosition(_data->window.getSize().x / 2 - _gameOverBody.getGlobalBounds().width / 2, _data->window.getSize().y / 2 - _gameOverBody.getGlobalBounds().height / 2);
        _gameOverTitle.setPosition(_data->window.getSize().x / 2 + 8 - _gameOverTitle.getGlobalBounds().width / 2, _gameOverBody.getPosition().y - _gameOverTitle.getGlobalBounds().height * 1.2f);
        _retryButton.setPosition(_data->window.getSize().x / 2 - _retryButton.getGlobalBounds().width / 2, _gameOverBody.getPosition().y + _gameOverBody.getGlobalBounds().height + _retryButton.getGlobalBounds().height * 0.2f);

        _scoreText.setFont(_data->assetManager.getFont("Flappy Font"));
        _scoreText.setString(std::to_string(_score));
        _scoreText.setCharacterSize(56);
        _scoreText.setFillColor(sf::Color::White);
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2);
        _scoreText.setPosition(_data->window.getSize().x / 10 * 7.25f, _data->window.getSize().y / 2.15f);

        _highScoreText.setFont(_data->assetManager.getFont("Flappy Font"));
        _highScoreText.setString(std::to_string(_highScore));
        _highScoreText.setCharacterSize(56);
        _highScoreText.setFillColor(sf::Color::White);
        _highScoreText.setOrigin(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2);
        _highScoreText.setPosition(_data->window.getSize().x / 10 * 7.25f, _data->window.getSize().y / 1.78f);
    }

    void gameOverState::handleInput() {
        sf::Event event;

        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type)
                _data->window.close();
            if (_data->inputManager.isSpriteClicked(_retryButton, sf::Mouse::Left, _data->window)) {
                _data->stateMachine.addState(StateRef(new gameState(_data)), true);
            }
        }
    }

    void gameOverState::update(float dt) {}

    void gameOverState::draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);
        _data->window.draw(_gameOverTitle);
        _data->window.draw(_gameOverBody);
        _data->window.draw(_retryButton);
        _data->window.draw(_scoreText);
        _data->window.draw(_highScoreText);
        _data->window.draw(_medal);
        _data->window.display();
    }
}