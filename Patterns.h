//
// Created by sen on 11/21/26.
//

#ifndef GAMEOFCONWAYLIFE_PATTERNS_H
#define GAMEOFCONWAYLIFE_PATTERNS_H

#include <QGraphicsScene>
#include "CellState.h"
#include "Grid.h"

void placeBlock(QGraphicsScene& myGrid, Grid& grid, const State &cellState);
void placeBlinker(QGraphicsScene& myGrid, Grid& grid, const State &cellState);
void placeGlider(QGraphicsScene& myGrid, Grid& grid, const State &cellState);

#endif //GAMEOFCONWAYLIFE_PATTERNS_H
