#pragma once

#include <SFML/Graphics.hpp>

namespace FlappyBirdEngine {
    class InputManager {
    public:
        InputManager() {}
        ~InputManager() {}

        bool isSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window);
        sf::Vector2i getMousePosition(sf::RenderWindow& window);
    };
}