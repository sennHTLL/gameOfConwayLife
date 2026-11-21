//
// Created by sen on 11/21/26.
//

#ifndef GAMEOFCONWAYLIFE_RULES_H
#define GAMEOFCONWAYLIFE_RULES_H
#include "Grid.h"

inline int neighbourCount(const Grid& grid, const State cell, const int r, const int c) {
    int neighbours = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) { continue; }

            const int row = r + i;
            const int col = c + j;

            if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
                if (grid.getGrid(row, col) == cell.live) {
                    neighbours++;
                }
            }
        }
    }

    return neighbours;
}

inline void rulesImplementation(const Grid& first, Grid& second, const State cell) {
    for (int i = 0; i < first.getRows(); i++) {
        for (int j = 0; j < first.getCols(); j++) {
            const int neighbours = neighbourCount(first, cell, i, j);

            char currentCell = first.getGrid(i, j);

            bool b3 = neighbours == 3 && currentCell == cell.dead;
            bool s23 = (neighbours == 2 || neighbours == 3) && currentCell == cell.live;
            bool lonely = neighbours < 2 && currentCell == cell.live;
            bool overpopulation = neighbours > 3 && currentCell == cell.live;
            bool stillDead = neighbours != 3 && currentCell == cell.dead;

            if (stillDead) { second.setDeadCells(i, j, cell); }
            if (lonely || overpopulation) { second.setDeadCells(i, j, cell); }
            if (s23)  { second.setLiveCells(i, j, cell); }
            if (b3) { second.setLiveCells(i, j, cell); }
        }
    }
}

inline void nextGeneration(const Grid& first, Grid& second, State cell) {
    rulesImplementation(first, second, cell);
    // std::cout << std::endl;
    // second.printGrid();
}

#endif //GAMEOFCONWAYLIFE_RULES_H
