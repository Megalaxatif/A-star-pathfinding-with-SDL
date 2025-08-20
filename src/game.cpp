#include <header/game.h>
#include <SDL/SDL.h>
#include <iostream>

cell maze[HEIGHT][WIDTH] = {cell()};
cell* start_cell = &maze[40][1];
cell* end_cell = &maze[20][20];

SDL_Renderer* renderer = nullptr;
SDL_Texture* GameTexture = nullptr;
SDL_Rect sourceRect {0, 0, WIDTH, HEIGHT};
SDL_Rect destRect {10, 10, SCREEN_W -20, SCREEN_H -20};

SDL_Color CELL_COLOR        {255, 255, 255, 255};   // white
SDL_Color START_CELL_COLOR  {40, 116, 166, 255};    // blue 
SDL_Color END_CELL_COLOR    {125, 60, 152, 255};    // purple
SDL_Color CHOSEN_CELL_COLOR {231, 76, 60, 255};     // red
SDL_Color OPEN_CELL_COLOR   {34, 153, 84, 255};     // green
SDL_Color BORDER_COLOR      {0, 0, 0, 0};           // black
SDL_Color PATH_COLOR        {216, 216, 31, 255};    // yellow

bool isDrawing = false;

void InitMaze(){ // initialise all the cell objects as empty space in the maze with their positions
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            maze[y][x] = cell(x,y, CELL::EMPTY_SPACE);
            maze[0][x].setType(CELL::BORDER);
            maze[y][0].setType(CELL::BORDER);
            maze[HEIGHT-1][x].setType(CELL::BORDER);
            maze[y][WIDTH -1].setType(CELL::BORDER);
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
            case CELL::PATH: SDL_SetRenderDrawColor(renderer, PATH_COLOR.r, PATH_COLOR.g, PATH_COLOR.b, PATH_COLOR.a);
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
void DrawCell(CELL type, int posx, int posy){
    maze[posy][posx].setType(type);
}
void Draw(){
    int cursorX = 0.0;
    int cursorY = 0.0;
    SDL_GetMouseState(&cursorX, &cursorY);  // retrieve the position of the mouse
    float normaliZedCursorX = float(cursorX)/SCREEN_W * sourceRect.w + sourceRect.x;
    float normalizedCursorY = float(cursorY)/SCREEN_H * sourceRect.h + sourceRect.y;
    //std::cout << "x: " << normaliZedCursorX << " y: " << normalizedCursorY << "\n"; // debug
    DrawCell(CELL::BORDER, normaliZedCursorX, normalizedCursorY);
    DrawMaze();
}
void DrawMaze(){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            std::cout << (int)maze[y][x].get_type() << " ";
        }
        std::cout << "\n";
    }
}
void ResetMaze(){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            if (maze[y][x].get_type() == CELL::CHOSEN_CELL || maze[y][x].get_type() == CELL::OPEN_CELL || maze[y][x].get_type() == CELL::PATH){
                maze[y][x].setType(CELL::EMPTY_SPACE);
            }  
        }
    }
}