#ifndef GAME_H
#define GAME_H
#include "computer.h"
#include <QVector>
#include <QPushButton>
#include "enums.h"

class TicTacToeBoard;

class Game
{
    TicTacToeBoard *board;
    QVector<QVector<Field>> fields;
    Computer *computer;
    int toWin = 3;
    void markWin(QVector<QPushButton*> buttons);
    State state = State::PREPARE;

public:
    Game(TicTacToeBoard *board, int toWin);

    void computerMove();
    State checkWinner(bool mark);
    QVector<QVector<Field>>& getFields();
    State getState();
    void setState(State state);
    void endGame();
};

#endif // GAME_H
