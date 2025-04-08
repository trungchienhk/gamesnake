#include "game.h"
#include<iostream>
int main(int argc, char* argv[]) {
    Game game;
    while (game.running==true) {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(100);
    }
    return 0;
}
