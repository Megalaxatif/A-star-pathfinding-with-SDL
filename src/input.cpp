#include <header/input.h>
#include <header/game.h>
#include <SDL/SDL.h>
#include <iostream>

bool running = true;
bool generating = true;
int delay = 100; // delay between each generation
SDL_Event event;

void InputHandler(){
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) running = false;
        else if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_RIGHT     : if(sourceRect.x + SPEED + sourceRect.w <= WIDTH)  sourceRect.x += SPEED;                                   break;
                case SDLK_LEFT      : if(sourceRect.x - SPEED >= 0)                         sourceRect.x -= SPEED;                                   break;
                case SDLK_UP        : if(sourceRect.y - SPEED >= 0)                         sourceRect.y -= SPEED;                                   break;
                case SDLK_DOWN      : if(sourceRect.y + SPEED + sourceRect.h <= HEIGHT)  sourceRect.y += SPEED;                                   break;
                case SDLK_r         :                                                       InitMaze();                                        break; // reset the seed
                case SDLK_KP_PLUS   : if (delay + DELAY <= 1000)                            delay += DELAY; std::cout << "delay: " << delay << "\n"; break; // slow down the generation
                case SDLK_KP_MINUS  : if (delay - DELAY >= 0)                               delay -= DELAY; std::cout << "delay: " << delay << "\n"; break; // accelerate the generation
                case SDLK_RETURN    :                                                       generating = !generating;                                break; // pause the game or unpause it 
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN){
            if (event.button.button == SDL_BUTTON_LEFT) {                                           // draw a cell
                float cursorX = float(event.button.x)/SCREEN_W * sourceRect.w + sourceRect.x;
                float cursorY = float(event.button.y)/SCREEN_H * sourceRect.h + sourceRect.y;
                DrawWall(cursorX, cursorY);
            }
        }
        else if (event.type == SDL_MOUSEWHEEL) {
            if(event.wheel.y > 0 && sourceRect.h > ZOOM && sourceRect.w > ZOOM) {                   // zoom in
                sourceRect.h -= ZOOM;
                sourceRect.w -= ZOOM;
            } 
            else if (event.wheel.y < 0 && sourceRect.h < HEIGHT && sourceRect.w < WIDTH) {   // zoom out
                if (sourceRect.h + sourceRect.y + ZOOM > HEIGHT) {                               // the sourceRect is exceeding the height of the Texture
                    sourceRect.y -= ZOOM;
                }
                if (sourceRect.w + sourceRect.x + ZOOM > WIDTH){                                // the sourceRect is exceeding the width of the Texture
                    sourceRect.x -= ZOOM;
                }
                sourceRect.h += ZOOM;
                sourceRect.w += ZOOM;
            }
        }
}