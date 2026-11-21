//
// Created by sen on 11/21/26.
//

#ifndef GAMEOFCONWAYLIFE_SIMULATIONSETTINGS_H
#define GAMEOFCONWAYLIFE_SIMULATIONSETTINGS_H

#include <QPen>
#include <QBrush>

const QPen greenPen(Qt::darkGray);
const QBrush greenBrush(Qt::green);
const QBrush transparentBrush(Qt::transparent);

constexpr int N = 30;
constexpr int W = 15;
constexpr int H = 15;
constexpr int START_X = 10;
constexpr int START_Y = 20;
constexpr int DENSITY = 30;
constexpr int MSEC = 1000;

#endif //GAMEOFCONWAYLIFE_SIMULATIONSETTINGS_H
