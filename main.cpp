#include <iostream>

using namespace std;

constexpr int row = 5, col = 5;

char deadCell = '~';
char liveCell = '@';

int neighbourCount(char grid[][col], int r, int c) {
    int neighbours = 0;

    if (grid[r - 1][c - 1] == '@') { neighbours++; }
    if (grid[r - 1][c] == '@') { neighbours++; }
    if (grid[r - 1][c + 1] == '@') { neighbours++; }

    if (grid[r][c - 1] == '@') { neighbours++; }
    if (grid[r][c + 1] == '@') { neighbours++; }

    if (grid[r + 1][c - 1] == '@') { neighbours++; }
    if (grid[r + 1][c] == '@') { neighbours++; }
    if (grid[r + 1][c + 1] == '@') { neighbours++; }

    return neighbours;
}

void setBlinker(char grid[][col], int i, int j) {
    if (j == 2) {
        if (i == 1 || i == 2 || i == 3) {
            grid[i][j] = liveCell;
        }
    }
}

void setGrid(char grid1[][col], char grid2[][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            grid1[i][j] = deadCell;
            grid2[i][j] = deadCell;

            setBlinker(grid1, i, j);
        }
    }
}

void rulesImplementation(char grid1[][col], char grid2[][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int neighbours = neighbourCount(grid1, i, j);

            if ((neighbours < 2 || neighbours > 3) && grid1[i][j] == liveCell) { grid2[i][j] = deadCell; }
            if ((neighbours == 2 || neighbours == 3) && grid1[i][j] == liveCell)  { grid2[i][j] = liveCell; }
            if (neighbours == 3 && grid1[i][j] == deadCell) { grid2[i][j] = liveCell; }
        }
    }
}

void printGrid(char grid[][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char grid1[row][col], grid2[row][col];

    setGrid(grid1, grid2);
    rulesImplementation(grid1, grid2);

    printGrid(grid1);
    cout << endl;
    printGrid(grid2);

    rulesImplementation(grid2, grid1);

    cout << endl;
    printGrid(grid1);
    
    return 0;
}