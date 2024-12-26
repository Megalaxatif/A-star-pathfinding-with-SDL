#include <header/game.h>

cell* start_cell = &maze[1][1];
cell* end_cell = &maze[6][6];

cell maze[HEIGHT][LENGTH] = {cell()};

void CreateBoard(){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < LENGTH; x++){
            maze[y][x] = cell(y,x, CELL::EMPTY_SPACE);
        }
    }
}