#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include <vector>
#include <SDL.h>
#include "const.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Segment {
    int x, y;
};

class Snake {
public:
    Snake();
    void handleInput(SDL_Keycode key);
    void update();
    void render(SDL_Renderer* renderer);
    void grow();
    bool checkCollision();
    void reset();
    Segment getHeadPosition();

private:
    std::vector<Segment> body;
    Direction direction;
};

#endif
