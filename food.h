#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED
#include <SDL.h>
#include"const.h"
class Food {
public:
    Food(SDL_Renderer* renderer);
    ~Food();
    void respawn();
    void render(SDL_Renderer* renderer);
    SDL_Point getPosition() const;

private:
    SDL_Point position;
    SDL_Texture* foodTexture;
    bool vis=true;
    int cnt=0;
};
#endif
