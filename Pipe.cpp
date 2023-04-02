#include "Pipe.hpp"

namespace FlappyBirdEngine {

    Pipe::Pipe(gameDataRef data) : _data(data) {
        _landHeight = _data->assetManager.getTexture("Land").getSize().y;
        _pipeSpawnYOffset = 0;
    }

    void Pipe::spawnBottomPipe() {
        sf::Sprite sprite(_data->assetManager.getTexture("Pipe Up"));
        sprite.setPosition(_data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset);
        _pipeSprites.push_back(sprite);
    }

    void Pipe::spawnTopPipe() {
        sf::Sprite sprite(_data->assetManager.getTexture("Pipe Down"));
        sprite.setPosition(_data->window.getSize().x, -_pipeSpawnYOffset);
        _pipeSprites.push_back(sprite);
    }

    void Pipe::spawnScoringPipe() {
        sf::Sprite sprite(_data->assetManager.getTexture("Scoring Pipe"));
        sprite.setPosition(_data->window.getSize().x, 0);
        sprite.setColor(sf::Color(0, 0, 0, 0));
        _scoringPipes.push_back(sprite);
    }

    void Pipe::movePipes(float dt) {
        for (auto i = 0; i < _pipeSprites.size(); i++) {
            if (_pipeSprites.at(i).getPosition().x < 0 - _pipeSprites.at(i).getGlobalBounds().width) {
                _pipeSprites.erase(_pipeSprites.begin() + i);
                continue;
            }
            float movement = PIPE_MOVESPEED * dt;
            _pipeSprites.at(i).move(-movement, 0);
        }
        for (auto i = 0; i < _scoringPipes.size(); i++) {
            if (_scoringPipes.at(i).getPosition().x < 0 - _scoringPipes.at(i).getGlobalBounds().width) {
                _scoringPipes.erase(_scoringPipes.begin() + i);
                continue;
            }
            float movement = PIPE_MOVESPEED * dt;
            _scoringPipes.at(i).move(-movement, 0);
        }
    }

    void Pipe::drawPipes() {
        for (const auto& pipeSprite : _pipeSprites) {
            _data->window.draw(pipeSprite);
        }
    }

    void Pipe::randomizePipeOffset() {
        _pipeSpawnYOffset = rand() % ( _landHeight + 1);
    }

    const std::vector<sf::Sprite>& Pipe::getSprites() const {
        return _pipeSprites;
    }

    std::vector<sf::Sprite>& Pipe::getScoringSprites() {
        return _scoringPipes;
    }
}