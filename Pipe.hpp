#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace FlappyBirdEngine {
    class Pipe {
    public:
        Pipe(gameDataRef data);

        void spawnBottomPipe();
        void spawnTopPipe();
        void spawnScoringPipe();
        void movePipes(float dt);
        void drawPipes();
        void randomizePipeOffset();

        const std::vector<sf::Sprite>& getSprites() const;
        std::vector<sf::Sprite>& getScoringSprites();

    private:
        gameDataRef _data;
        std::vector<sf::Sprite> _pipeSprites;
        std::vector<sf::Sprite> _scoringPipes;
        int _landHeight;
        int _pipeSpawnYOffset;
    };
}