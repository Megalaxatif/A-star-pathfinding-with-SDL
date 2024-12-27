#include <header/pathfinding.h>
#include <header/game.h>
#include <SDL/SDL.h>
#include <iostream>
#include <header/game.h>
#include <header/input.h>
#include <chrono>

#undef main

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = nullptr;
    SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // clear the screen
    SDL_RenderClear(renderer);
    std::vector<cell*> path = AstarPathfinding(start_cell, end_cell); // run the pathfinding algorithm
    
    // main loop
    auto start = std::chrono::high_resolution_clock::now();

    while (running){
        InputHandler(); // input handler

        if (generating){
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // fix the speed between the generations
            if (elapsed.count() >= delay){
                start = std::chrono::high_resolution_clock::now();

                // DO SOMETHING....

            }
        }
            RefreshGameTexture();
            DrawGameTexture();
            SDL_Delay(5); // little delay not to burn the cpu ;)
    }
    return 0;
}