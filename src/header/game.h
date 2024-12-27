#pragma once

#include <header/cell.h>
#include <SDL/SDL.h>

#define WIDTH 100
#define HEIGHT 100
#define SCREEN_W 500
#define SCREEN_H 500
#define SPEED 10
#define ZOOM 5
#define DELAY 10

extern SDL_Rect sourceRect;
extern SDL_Rect destRect;

SDL_Color CELL_COLOR        {255, 255, 255, 255};   // white
extern SDL_Color START_CELL_COLOR  {40, 116, 166, 255};    // blue 
SDL_Color END_CELL_COLOR    {125, 60, 152, 255};    // purple
SDL_Color CHOSEN_CELL_COLOR {231, 76, 60, 255};     // red
SDL_Color OPEN_CELL_COLOR   {34, 153, 84, 255};     // green
SDL_Color BORDER_COLOR      {0, 0, 0, 0};           // black

extern cell* start_cell;
extern cell* end_cell;
extern cell maze[HEIGHT][WIDTH];
extern SDL_Renderer* renderer;

void InitMaze();
void CreateGameTexture();
void DrawGameTexture();
void RefreshGameTexture();
void DrawWall(int posx, int posy);


