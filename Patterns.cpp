//
// Created by sen on 11/21/26.
//

#include "SimulationOperations.h"
#include "Patterns.h"

void placeBlock(QGraphicsScene& myGrid, Grid& grid, const State &cellState) {
    constexpr std::size_t patternRows = 2;
    constexpr std::size_t patternCols = 2;

    if (grid.getRows() < patternRows || grid.getCols() < patternCols) { return; }

    const auto startRow = (grid.getRows() - patternRows) / 2;
    const auto startCol = (grid.getCols() - patternCols) / 2;

    grid.setLiveCells(startRow, startCol, cellState);
    grid.setLiveCells(startRow, startCol + 1, cellState);
    grid.setLiveCells(startRow + 1, startCol, cellState);
    grid.setLiveCells(startRow + 1, startCol + 1, cellState);

    updateGridScene(myGrid, grid, cellState);
}

void placeBlinker(QGraphicsScene& myGrid, Grid& grid, const State &cellState) {
    constexpr std::size_t patternRows = 3;
    constexpr std::size_t patternCols = 1;

    if (grid.getRows() < patternRows || grid.getCols() < patternCols) { return; }

    const auto startRow = (grid.getRows() - patternRows) / 2;
    const auto startCol = (grid.getCols() - patternCols) / 2;

    grid.setLiveCells(startRow, startCol, cellState);
    grid.setLiveCells(startRow + 1, startCol, cellState);
    grid.setLiveCells(startRow + 2, startCol, cellState);

    updateGridScene(myGrid, grid, cellState);
}

void placeGlider(QGraphicsScene& myGrid, Grid& grid, const State &cellState) {
    constexpr std::size_t patternRows = 3;
    constexpr std::size_t patternCols = 3;

    if (grid.getRows() < patternRows || grid.getCols() < patternCols) { return; }

    const auto startRow = (grid.getRows() - patternRows) / 2;
    const auto startCol = (grid.getCols() - patternCols) / 2;

    grid.setLiveCells(startRow, startCol + 1, cellState);
    grid.setLiveCells(startRow + 1, startCol + 2, cellState);
    grid.setLiveCells(startRow + 2, startCol + 2, cellState);
    grid.setLiveCells(startRow + 2, startCol + 1, cellState);
    grid.setLiveCells(startRow + 2, startCol, cellState);

    updateGridScene(myGrid, grid, cellState);
}