#include <QtWidgets>
#include "CellState.h"
#include "Grid.h"
#include "SimulationConfig.h"
#include "SimulationBrushes.h"
#include "SimulationOperations.h"

class MyGrid : public QGraphicsScene {
    Grid* cellGrid;
    State* cellState;

public:
    MyGrid(Grid* cellGrid, State* cellState) {
        this->cellGrid = cellGrid;
        this->cellState = cellState;
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            const QPointF clickPos = event->scenePos();
            const int X = (clickPos.x() - START_X) / W;
            const int Y = (clickPos.y() - START_Y) / H;

            QGraphicsItem* iPoint = itemAt(clickPos, QTransform());
            auto* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(iPoint);

            if (rectItem != nullptr && X >= 0 && X < N && Y >= 0 && Y < N) {
                rectItem->setBrush(greenBrush);
                cellGrid->setLiveCells(Y, X, *cellState);
                std::cout << X << " " << Y << " Changed to " << cellGrid->getGrid(Y, X) << std::endl;
            }
        }

        if (event->button() == Qt::RightButton) {
            const QPointF clickPos = event->scenePos();
            const int X = (clickPos.x() - START_X) / W;
            const int Y = (clickPos.y() - START_Y) / H;

            QGraphicsItem* iPoint = itemAt(clickPos, QTransform());
            auto* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(iPoint);

            if (rectItem != nullptr && X >= 0 && X < N && Y >= 0 && Y < N) {
                rectItem->setBrush(transparentBrush);
                cellGrid->setDeadCells(Y, X, *cellState);
                std::cout << X << " " << Y << " Changed to " << cellGrid->getGrid(Y, X) << std::endl;
            }
        }

        QGraphicsScene::mousePressEvent(event);
    }

};

static void createGridScene(MyGrid* myGrid) {
    int pointX = START_X, pointY = START_Y;

    for (int i = 0; i < N; i++) {
        pointX = START_X;
        for (int j = 0; j < N; j++) {
            myGrid->addRect(pointX, pointY, W, H, greenPen, transparentBrush);
            pointX += W;
        }
        pointY += H;
    }
}

static QHBoxLayout* buttonPlace(MyGrid &myGrid, QWidget *widget, Grid &firstGrid, Grid &secondGrid, const State &cellState) {
    auto* btnStart = new QPushButton("start", widget);
    auto* btnStop = new QPushButton("stop", widget);
    auto* btnStep = new QPushButton("step", widget);
    auto* btnClear = new QPushButton("clear", widget);
    auto* btnRandom = new QPushButton("random", widget);

    auto* timer = new QTimer(widget);
    QObject::connect(timer, &QTimer::timeout, widget, [&] {
        performGridStep(myGrid, firstGrid, secondGrid, cellState);
    });

    QPushButton::connect(btnStart, &QPushButton::clicked, widget, [timer] {
        std::cout << "start" << std::endl;
        timer->start(500);
    });

    QPushButton::connect(btnStop, &QPushButton::clicked, widget, [timer] {
        std::cout << "stop" << std::endl;
        timer->stop();
    });

    QPushButton::connect(btnStep, &QPushButton::clicked, widget, [&] {
        std::cout << "step" << std::endl;
        performGridStep(myGrid, firstGrid, secondGrid, cellState);
    });

    QPushButton::connect(btnClear, &QPushButton::clicked, widget, [&, timer] {
        std::cout << "clear" << std::endl;
        timer->stop();
        clearGridScene(myGrid, firstGrid, secondGrid, cellState);
    });

    QPushButton::connect(btnRandom, &QPushButton::clicked, widget, [&] {
        std::cout << "random" << std::endl;
        randomizeGridScene(myGrid, firstGrid, cellState);
    });

    auto* hLayout = new QHBoxLayout;

    hLayout->addWidget(btnStart);
    hLayout->addWidget(btnStop);
    hLayout->addWidget(btnStep);
    hLayout->addWidget(btnClear);
    hLayout->addWidget(btnRandom);

    return hLayout;
}

static void placeWidgets(QWidget* widget, MyGrid* grid, Grid* firstGrid, Grid* secondGrid, const State* cellState, QGraphicsView* view, QVBoxLayout* layout) {
    createGridScene(grid);
    view->setScene(grid);

    layout->addWidget(view);
    layout->addLayout(buttonPlace(*grid, widget, *firstGrid, *secondGrid, *cellState));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    QGraphicsView mainView;

    State cellState;

    Grid firstGrid;
    firstGrid.setGrid(N, N);
    firstGrid.setAllDead(cellState);

    Grid secondGrid;
    secondGrid.setGrid(N, N);
    secondGrid.setAllDead(cellState);

    auto mainGrid = MyGrid(&firstGrid, &cellState);
    auto* mainLayout = new QVBoxLayout;

    window.setLayout(mainLayout);
    placeWidgets(&window, &mainGrid, &firstGrid, &secondGrid, &cellState, &mainView, mainLayout);

    window.show();
    return QApplication::exec();
}
