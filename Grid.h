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
    std::size_t getRows() const { return grid.size(); }

    std::size_t getCols() const {
        std::size_t cols = 0;
        if (getRows() > 0) cols = grid[0].size();
        return cols;
    }

    char getGrid(const std::size_t row, const std::size_t col) const { return grid[row][col]; }

    void setGrid(const std::size_t row, const std::size_t col) { grid.assign(row, std::vector<char>(col, ' ')); }

    void setLiveCells(const std::size_t row, const std::size_t col, const State cell) { grid[row][col] = cell.live; }
    void setDeadCells(const std::size_t row, const std::size_t col, const State cell) { grid[row][col] = cell.dead; }

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
