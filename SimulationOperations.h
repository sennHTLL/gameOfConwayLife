//
// Created by sen on 11/21/26.
//

#ifndef GAMEOFCONWAYLIFE_SIMULATIONOPERATIONS_H
#define GAMEOFCONWAYLIFE_SIMULATIONOPERATIONS_H
#include <QGraphicsScene>
#include "Grid.h"

void updateGridScene(QGraphicsScene& myGrid, Grid &grid, const State &cellState);
void performGridStep(QGraphicsScene& myGrid, Grid &firstGrid, Grid &secondGrid, const State &cellState);
void clearGridScene(QGraphicsScene& myGrid, Grid &firstGrid, Grid &secondGrid, const State &cellState);
void randomizeGridScene(QGraphicsScene& myGrid, Grid &grid, const State &cellState);

#endif //GAMEOFCONWAYLIFE_SIMULATIONOPERATIONS_H
