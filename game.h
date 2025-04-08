#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "snake.h"
#include "food.h"
#include<SDL_mixer.h>
class Game {
public:
    Game();
    ~Game();
    bool running=true;
    void handleEvents();
    void update();
    void render();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Snake snake;
    Food food = Food(renderer);
    bool gameover=false;
    int dem=0;
    Mix_Chunk* eatSound;
    Mix_Music* backgroundMusic;
    Mix_Music* gameOverMusic;
    void reset();
    SDL_Texture* backgroundTexture;
    void loadSounds();
};


#endif
