#include "Bird.hpp"

namespace FlappyBirdEngine {
    Bird::Bird(gameDataRef data) : _data(data) {
        _animationIt = 0;
        _angle = 0;
        _birdState = BIRD_STATE_STILL;
        _animationFrames.push_back(_data->assetManager.getTexture("Bird Frame 1"));
        _animationFrames.push_back(_data->assetManager.getTexture("Bird Frame 2"));
        _animationFrames.push_back(_data->assetManager.getTexture("Bird Frame 3"));
        _animationFrames.push_back(_data->assetManager.getTexture("Bird Frame 4"));
        _birdSprite.setTexture(_animationFrames.at(_animationIt));
        _birdSprite.setPosition(
                _data->window.getSize().x / 4 - (_birdSprite.getGlobalBounds().width / 2),
                _data->window.getSize().y / 2 - (_birdSprite.getGlobalBounds().height / 2)
        );

        sf::Vector2f origin = sf::Vector2f(
                _birdSprite.getGlobalBounds().width / 2,
                _birdSprite.getGlobalBounds().height / 2
        );
        _birdSprite.setOrigin(origin);
    }

    void Bird::draw() {
        _data->window.draw(_birdSprite);
    }

    void Bird::animate(float dt) {
        if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size()) {
            if (_animationIt < _animationFrames.size() - 1)
                _animationIt++;
            else
                _animationIt = 0;
            _birdSprite.setTexture(_animationFrames.at(_animationIt));
            _clock.restart();
        }
    }

    void Bird::tap() {
        _movementClock.restart();
        _birdState = BIRD_STATE_FLYING;
    }

    void Bird::update(float dt) {
        if (_birdState == BIRD_STATE_FALLING) {
            _birdSprite.move(0, GRAVITY * dt);
            _angle += ROTATION_SPEED * dt;
            if (_angle > MAX_ANGLE)
                _angle = MAX_ANGLE;
            _birdSprite.setRotation(_angle);
        } else if (_birdState == BIRD_STATE_FLYING) {
            _angle -= ROTATION_SPEED * dt;
            if (_birdSprite.getPosition().y > _birdSprite.getGlobalBounds().height / 2 - 8) {
                _birdSprite.move(0.0f, -FLYING_SPEED * dt);
            } else
                _birdState = BIRD_STATE_FALLING;
            if (_angle < MIN_ANGLE)
                _angle = MIN_ANGLE;
            _birdSprite.setRotation(_angle);
        }
        if (_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION) {
            _movementClock.restart();
            _birdState = BIRD_STATE_FALLING;
        }
    }

    const sf::Sprite& Bird::getSprite() const {
        return _birdSprite;
    }
}