#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace FlappyBirdEngine {
    struct GameData {
        StateMachine stateMachine;
        sf::RenderWindow window;
        AssetManager assetManager;
        InputManager inputManager;
    };

    typedef std::shared_ptr<GameData> gameDataRef;

    class Game {
    public:
        Game(int width, int height, std::string title);

    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock _clock;
        gameDataRef _data = std::make_shared<GameData>();

        void run();
    };
}