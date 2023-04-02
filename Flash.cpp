#include "Flash.hpp"

namespace FlappyBirdEngine {
    Flash::Flash(gameDataRef data) : _data(data) {
        _shape = sf::RectangleShape(sf::Vector2f(_data->window.getSize()));
        _shape.setFillColor(sf::Color(255, 255, 255, 0));
        _flashOn = true;
    }

    void Flash::show(float dt) {
        int alpha = 0;
        if (_flashOn) {
            alpha = _shape.getFillColor().a + FLASH_SPEED * dt;
            if (alpha >= 255) {
                alpha = 255;
                _flashOn = false;
            }
            _shape.setFillColor(sf::Color(255, 255, 255, alpha));
        } else {
            alpha = _shape.getFillColor().a - FLASH_SPEED * dt;
            if (alpha < 0) {
                alpha = 0;
            }
            _shape.setFillColor(sf::Color(255, 255, 255, alpha));
        }
    }

    void Flash::draw() {
        _data->window.draw(_shape);
    }
}