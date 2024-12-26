#include <header/cell.h>
#include <header/pathfinding.h>
#include <header/game.h>
#include <algorithm>
#include <string>
#include <windows.h>
#include <iostream>

std::vector<cell*> open; // the cells we are looking at
std::vector<cell*> chosen; // the chosen cells

bool findNewOpenCell(cell *cell_){
    if(maze[cell_->get_coordy()][cell_->get_coordx()].get_type() == (unsigned short)CELL::BORDER) {
        return false;
    } // the cell is a border
    for(cell* cell__ : chosen)  { if(cell__->get_coordx() == cell_->get_coordx() && cell__->get_coordy() == cell_->get_coordy()) return false; }// the cell is in the chosen cell vector
    for(cell* cell__ : open)    { if(cell__->get_coordx() == cell_->get_coordx() && cell__->get_coordy() == cell_->get_coordy()) return false; }// the cell is in the open cell vector
    return true; // if the cell is neither a border or in the chosen or open cell vector, it can be in the open cell vector
}

void includeCell(cell* cell_, cell* parent_cell){
    cell_->calculateFHGcost();
    open.push_back(cell_);
    cell_->setParentCell(parent_cell);
    std::string cell_str = " " + std::to_string(cell_->getGcost()) + " " + std::to_string(cell_->getFcost());
}
void CheckSurroundingCells(cell* parent_cell){
    cell* topRightCell =    &maze[parent_cell->get_coordx() + 1][parent_cell->get_coordy() - 1];
    cell* rightCell =       &maze[parent_cell->get_coordx() + 1][parent_cell->get_coordy()    ];
    cell* bottomRightCell = &maze[parent_cell->get_coordx() + 1][parent_cell->get_coordy() + 1];
    cell* bottomCell =      &maze[parent_cell->get_coordx()    ][parent_cell->get_coordy() + 1];
    cell* bottomLeftCell =  &maze[parent_cell->get_coordx() - 1][parent_cell->get_coordy() + 1];
    cell* leftCell =        &maze[parent_cell->get_coordx() - 1][parent_cell->get_coordy()    ];
    cell* topLeftCell =     &maze[parent_cell->get_coordx() - 1][parent_cell->get_coordy() - 1];
    cell* topCell =         &maze[parent_cell->get_coordx()    ][parent_cell->get_coordy() - 1];

    if(findNewOpenCell(rightCell))       {includeCell(rightCell, parent_cell);}         //right
    if(findNewOpenCell(topRightCell))    {includeCell(topRightCell, parent_cell);}      //top right
    if(findNewOpenCell(bottomRightCell)) {includeCell(bottomRightCell, parent_cell);}   //bottom right
    if(findNewOpenCell(bottomCell))      {includeCell(bottomCell, parent_cell);}        //bottom
    if(findNewOpenCell(bottomLeftCell))  {includeCell(bottomLeftCell, parent_cell);}    // bottom left
    if(findNewOpenCell(leftCell))        {includeCell(leftCell, parent_cell);}          //left
    if(findNewOpenCell(topLeftCell))     {includeCell(topLeftCell, parent_cell);}       //top left
    if(findNewOpenCell(topCell))         {includeCell(topCell, parent_cell);}           //top
}
cell* GetCurrent(){
    cell *current = open[0]; // initialise the lowest cost to the first cell in open
    for(int i = 0; i < open.size(); i++){
        if (open[i]->getGcost() < current->getGcost()){ // we prioritise the Gcost              
            current = open[i];
        }
        else if (open[i]->getGcost() == current->getGcost()){ // if the two cells are equal we take the one with the lowest F cost
            if(open[i]->getFcost() < current->getFcost()) {                  
                current = open[i];
            }
        }
    } 
    return current;
}
std::vector<cell*> AstarPathfinding(cell *start_cell_, cell *end_cell_){
    // reset both open and chosen vector
    open = std::vector<cell*>();
    chosen = std::vector<cell*>();
    std::vector<cell*> path;
    start_cell_->calculateFHGcost();
    open.push_back(start_cell_); // adding starting cell to open

    while(1){
        cell* current = GetCurrent(); // get the nearest cell to the end
        // we are sure to have found a better or equal cell at the end of the loop, so we move the current cell from the open vector to the chosen one
        // if the cell we add to the chosen vector is the same cell we add before it means that there is no other ways to the end cell and we are blocked, we must ckeck this
        // IMPORTANT: during the first loop the "chosen_vector" is empty, leading to an undefined statement if chosen.back() is executed. That's why we
        // have to let the code continue if the vector is empty
        if (chosen.empty() || current != chosen.back()){
            open.erase(std::find(open.begin(), open.end(), current));   // remove the cell from open list
            chosen.push_back(current);                                  // add the cell to chosen list
        }
        else { // we are blocked
            std::cerr << "pathfinding error: impossible to find a valid path with the data given. ";
        }
        // we check if we found the path
        if(current->get_coordx() == end_cell_->get_coordx() && current->get_coordy() == end_cell_->get_coordy()){
            cell *current_ = end_cell_; // initialise the current-cell to the end cell
            path.push_back(current_); // put the end cell at the first place in the path vector
            // find the way back with the parent cells
            while(current_->get_coordx() != start_cell_->get_coordx() && current_->get_coordy() != start_cell_->get_coordy()){
                //d::cout << "coucoucoucoucouocu " << "\n";
                //system("cls");
                path.push_back(current_->getParentCell());
                current_ = current_->getParentCell();
            }
            return path;
        }
        // add the neighbouring cell to the open list and set their parent cell to current
        CheckSurroundingCells(current);
        
        // debuging
        std::cout << " chosen: " << chosen.size() << " open: " << open.size();
        // press space and release it to continue the pathfinding
        while (GetAsyncKeyState(VK_SPACE) & 0x8000) {}      
        while (!(GetAsyncKeyState(VK_SPACE) & 0x8000)) {}
    }
    return path;
};
