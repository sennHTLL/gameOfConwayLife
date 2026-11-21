#include <QtWidgets>
#include "CellState.h"
#include "Grid.h"
#include "Rules.h"
#include "SimulationSettings.h"
#include "SimulationOperations.h"
#include "Patterns.h"

static void configureGenerationStatistics(QLabel* lblGeneration, std::size_t generation) {
    lblGeneration->setText(
        QString("Поколение: %1")
            .arg(static_cast<qulonglong>(generation))
    );
}

static void configureLiveCellStatistics(QLabel* lblLiveCells, Grid& firstGrid, const State &cellState) {
    lblLiveCells->setText(
        QString("Живых клеток: %1")
            .arg(static_cast<qulonglong>(countLiveCells(firstGrid, cellState)))
    );
}

class MyGrid : public QGraphicsScene {
    Grid* cellGrid;
    State* cellState;
    QLabel* lblGeneration;
    QLabel* lblLiveCells;
    std::size_t* generationCount;

public:
    MyGrid(Grid* cellGrid, State* cellState, QLabel* lblGeneration, QLabel* lblLiveCells, std::size_t* generationCount) {
        this->cellGrid = cellGrid;
        this->cellState = cellState;
        this->lblLiveCells = lblLiveCells;
        this->lblGeneration = lblGeneration;
        this->generationCount = generationCount;
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
                *generationCount = 0;
                configureGenerationStatistics(lblGeneration, *generationCount);
                configureLiveCellStatistics(lblLiveCells, *cellGrid, *cellState);
                // std::cout << X << " " << Y << " Changed to " << cellGrid->getGrid(Y, X) << std::endl;
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
                *generationCount = 0;
                configureGenerationStatistics(lblGeneration, *generationCount);
                configureLiveCellStatistics(lblLiveCells, *cellGrid, *cellState);
                // std::cout << X << " " << Y << " Changed to " << cellGrid->getGrid(Y, X) << std::endl;
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

static QHBoxLayout* statisticPlace(Grid& firstGrid, const State& cellState, QLabel* lblGeneration, QLabel* lblLiveCells, std::size_t& generationCount) {
    configureGenerationStatistics(lblGeneration, generationCount);
    configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);

    auto* hLayout = new QHBoxLayout;

    hLayout->addWidget(lblGeneration);
    hLayout->addWidget(lblLiveCells);

    return hLayout;
}

static QHBoxLayout* buttonPlace(MyGrid &myGrid, QWidget *widget, Grid &firstGrid, Grid &secondGrid, const State &cellState,
    QTimer* timer, QLabel* lblGeneration, QLabel* lblLiveCells, std::size_t& generationCount) {
    auto* btnStart = new QPushButton("start", widget);
    auto* btnStop = new QPushButton("stop", widget);
    auto* btnStep = new QPushButton("step", widget);
    auto* btnClear = new QPushButton("clear", widget);
    auto* btnRandom = new QPushButton("random", widget);

    QObject::connect(timer, &QTimer::timeout, widget, [&, lblGeneration, lblLiveCells] {
        performGridStep(myGrid, firstGrid, secondGrid, cellState);
        ++generationCount;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    QPushButton::connect(btnStart, &QPushButton::clicked, widget, [timer] {
        std::cout << "start" << std::endl;
        timer->start(MSEC);
    });

    QPushButton::connect(btnStop, &QPushButton::clicked, widget, [timer] {
        std::cout << "stop" << std::endl;
        timer->stop();
    });

    QPushButton::connect(btnStep, &QPushButton::clicked, widget, [&, lblGeneration, lblLiveCells] {
        std::cout << "step" << std::endl;
        performGridStep(myGrid, firstGrid, secondGrid, cellState);
        ++generationCount;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    QPushButton::connect(btnClear, &QPushButton::clicked, widget, [&, timer, lblGeneration, lblLiveCells] {
        std::cout << "clear" << std::endl;
        timer->stop();
        clearGridScene(myGrid, firstGrid, secondGrid, cellState);
        generationCount = 0;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    QPushButton::connect(btnRandom, &QPushButton::clicked, widget, [&, timer, lblGeneration, lblLiveCells] {
        std::cout << "random" << std::endl;
        timer->stop();
        randomizeGridScene(myGrid, firstGrid, cellState);
        generationCount = 0;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    auto* hLayout = new QHBoxLayout;

    hLayout->addWidget(btnStart);
    hLayout->addWidget(btnStop);
    hLayout->addWidget(btnStep);
    hLayout->addWidget(btnClear);
    hLayout->addWidget(btnRandom);

    return hLayout;
}

static QHBoxLayout* patternPlace(MyGrid& myGrid, QWidget *widget, Grid& firstGrid, Grid& secondGrid, const State& cellState,
    QTimer* timer, QLabel* lblGeneration, QLabel* lblLiveCells, std::size_t& generationCount) {
    auto* btnBlock = new QPushButton("block", widget);
    auto* btnBlinker = new QPushButton("blinker", widget);
    auto* btnGlider = new QPushButton("glider", widget);

    QPushButton::connect(btnBlock, &QPushButton::clicked, widget, [&, timer, lblGeneration, lblLiveCells] {
        timer->stop();
        clearGridScene(myGrid, firstGrid, secondGrid, cellState);
        placeBlock(myGrid, firstGrid, cellState);
        generationCount = 0;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    QPushButton::connect(btnBlinker, &QPushButton::clicked, widget, [&, timer, lblGeneration, lblLiveCells] {
        timer->stop();
        clearGridScene(myGrid, firstGrid, secondGrid, cellState);
        placeBlinker(myGrid, firstGrid, cellState);
        generationCount = 0;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    QPushButton::connect(btnGlider, &QPushButton::clicked, widget, [&, timer, lblGeneration, lblLiveCells] {
        timer->stop();
        clearGridScene(myGrid, firstGrid, secondGrid, cellState);
        placeGlider(myGrid, firstGrid, cellState);
        generationCount = 0;
        configureGenerationStatistics(lblGeneration, generationCount);
        configureLiveCellStatistics(lblLiveCells, firstGrid, cellState);
    });

    auto* hLayout = new QHBoxLayout;

    hLayout->addWidget(btnBlock);
    hLayout->addWidget(btnBlinker);
    hLayout->addWidget(btnGlider);

    return hLayout;
}

static void placeWidgets(QWidget* widget, MyGrid* myGrid, Grid* firstGrid, Grid* secondGrid, const State* cellState,
    QTimer* timer, QLabel* lblGeneration, QLabel* lblLiveCells, std::size_t& generationCount,
    QGraphicsView* view, QVBoxLayout* layout) {
    createGridScene(myGrid);
    view->setScene(myGrid);

    layout->addWidget(view);

    layout->addLayout(statisticPlace(*firstGrid, *cellState, lblGeneration, lblLiveCells, generationCount));
    layout->addLayout(buttonPlace(*myGrid, widget, *firstGrid, *secondGrid, *cellState, timer, lblGeneration, lblLiveCells, generationCount));
    layout->addLayout(patternPlace(*myGrid, widget, *firstGrid, *secondGrid, *cellState, timer, lblGeneration, lblLiveCells, generationCount));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    QGraphicsView mainView;

    State cellState;

    auto* timer = new QTimer(&window);
    auto* lblGeneration = new QLabel(&window);
    auto* lblLiveCells = new QLabel(&window);
    std::size_t generationCount = 0;

    Grid firstGrid;
    firstGrid.setGrid(N, N);
    firstGrid.setAllDead(cellState);

    Grid secondGrid;
    secondGrid.setGrid(N, N);
    secondGrid.setAllDead(cellState);

    auto mainGrid = MyGrid(&firstGrid, &cellState, lblGeneration, lblLiveCells, &generationCount);
    auto* mainLayout = new QVBoxLayout;

    window.setLayout(mainLayout);
    placeWidgets(&window, &mainGrid, &firstGrid, &secondGrid, &cellState, timer, lblGeneration, lblLiveCells, generationCount, &mainView, mainLayout);

    window.show();
    return QApplication::exec();
}
