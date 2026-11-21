//
// Created by sen on 11/21/26.
//

#ifndef GAMEOFCONWAYLIFE_GRID_H
#define GAMEOFCONWAYLIFE_GRID_H
#include <vector>
#include <iostream>
#include "CellState.h"

class Grid {
    std::vector<std::vector<char>> grid;
public:
    int getRows() const { return grid.size(); }
    int getCols() const { return grid[0].size(); }
    char getGrid(const int row, const int col) const { return grid[row][col]; }

    // void setGrid(int row, int col, char val) { grid[row][col] = val; }
    // void setGrid(int row, int col) { grid[row][col] = ' '; }
    void setGrid(const int row, const int col) { grid.resize(row, std::vector(col, ' ')); }

    void setLiveCells(const int row, const int col, const State cell) { grid[row][col] = cell.live; }
    void setDeadCells(const int row, const int col, const State cell) { grid[row][col] = cell.dead; }

    void setAllDead(const State cell) {
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getCols(); j++) {
                grid[i][j] = cell.dead;
            }
        }
    }

    void printGrid() const {
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getCols(); j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif //GAMEOFCONWAYLIFE_GRID_H
