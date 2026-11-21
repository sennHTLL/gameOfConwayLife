//
// Created by sen on 11/21/26.
//
#include "SimulationOperations.h"
#include "SimulationSettings.h"

#include <qgraphicsitem.h>
#include <qrandom.h>

#include "Rules.h"

void updateGridScene(QGraphicsScene& myGrid, Grid &grid, const State &cellState) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            const int pointX = START_X + j * W;
            const int pointY = START_Y + i * H;
            QPointF point(pointX + W / 2, pointY + H / 2);

            QGraphicsItem* iPoint = myGrid.itemAt(point, QTransform());
            auto* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(iPoint);

            if (grid.getGrid(i, j) == cellState.live && rectItem != nullptr) {
                rectItem->setBrush(greenBrush);
            }
            if (grid.getGrid(i, j) == cellState.dead && rectItem != nullptr) {
                rectItem->setBrush(transparentBrush);
            }
        }
    }
}

void performGridStep(QGraphicsScene& myGrid, Grid &firstGrid, Grid &secondGrid, const State &cellState) {
    nextGeneration(firstGrid, secondGrid, cellState);
    updateGridScene(myGrid, secondGrid, cellState);
    firstGrid = secondGrid;
}

void clearGridScene(QGraphicsScene& myGrid, Grid &firstGrid, Grid &secondGrid, const State &cellState) {
    firstGrid.setAllDead(cellState);
    secondGrid.setAllDead(cellState);
    updateGridScene(myGrid, firstGrid, cellState);
}

void randomizeGridScene(QGraphicsScene& myGrid, Grid &grid, const State &cellState) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int randomNumber = QRandomGenerator::global()->bounded(100);

            if (randomNumber < DENSITY) {
                grid.setLiveCells(i, j, cellState);
            } else {
                grid.setDeadCells(i, j, cellState);
            }
        }
    }

    updateGridScene(myGrid, grid, cellState);
}
