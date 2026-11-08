#include <iostream>
#include "CellState.h"
#include "Grid.h"

using namespace std;

void setBlinker(Grid& grid, State cell) {
    for (int i = 0; i < grid.getRows(); i++) {
        for (int j = 0; j < grid.getCols(); j++) {
            if (j == 2) {
                if (i == 1 || i == 2 || i == 3) {
                    grid.setLiveCells(i, j, cell);
                }
            }
        }
    }
}
void setGlider(Grid& grid, State cell) {
    for (int i = 0; i < grid.getRows(); i++) {
        for (int j = 0; j < grid.getCols(); j++) {
            if (i == 0 && j == 1) { grid.setLiveCells(i, j, cell); }
            if (i == 1 && j == 2) { grid.setLiveCells(i, j, cell); }
            if (i == 2 && (j == 0 || j == 1 || j == 2)) { grid.setLiveCells(i, j, cell); }
        }
    }
}
void setBlock(Grid& grid, State cell) {
    for (int i = 0; i < grid.getRows(); i++) {
        for (int j = 0; j < grid.getCols(); j++) {
            if (i == 1 && (j == 1 || j == 2)) { grid.setLiveCells(i, j, cell); }
            if (i == 2 && (j == 1 || j == 2)) { grid.setLiveCells(i, j, cell); }
        }
    }
}

int neighbourCount(Grid& grid, State cell, int r, int c) {
    int neighbours = 0;

    if (r == 0 && c == 0) {
        if (grid.getGrid(r, c + 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r + 1, c) == cell.live) { neighbours++; }
        if (grid.getGrid(r + 1, c + 1) == cell.live) { neighbours++; }
    }
    else if (r == grid.getRows() - 1 && c == grid.getCols() - 1) {
        if (grid.getGrid(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getGrid(r, c - 1) == cell.live) { neighbours++; }
    }
    else if (r == 0) {
        if (c == grid.getCols() - 1) {
            if (grid.getGrid(r, c - 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r + 1, c - 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r + 1, c) == cell.live) { neighbours++; }
        }
        else {
            if (grid.getGrid(r, c - 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r, c + 1) == cell.live) { neighbours++; }

            if (grid.getGrid(r + 1, c - 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r + 1, c) == cell.live) { neighbours++; }
            if (grid.getGrid(r + 1, c + 1) == cell.live) { neighbours++; }
        }
    }
    else if (c == 0) {
        if (r == grid.getRows() - 1) {
            if (grid.getGrid(r - 1, c) == cell.live) { neighbours++; }
            if (grid.getGrid(r - 1, c + 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r, c + 1) == cell.live) { neighbours++; }
        }
        else {
            if (grid.getGrid(r - 1, c) == cell.live) { neighbours++; }
            if (grid.getGrid(r - 1, c + 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r, c + 1) == cell.live) { neighbours++; }
            if (grid.getGrid(r + 1, c) == cell.live) { neighbours++; }
            if (grid.getGrid(r + 1, c + 1) == cell.live) { neighbours++; }
        }
    }
    else if (r == grid.getRows() - 1) {
        if (grid.getGrid(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getGrid(r - 1, c + 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r, c + 1) == cell.live) { neighbours++; }
    }
    else if (c == grid.getCols() - 1) {
        if (grid.getGrid(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getGrid(r, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r + 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r + 1, c) == cell.live) { neighbours++; }
    }
    else {
        if (grid.getGrid(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getGrid(r - 1, c + 1) == cell.live) { neighbours++; }

        if (grid.getGrid(r, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r, c + 1) == cell.live) { neighbours++; }

        if (grid.getGrid(r + 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getGrid(r + 1, c) == cell.live) { neighbours++; }
        if (grid.getGrid(r + 1, c + 1) == cell.live) { neighbours++; }
    }

    return neighbours;
}

void rulesImplementation(Grid& first, Grid& second, State cell) {
    for (int i = 0; i < first.getRows(); i++) {
        for (int j = 0; j < first.getCols(); j++) {
            int neighbours = neighbourCount(first, cell, i, j);

            if (neighbours != 3 && first.getGrid(i, j) == cell.dead) { second.setDeadCells(i, j, cell); }
            if ((neighbours < 2 || neighbours > 3) && first.getGrid(i, j) == cell.live) { second.setDeadCells(i, j, cell); }
            if ((neighbours == 2 || neighbours == 3) && first.getGrid(i, j) == cell.live)  { second.setLiveCells(i, j, cell); }
            if (neighbours == 3 && first.getGrid(i, j) == cell.dead) { second.setLiveCells(i, j, cell); }
        }
    }
}

void nextGeneration(Grid& first, Grid& second, State cell) {
    first.print();
    rulesImplementation(first, second, cell);
    cout << endl;
}

int main() {
    State cell;

    Grid first;
    Grid second;

    int r, c;
    cout << "Enter row then col" << endl;
    cin >> r >> c;

    first.setGrid(r, c);
    second.setGrid(r, c);

    first.setAllDead(cell);
    second.setAllDead(cell);

    // setBlinker(first, cell);
    setGlider(first, cell);
    // setBlinker(first, cell);

    int n = 5;
    int count = 0;

    while (n > 0) {
        if (count % 2 == 0) {
            nextGeneration(first, second, cell);
        } else {
            nextGeneration(second, first, cell);
        }

        count++;
        n--;
    }

    return 0;
}