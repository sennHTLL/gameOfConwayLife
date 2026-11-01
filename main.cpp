#include <iostream>

using namespace std;

constexpr int row = 5, col = 5;

char deadCell = '~';
char liveCell = '@';

int rules(char grid[][col], int r, int c) {
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

int main() {
    char grid[row][col];
    char grid2[row][col];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            grid[i][j] = deadCell;
            grid2[i][j] = deadCell;

            if (j == 2) {
                if (i == 1 || i == 2 || i == 3) {
                    grid[i][j] = liveCell;
                }
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int neighbours = rules(grid, i, j);

            if ((neighbours == 2 || neighbours == 3) && grid[i][j] == liveCell)  {
                grid2[i][j] = liveCell;
            }
            if (neighbours == 3 && grid[i][j] == deadCell) {
                grid2[i][j] = liveCell;
            }
            if ((neighbours < 2 || neighbours > 3) && grid[i][j] == liveCell) {
                grid2[i][j] = deadCell;
            }
        }
    }

    cout << endl;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << grid2[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}