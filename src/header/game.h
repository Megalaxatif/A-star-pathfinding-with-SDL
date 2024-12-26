#pragma once

#include <header/cell.h>

#define LENGTH 100
#define HEIGHT 100
#define SCREEN_W 500
#define SCREEN_H 500

extern cell* start_cell;
extern cell* end_cell;

extern cell maze[HEIGHT][LENGTH];
void CreateBoard();