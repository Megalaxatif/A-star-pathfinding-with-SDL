#include <header/game.h>
#include <SDL/SDL.h>
#include <iostream>

cell* start_cell = &maze[1][1];
cell* end_cell = &maze[6][6];
cell maze[HEIGHT][WIDTH] = {cell()};

SDL_Renderer* renderer = nullptr;
SDL_Texture* GameTexture = nullptr;
SDL_Rect sourceRect {0, 0, WIDTH, HEIGHT};
SDL_Rect destRect {10, 10, SCREEN_W -20, SCREEN_H -20};

void InitMaze(){ // initialise all the cell objects as empty space in the maze with their positions
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            maze[y][x] = cell(y,x, CELL::EMPTY_SPACE);
        }
    }
}
void CreateGameTexture(){
    GameTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT); // we create a texture with the same width and height as maze array
}
void RefreshGameTexture(){
    SDL_SetRenderTarget(renderer, GameTexture); // we draw on the texture
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){ 
            cell cell_ = maze[y][x]; 
            switch (cell_.get_type()) // change the rendering color accordingly with the type of the cell faced in the array
            {
            case CELL::BORDER: SDL_SetRenderDrawColor(renderer, BORDER_COLOR.r, BORDER_COLOR.g, BORDER_COLOR.b, BORDER_COLOR.a);
                break;
            case CELL::EMPTY_SPACE: SDL_SetRenderDrawColor(renderer, CELL_COLOR.r, CELL_COLOR.g, CELL_COLOR.b, CELL_COLOR.a);
                break;
            case CELL::CHOSEN_CELL: SDL_SetRenderDrawColor(renderer, CHOSEN_CELL_COLOR.r, CHOSEN_CELL_COLOR.g, CHOSEN_CELL_COLOR.b, CHOSEN_CELL_COLOR.a);
                break;
            case CELL::OPEN_CELL: SDL_SetRenderDrawColor(renderer, OPEN_CELL_COLOR.r, OPEN_CELL_COLOR.g, OPEN_CELL_COLOR.b, OPEN_CELL_COLOR.a);
                break;
            case CELL::START_CELL: SDL_SetRenderDrawColor(renderer, START_CELL_COLOR.r, START_CELL_COLOR.g, START_CELL_COLOR.b, START_CELL_COLOR.a);
                break;
            case CELL::END_CELL: SDL_SetRenderDrawColor(renderer, END_CELL_COLOR.r, END_CELL_COLOR.g, END_CELL_COLOR.b, END_CELL_COLOR.a);
                break;
            default:
                std::cerr << "invalid value in the maze array" << "\n";
                break;
            }
            SDL_RenderDrawPoint(renderer, cell_.get_coordx(), cell_.get_coordy()); // draw a point in the texture for each cell
        }
    }
}
void DrawGameTexture(){ // Present the texture to the screen
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, GameTexture, &sourceRect, &destRect);
    SDL_RenderPresent(renderer);
}
void DrawWall(int posx, int posy){
    maze[posy][posx].setType(CELL::BORDER);
}