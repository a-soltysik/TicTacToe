#ifndef TICTACTOEBOARD_H
#define TICTACTOEBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include <QHash>
#include <QPair>
#include <QSignalMapper>
#include "game.h"
#include "mainwindow.h"

class TicTacToeBoard : public QWidget
{
    Q_OBJECT
    QVector<QVector<QPushButton *>> buttons;
    QHash<QPushButton*, QPair<int, int>> buttonHash;
    QSignalMapper *signalMapper;
    QGridLayout *buttonLayout = new QGridLayout();
    QGridLayout *mainLayout = new QGridLayout();
    QGridLayout *comboBoxLayout = new QGridLayout();
    QPushButton *actionButton;
    Game *game = NULL;
    MainWindow* mainWindow;
    int size = 3;
    int toWin = 3;

    void initializeButtons();
    void initializeStartButton();
    void initializeComboBoxes();
    void deleteButtons();

public:
    explicit TicTacToeBoard(QWidget *parent = nullptr);
    QVector<QVector<QPushButton *>> &getButtons();
    int getSize();
    Game *getGame();

public slots:
    void onBoardButtonClicked();
    void onSizeBoxChanged(QString string);
    void onToWinBoxChanged(QString string);
    void onActionButtonClicked();
};

#endif // TICTACTOEBOARD_H
