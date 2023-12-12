#pragma once

#include "Game.hpp"

int main() {

    Game game; //initialises the game engine

    while (game.running()) {
        game.update();
        game.render();
    }
    return 0;
}

/*TODO:


*/