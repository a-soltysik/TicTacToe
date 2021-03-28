#include <QApplication>
#include "tictactoeboard.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    MainWindow w;
    TicTacToeBoard board(&w);
    w.setCentralWidget(&board);
    w.resize(w.minimumSizeHint());
    w.show();
    return a.exec();
}
