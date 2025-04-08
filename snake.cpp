#include "snake.h"
#include <SDL.h>

Snake::Snake() {
    reset();
}

void Snake::reset() {
    body.clear();
    int startX = SCREEN_WIDTH / 2;
    int startY = SCREEN_HEIGHT / 2;
    direction = RIGHT;

    for (int i = 0; i < INITIAL_LENGTH; i++) {
        body.push_back({ startX - i * CELL_SIZE, startY });
    }
}

void Snake::handleInput(SDL_Keycode key) {
    Direction newDirection = direction;
    switch (key) {
        case SDLK_UP:
            if (direction != DOWN) newDirection = UP;
            break;
        case SDLK_DOWN:
            if (direction != UP) newDirection = DOWN;
            break;
        case SDLK_LEFT:
            if (direction != RIGHT) newDirection = LEFT;
            break;
        case SDLK_RIGHT:
            if (direction != LEFT) newDirection = RIGHT;
            break;
    }
    if (newDirection != direction) {
        direction = newDirection;
    }
}

void Snake::update() {
    Segment newHead = body.front();
    switch (direction) {
        case UP:    newHead.y -= CELL_SIZE; break;
        case DOWN:  newHead.y += CELL_SIZE; break;
        case LEFT:  newHead.x -= CELL_SIZE; break;
        case RIGHT: newHead.x += CELL_SIZE; break;
    }
    body.insert(body.begin(), newHead);
    body.pop_back();
}

void Snake::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (const auto& segment : body) {
        SDL_Rect rect = { segment.x, segment.y, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Snake::grow() {
    body.push_back(body.back());
}

bool Snake::checkCollision() {
    const Segment& head = body.front();
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i].x == head.x && body[i].y == head.y) {
            return true;
        }
    }
    return (head.x < 0 || head.y < 0 || head.x >= SCREEN_WIDTH || head.y >= SCREEN_HEIGHT);
}

Segment Snake::getHeadPosition() {
    return body.front();
}
