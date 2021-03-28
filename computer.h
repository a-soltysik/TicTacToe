#ifndef COMPUTER_H
#define COMPUTER_H

#include <QVector>
#include <QPair>
#include "enums.h"

class Game;

class Computer
{
    int depth;
    Game* game;

public:
    Computer(Game* game, int depth);
    QPair<int, int> move(QVector<QVector<Field>> &fields);
    int minmax(QVector<QVector<Field>> &fields, int depth, int alpha, int beta, bool isMaximazing);
};

#endif // COMPUTER_H
