#pragma once

#include <header/cell.h>
#include <SDL/SDL.h>

#define WIDTH 50
#define HEIGHT 50
#define SCREEN_W 500
#define SCREEN_H 500
#define SPEED 10
#define ZOOM 5
#define DELAY 10

extern SDL_Rect sourceRect;
extern SDL_Rect destRect;

extern SDL_Color CELL_COLOR;           
extern SDL_Color START_CELL_COLOR;     
extern SDL_Color END_CELL_COLOR;       
extern SDL_Color CHOSEN_CELL_COLOR;    
extern SDL_Color OPEN_CELL_COLOR;      
extern SDL_Color BORDER_COLOR;         
extern SDL_Color PATH_COLOR;           

extern cell* start_cell;
extern cell* end_cell;
extern cell maze[HEIGHT][WIDTH];
extern SDL_Renderer* renderer;

extern bool isDrawing;

void InitMaze();
void ResetMaze(); // set every cells whose type is OPEN_CELL or CHOSEN_CELL to EMPTY_SPACE
void CreateGameTexture();
void DrawGameTexture();
void RefreshGameTexture();
void DrawCell(CELL type, int posx, int posy);
void DrawMaze();
void Draw();


