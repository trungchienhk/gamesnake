#include<iostream>
#include "game.h"
#include "const.h"
#include<SDL_image.h>
#include<SDL_mixer.h>
Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* bgSurface = IMG_Load("image/background.jpg");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    SDL_Surface* overSurface = IMG_Load("image/gameover.jpg");
    overTexture = SDL_CreateTextureFromSurface(renderer, overSurface);
    SDL_FreeSurface(overSurface);
    SDL_Surface* newSurface = IMG_Load("image/moman.jpg");
    newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
    SDL_FreeSurface(newSurface);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    loadSounds();
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    if (backgroundTexture) {
    SDL_DestroyTexture(backgroundTexture);
}
    IMG_Quit();
    Mix_FreeChunk(eatSound);
    Mix_FreeMusic(gameOverMusic);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    Mix_Quit();
}
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            if (mo) {
                mo = false;
                Mix_PlayMusic(backgroundMusic, -1);
                return;
            }
            if (event.key.keysym.sym == SDLK_SPACE && gameover==true) {
                reset();
                gameover=false;
            } else {
                snake.handleInput(event.key.keysym.sym);
            }
        }
    }
}

void Game::update() {
    if (gameover==true||mo==true) return;
    snake.update();
    if (snake.checkCollision()) {
        gameover = true;
        Mix_PlayMusic(gameOverMusic,1);
        std::cout<<"\rYour score is: "<<dem;
        dem=0;
        return;
    }
    if (snake.getHeadPosition().x == food.getPosition().x &&
        snake.getHeadPosition().y == food.getPosition().y) {
        snake.grow();
        food.respawn();
        dem++;
        Mix_PlayChannel(-1, eatSound, 0);
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    if(mo==true){
        SDL_RenderCopy(renderer, newTexture, NULL, NULL);
    }
    else if(gameover==true){
        SDL_RenderCopy(renderer, overTexture, NULL, NULL);
    }
    else{
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        snake.render(renderer);
        food.render(renderer);
    }
    SDL_RenderPresent(renderer);
}


void Game::reset() {
    snake.reset();
    food.respawn();
    gameover = false;
    if (backgroundMusic) {
        Mix_HaltMusic();
        Mix_PlayMusic(backgroundMusic, -1);
    }
}
void Game::loadSounds() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Init(MIX_INIT_MP3);
    eatSound = Mix_LoadWAV("mixer/grow.wav");
    Mix_VolumeChunk(eatSound, MIX_MAX_VOLUME);
    gameOverMusic = Mix_LoadMUS("mixer/gameover.mp3");
    backgroundMusic = Mix_LoadMUS("mixer/nhacnen.mp3");
}
