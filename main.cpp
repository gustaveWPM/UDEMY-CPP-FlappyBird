#include "Game.hpp"
#include "DEFINITIONS.hpp"

#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(nullptr));
    FlappyBirdEngine::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
}
