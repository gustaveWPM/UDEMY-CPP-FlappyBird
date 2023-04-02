#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace FlappyBirdEngine {
    Land::Land(gameDataRef data) : _data(data) {
        sf::Sprite sprite(_data->assetManager.getTexture("Land"));
        sf::Sprite sprite2(_data->assetManager.getTexture("Land"));

        sprite.setPosition(0, _data->window.getSize().y - sprite.getGlobalBounds().height);
        sprite2.setPosition(sprite.getGlobalBounds().width, _data->window.getSize().y - sprite.getGlobalBounds().height);

        _landSprites.push_back(sprite);
        _landSprites.push_back(sprite2);
    }

    void Land::moveLand(float dt) {
//        for (auto i = 0; i < _landSprites.size(); i++) {
//            float movement = PIPE_MOVESPEED * dt;
//
//            _landSprites.at(i).move(-movement, 0);
//            if (_landSprites.at(i).getPosition().x < 0 - _landSprites.at(i).getGlobalBounds().width) {
//                sf::Vector2f position(_data->window.getSize().x, _landSprites.at(i).getPosition().y);
//                _landSprites.at(i).setPosition(position);
//            }
//        }
        for (auto& landSprite : _landSprites) {
            float movement = PIPE_MOVESPEED * dt;

            landSprite.move(-movement, 0);
            if (landSprite.getPosition().x < 0 - landSprite.getGlobalBounds().width)
                landSprite.setPosition(_data->window.getSize().x, landSprite.getPosition().y);
        }
    }

    void Land::drawLand() {
        for (auto& landSprite : _landSprites)
            _data->window.draw(landSprite);
    }

    const std::vector<sf::Sprite>& Land::getSprites() const {
        return _landSprites;
    }
}