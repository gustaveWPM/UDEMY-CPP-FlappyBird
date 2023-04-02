#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"

#include <iostream>

namespace FlappyBirdEngine {
    gameState::gameState(gameDataRef data) : _data(data) {}

    void gameState::init() {
        if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
            std::cerr << "Error loading hit sound file" << std::endl;
        if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
            std::cerr << "Error loading wing sound file" << std::endl;
        if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
            std::cerr << "Error loading point sound file" << std::endl;

        _hitSound.setBuffer(_hitSoundBuffer);
        _wingSound.setBuffer(_wingSoundBuffer);
        _pointSound.setBuffer(_pointSoundBuffer);

        _data->assetManager.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _data->assetManager.loadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assetManager.loadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        _data->assetManager.loadTexture("Land", LAND_FILEPATH);
        _data->assetManager.loadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
        _data->assetManager.loadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
        _data->assetManager.loadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
        _data->assetManager.loadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
        _data->assetManager.loadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
        _data->assetManager.loadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

        _pipe = new Pipe(_data);
        _land = new Land(_data);
        _bird = new Bird(_data);
        _flash = new Flash(_data);
        _hud = new HUD(_data);

        _score = 0;
        _hud->updateScore(_score);

        _background.setTexture(_data->assetManager.getTexture("Game Background"));

        _gameState = GameStates::eReady;
    }

    void gameState::handleInput() {
        sf::Event event;

        while (_data->window.pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                _wingSound.stop();
                _hitSound.stop();
                _pointSound.stop();
                _data->window.close();
            }
            if (_data->inputManager.isSpriteClicked(_background, sf::Mouse::Left, _data->window))
                if (_gameState != GameStates::eGameOver) {
                    _gameState = GameStates::ePlaying;
                    _bird->tap();
                    _wingSound.play();
                }
        }
    }

    void gameState::update(float dt) {
        if (_gameState != GameStates::eGameOver) {
            _bird->animate(dt);
            _land->moveLand(dt);
        }

        if (_gameState == GameStates::ePlaying) {
            _pipe->movePipes(dt);
            if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {
                _pipe->randomizePipeOffset();

                _pipe->spawnScoringPipe();
                _pipe->spawnBottomPipe();
                _pipe->spawnTopPipe();

                _clock.restart();
            }
            _bird->update(dt);
            std::vector <sf::Sprite> landSprites = _land->getSprites();
            for (auto &landSprite: landSprites) {
                if (collision.checkSpriteCollision(_bird->getSprite(), landSprite, 0.7f, 1.0f)) {
                    _gameState = GameStates::eGameOver;
                    _clock.restart();
                    _hitSound.play();
                }
            }
            std::vector <sf::Sprite> pipeSprites = _pipe->getSprites();
            for (auto &pipeSprite: pipeSprites) {
                if (collision.checkSpriteCollision(_bird->getSprite(), pipeSprite, 0.625f, 1.0f)) {
                    _gameState = GameStates::eGameOver;
                    _clock.restart();
                    _hitSound.play();
                }
            }
            if (_gameState == GameStates::ePlaying) {
                std::vector <sf::Sprite> &scoringSprites = _pipe->getScoringSprites();
                for (int i = 0; i < scoringSprites.size(); i++) {
                    if (collision.checkSpriteCollision(_bird->getSprite(), scoringSprites.at(i), 0.625f, 1.0f)) {
                        _pointSound.play();
                        _score++;
                        _hud->updateScore(_score);
                        scoringSprites.erase(scoringSprites.begin() + i);
                    }
                }
            }
        }

        if (_gameState == GameStates::eGameOver) {
            _flash->show(dt);
            if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) {
                _data->stateMachine.addState(StateRef(new gameOverState(_data, _score)), true);
            }
        }
    }

    void gameState::draw(float dt) {
        _data->window.clear();
        _data->window.draw(_background);

        _pipe->drawPipes();
        _land->drawLand();
        _bird->draw();
        _flash->draw();
        _hud->draw();

        _data->window.display();
    }
}