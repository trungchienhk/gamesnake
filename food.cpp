#include "food.h"
#include <cstdlib>
#include "const.h"
#include <SDL.h>
#include <SDL_image.h>
#include"game.h"
Food::Food(SDL_Renderer* renderer)  {
    SDL_Surface* surface = IMG_Load("food.jpg");
    foodTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    respawn();
}

Food::~Food() {
    if (foodTexture) {
        SDL_DestroyTexture(foodTexture);
    }
}

void Food::respawn() {
    position.x = (rand() % (SCREEN_WIDTH / CELL_SIZE)) * CELL_SIZE;
    position.y = (rand() % (SCREEN_HEIGHT / CELL_SIZE)) * CELL_SIZE;
}

void Food::render(SDL_Renderer* renderer) {
    cnt++;
    if (cnt >= 4) {
        vis= !vis;
        cnt = 0;
    }
    if (vis) {
        SDL_Rect rect = { position.x, position.y, CELL_SIZE, CELL_SIZE };
        if (foodTexture) {
            SDL_RenderCopy(renderer, foodTexture, NULL, &rect);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

SDL_Point Food::getPosition() const {
    return position;
}
