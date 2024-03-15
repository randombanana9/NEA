#pragma once

#include "Game.hpp"

int main() {
    Game game; //initialises the game engine

    while (game.running()) { //While the game has not been closed
        game.update(); //Updates the game state, 60 times per seconds
        game.render(); //Renders the game visuals, 60 times per second
    }
    return 0;
}