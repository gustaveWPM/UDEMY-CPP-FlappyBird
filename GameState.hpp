#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collisions.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace FlappyBirdEngine {
    class gameState : public State {
    public:
        gameState(gameDataRef data);

        void init();

        void handleInput();
        void update(float dt);
        void draw(float dt);

    private:
        gameDataRef _data;
        sf::Sprite _background;
        Pipe* _pipe;
        Land* _land;
        Bird* _bird;
        Flash* _flash;
        HUD* _hud;

        Collisions collision;
        sf::Clock _clock;
        int _gameState;
        int _score;

        sf::SoundBuffer _hitSoundBuffer;
        sf::SoundBuffer _wingSoundBuffer;
        sf::SoundBuffer _pointSoundBuffer;
        sf::Sound _hitSound;
        sf::Sound _wingSound;
        sf::Sound _pointSound;
    };
}