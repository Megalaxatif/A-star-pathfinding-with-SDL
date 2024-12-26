#include <header/pathfinding.h>
#include <header/game.h>
#include <SDL/SDL.h>
#include <iostream>
#undef main

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // clear the screen
    SDL_RenderClear(renderer);
    std::vector<cell*> path = AstarPathfinding(start_cell, end_cell);

    return 0;
}