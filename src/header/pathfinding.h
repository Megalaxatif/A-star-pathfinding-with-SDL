#pragma once

#include <header/cell.h>

std::vector<cell*> AstarPathfinding(cell *start_cell_, cell *end_cell_);
bool findNewOpenCell(cell *cell_);
void includeCell(cell* cell_, cell* parent_cell);   // add the neighbouring cell to the open list and set their parent cell to current
void CheckSurroundingCells(cell* parent_cell);    
cell* GetCurrent();