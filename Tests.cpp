//
// Created by sen on 11/23/26.
//

#include <iostream>
#include "Grid.h"
#include "Rules.h"

bool sameGrid(const Grid& first, const Grid& second) {
    if (first.getRows() != second.getRows() || first.getCols() != second.getCols()) { return false; }

    for (std::size_t i = 0; i < first.getRows(); i++) {
        for (std::size_t j = 0; j < first.getCols(); j++) {
            if (first.getGrid(i, j) != second.getGrid(i, j)) { return false; }
        }
    }

    return true;
}

bool testSingleCell() {
    State state;

    Grid first;
    Grid second;

    first.setGrid(5, 5);
    second.setGrid(5, 5);

    first.setAllDead(state);
    second.setAllDead(state);

    first.setLiveCells(2, 2, state);

    nextGeneration(first, second, state);

    if (countLiveCells(second, state) != 0) {
        std::cerr << "FAIL: single cell should die\n";
        return false;
    }

    std::cout << "PASS: single cell dies\n";
    return true;
}

bool testBirth() {
    State state;

    Grid first;
    Grid second;

    first.setGrid(5, 5);
    second.setGrid(5, 5);

    first.setAllDead(state);
    second.setAllDead(state);

    first.setLiveCells(1, 1, state);
    first.setLiveCells(1, 2, state);
    first.setLiveCells(2, 1, state);

    nextGeneration(first, second, state);

    return second.getGrid(2, 2) == state.live;
}

bool testBoundary() {
    int n = 3;
    State state;

    Grid first;
    Grid second;
    Grid expected;

    first.setGrid(n, n);
    second.setGrid(n, n);
    expected.setGrid(n, n);

    first.setAllDead(state);
    second.setAllDead(state);
    expected.setAllDead(state);

    first.setLiveCells(0, 0, state);
    first.setLiveCells(0, 1, state);
    first.setLiveCells(0, 2, state);

    expected.setLiveCells(0, 1, state);
    expected.setLiveCells(1, 1, state);

    nextGeneration(first, second, state);

    return sameGrid(second, expected);
}

// PATTERNS TEST

bool testBlock() {
    State state;

    Grid first;
    Grid second;

    first.setGrid(5, 5);
    second.setGrid(5, 5);

    first.setAllDead(state);
    second.setAllDead(state);

    first.setLiveCells(1, 2, state);
    first.setLiveCells(1, 3, state);
    first.setLiveCells(2, 2, state);
    first.setLiveCells(2, 3, state);

    Grid original = first;

    nextGeneration(first, second, state);

    return sameGrid(original, second);
}

bool testBlinker() {
    State state;

    Grid first;
    Grid second;

    first.setGrid(5, 5);
    second.setGrid(5, 5);

    first.setAllDead(state);
    second.setAllDead(state);

    first.setLiveCells(1, 3, state);
    first.setLiveCells(2, 3, state);
    first.setLiveCells(3, 3, state);

    Grid original = first;

    nextGeneration(first, second, state);
    first = second;
    nextGeneration(first, second, state);

    return sameGrid(original, second);
}

bool testGlider() {
    int n = 10;
    State state;

    Grid first;
    Grid second;
    Grid expected;

    first.setGrid(n, n);
    second.setGrid(n, n);
    expected.setGrid(n, n);

    first.setAllDead(state);
    second.setAllDead(state);
    expected.setAllDead(state);

    first.setLiveCells(1, 2, state);
    first.setLiveCells(2, 3, state);
    first.setLiveCells(3, 1, state);
    first.setLiveCells(3, 2, state);
    first.setLiveCells(3, 3, state);

    expected.setLiveCells(2, 3, state);
    expected.setLiveCells(3, 4, state);
    expected.setLiveCells(4, 2, state);
    expected.setLiveCells(4, 3, state);
    expected.setLiveCells(4, 4, state);

    int i = 0;
    while (i < 4) {
        nextGeneration(first, second, state);
        first = second;
        i++;
    }

    return sameGrid(first, expected);
}

int main() {
    const bool singleCell = testSingleCell();
    const bool b3Rule = testBirth();
    const bool boundary = testBoundary();

    std::cout << "Single Cell: " << (singleCell ? "PASS" : "FAIL") << '\n';
    std::cout << "B3 Rule: " << (b3Rule ? "PASS" : "FAIL") << '\n';
    std::cout << "Boundary: " << (boundary ? "PASS" : "FAIL") << '\n';

    int logicResults = singleCell && b3Rule && boundary ? 0 : 1;

    const bool block = testBlock();
    const bool blinker = testBlinker();
    const bool glider = testGlider();

    std::cout << "Block: " << (block ? "PASS" : "FAIL") << '\n';
    std::cout << "Blinker: " << (blinker ? "PASS" : "FAIL") << '\n';
    std::cout << "Glider: " << (glider ? "PASS" : "FAIL") << '\n';

    int patternResult = block && blinker && glider ? 0 : 1;

    return logicResults || patternResult ? 0 : 1;
}