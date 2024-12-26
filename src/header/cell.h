#pragma once

#include <vector>

enum class CELL{
    EMPTY_SPACE = 0,
    BORDER = 1,
    START_CELL = 2,
    END_CELL = 3,
    CHOSEN_CELL = 4,
    OPEN_CELL = 5
};

class cell{
    public:
        cell(int coordx, int coordy, CELL type);
        cell();
        void calculateFHGcost();
        inline unsigned short get_type() {return type;}
        inline int get_coordx() {return x;}
        inline int get_coordy() {return y;}
        inline int getFcost() {return F_cost;}
        inline int getHcost() {return H_cost;}
        inline int getGcost() {return G_cost;}
        inline cell* getParentCell() {return parent_cell;}
        inline void setParentCell(cell *cell_) {parent_cell = cell_;}
        inline void setType(CELL type_) {type = (unsigned short)type_;}
    private:
        int x = 0;
        int y = 0;
        int F_cost = 0;
        int H_cost = 0;
        int G_cost = 0;
        unsigned short type = 0;
        cell *parent_cell;
};