#include "tictactoeboard.h"
#include <QSignalMapper>
#include <QComboBox>
#include <QStringListModel>
#include <QTextEdit>
#include <QLabel>

TicTacToeBoard::TicTacToeBoard(QWidget *parent) : QWidget(parent) {
    this->setLayout(mainLayout);
    this->mainWindow = qobject_cast<MainWindow *>(parent);

    actionButton = new QPushButton("Start");
    connect(actionButton, SIGNAL(clicked()), this, SLOT(onActionButtonClicked()));

    signalMapper = new QSignalMapper(this);

    initializeComboBoxes();
    mainLayout->addLayout(comboBoxLayout, 0, 0);
    mainLayout->addWidget(actionButton, 2, 0);
}


void TicTacToeBoard::deleteButtons() {
    QLayoutItem *item;
    QWidget *widget;
    while ((item = buttonLayout->takeAt(0))) {
        if ((widget = item->widget()) != 0) {
            widget->hide();
            delete widget;
        } else {
            delete item;
        }
    }
}


void TicTacToeBoard::initializeComboBoxes() {
    QComboBox *sizeBox = new QComboBox();

    for (int i = 3; i <= 8; i++) {
        sizeBox->addItem(QString::number(i));
    }
    comboBoxLayout->addWidget(new QLabel("Wielkość planszy"), 0, 0);
    comboBoxLayout->addWidget(sizeBox, 1, 0);
    connect(sizeBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onSizeBoxChanged(QString)));

    QComboBox *toWinBox = new QComboBox();

    for (int i = 3; i <= (size > 5 ? 5 : size); i++) {
        toWinBox->addItem(QString::number(i));
    }
    comboBoxLayout->addWidget(new QLabel("Ilość do zaznaczenia"), 0, 1);
    comboBoxLayout->addWidget(toWinBox, 1, 1);
    connect(toWinBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onToWinBoxChanged(QString)));
}

void TicTacToeBoard::onSizeBoxChanged(QString string) {
    size = string.toInt();
    QComboBox* toWinBox = qobject_cast<QComboBox*>(comboBoxLayout->itemAtPosition(1,1)->widget());
    toWinBox->clear();
    for (int i = 3; i <= (size > 5 ? 5 : size); i++) {
        toWinBox->addItem(QString::number(i));
    }
}

void TicTacToeBoard::onToWinBoxChanged(QString string) {
    toWin = string.toInt();
}

void TicTacToeBoard::onActionButtonClicked() {
    if (game == NULL) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                comboBoxLayout->itemAtPosition(i, j)->widget()->setVisible(false);
            }
        }

        initializeButtons();
        mainLayout->addLayout(buttonLayout, 1, 0);
        mainWindow->resize(mainWindow->minimumSizeHint());

        game = new Game(this, toWin);
        game->computerMove();

    } else {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                comboBoxLayout->itemAtPosition(i, j)->widget()->setVisible(true);
            }
        }
        mainLayout->removeItem(buttonLayout);
        deleteButtons();
        this->resize(this->minimumSizeHint());
        mainWindow->resize(mainWindow->minimumSizeHint());

        delete game;
        game = NULL;
        actionButton->setText("Start");


        delete signalMapper;
        signalMapper = new QSignalMapper(this);


    }
}

void TicTacToeBoard::initializeButtons() {
    buttons = QVector<QVector<QPushButton *>>(size, QVector<QPushButton *>(size));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            buttons[i][j] = new QPushButton("");
            buttons[i][j]->setFixedSize(QSize(50, 50));
            buttonLayout->addWidget(buttons[i][j], i, j);
            buttonLayout->setSpacing(0);
            QPair<int, int> pair(i, j);

            buttonHash.insert(buttons[i][j], pair);

            connect(buttons[i][j], SIGNAL(clicked()), this, SLOT(onBoardButtonClicked()));
        }
    }
}

void TicTacToeBoard::onBoardButtonClicked() {
    QPair<int, int> pair = buttonHash.value(qobject_cast<QPushButton *>(sender()));
    int i = pair.first;
    int j = pair.second;
    if (game->getFields()[i][j] == Field::EMPTY) {
        game->getFields()[i][j] = Field::PLAYER;
        buttons[i][j]->setText("X");
        if (game->checkWinner(true) == State::NONE) {
            game->computerMove();
        } else {
            game->endGame();
        }
    }

}

QVector <QVector<QPushButton *>> &TicTacToeBoard::getButtons() {
    return buttons;
}

int TicTacToeBoard::getSize() {
    return size;
}

Game *TicTacToeBoard::getGame() {
    return game;
}
