#include <iostream>

using namespace std;

class State {
public:
    char live = '@';
    char dead = '~';
};

class Grid {
    static const int ROWS = 5;
    static const int COLS = 5;

    char cells[ROWS][COLS];

public:
    int getRows() { return ROWS; }
    int getCols() { return COLS; }

    char getCells(int r, int c) { return cells[r][c]; }

    void setLiveCells(int row, int col, State cell) {
        cells[row][col] = cell.live;
    }

    void setDeadCells(int row, int col, State cell) {
        cells[row][col] = cell.dead;
    }

    void set(State cell) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cells[i][j] = cell.dead;
            }
        }
    }

    void print() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cout << cells[i][j] << " ";
            }
            cout << endl;
        }
    }
};

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

int neighbourCount(Grid& grid, State cell, int r, int c) {
    int neighbours = 0;

    if (r == 0 && c == 0) {
        if (grid.getCells(r, c + 1) == cell.live) { neighbours++; }
        if (grid.getCells(r + 1, c) == cell.live) { neighbours++; }
        if (grid.getCells(r + 1, c + 1) == cell.live) { neighbours++; }
    }
    else if (r == grid.getRows() - 1 && c == grid.getCols() - 1) {
        if (grid.getCells(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getCells(r, c - 1) == cell.live) { neighbours++; }
    }
    else if (r == 0) {
        if (c == grid.getCols() - 1) {
            if (grid.getCells(r, c - 1) == cell.live) { neighbours++; }
            if (grid.getCells(r + 1, c - 1) == cell.live) { neighbours++; }
            if (grid.getCells(r + 1, c) == cell.live) { neighbours++; }
        }
        else {
            if (grid.getCells(r, c - 1) == cell.live) { neighbours++; }
            if (grid.getCells(r, c + 1) == cell.live) { neighbours++; }

            if (grid.getCells(r + 1, c - 1) == cell.live) { neighbours++; }
            if (grid.getCells(r + 1, c) == cell.live) { neighbours++; }
            if (grid.getCells(r + 1, c + 1) == cell.live) { neighbours++; }
        }
    }
    else if (c == 0) {
        if (r == grid.getRows() - 1) {
            if (grid.getCells(r - 1, c) == cell.live) { neighbours++; }
            if (grid.getCells(r - 1, c + 1) == cell.live) { neighbours++; }
            if (grid.getCells(r, c + 1) == cell.live) { neighbours++; }
        }
        else {
            if (grid.getCells(r - 1, c) == cell.live) { neighbours++; }
            if (grid.getCells(r - 1, c + 1) == cell.live) { neighbours++; }
            if (grid.getCells(r, c + 1) == cell.live) { neighbours++; }
            if (grid.getCells(r + 1, c) == cell.live) { neighbours++; }
            if (grid.getCells(r + 1, c + 1) == cell.live) { neighbours++; }
        }
    }
    else if (r == grid.getRows() - 1) {
        if (grid.getCells(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getCells(r - 1, c + 1) == cell.live) { neighbours++; }
        if (grid.getCells(r, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r, c + 1) == cell.live) { neighbours++; }
    }
    else if (c == grid.getCols() - 1) {
        if (grid.getCells(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getCells(r, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r + 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r + 1, c) == cell.live) { neighbours++; }
    }
    else {
        if (grid.getCells(r - 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r - 1, c) == cell.live) { neighbours++; }
        if (grid.getCells(r - 1, c + 1) == cell.live) { neighbours++; }

        if (grid.getCells(r, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r, c + 1) == cell.live) { neighbours++; }

        if (grid.getCells(r + 1, c - 1) == cell.live) { neighbours++; }
        if (grid.getCells(r + 1, c) == cell.live) { neighbours++; }
        if (grid.getCells(r + 1, c + 1) == cell.live) { neighbours++; }
    }

    return neighbours;
}

void rulesImplementation(Grid& first, Grid& second, State cell) {
    for (int i = 0; i < first.getRows(); i++) {
        for (int j = 0; j < first.getCols(); j++) {
            int neighbours = neighbourCount(first, cell, i, j);

            if (neighbours != 3 && first.getCells(i, j) == cell.dead) { second.setDeadCells(i, j, cell); }
            if ((neighbours < 2 || neighbours > 3) && first.getCells(i, j) == cell.live) { second.setDeadCells(i, j, cell); }
            if ((neighbours == 2 || neighbours == 3) && first.getCells(i, j) == cell.live)  { second.setLiveCells(i, j, cell); }
            if (neighbours == 3 && first.getCells(i, j) == cell.dead) { second.setLiveCells(i, j, cell); }
        }
    }
}

void printSteps(int steps, Grid first, Grid second, State cell) {
    for (int i = 0; i < steps; i++) {
        cout << "11111" << endl;
        first.print();
        rulesImplementation(first, second, cell);
        cout << endl;

        cout << "22222" << endl;
        second.print();
        rulesImplementation(second, first, cell);
        cout << endl;
    }
}

int main() {
    State cell;

    Grid first;
    Grid second;

    first.set(cell);
    second.set(cell);
    setBlinker(first, cell);

    printSteps(2, first, second, cell);

    return 0;
}