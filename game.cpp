#include "game.h"
#include "tictactoeboard.h"
#include <QThread>
#include <QDebug>

Game::Game(TicTacToeBoard *board, int toWin)
{
    int depth = 0;
    switch (board->getSize()) {
    case 3: depth = 9;
        break;
    case 4: depth = 7;
        break;
    case 5: depth = 6;
        break;
    case 6: depth = 4;
        break;
    case 7: depth = 3;
        break;
    case 8: depth = 3;
        break;
    }
    computer = new Computer(this, depth);
    this->board = board;
    this->toWin = toWin;
    fields = QVector<QVector<Field>>(board->getSize(), QVector<Field>(board->getSize(), Field::EMPTY));
}

State Game::getState() {
    return state;
}

void Game::setState(State state) {
    this->state = state;
}

void Game::endGame() {
    for (auto& vec : board->getButtons()) {
        for (auto& button : vec) {
            button->setEnabled(false);
        }
    }
}

void Game::computerMove()
{
    QPair<int, int> pair = computer->move(fields);
    if (pair.first != -1 && pair.second != -1) {
        board->getButtons()[pair.first][pair.second]->setText("O");
    }
    state = checkWinner(true);
    if (state != State::NONE) {
        endGame();
    }
}

QVector<QVector<Field>>& Game::getFields() {
    return fields;
}

State Game::checkWinner(bool mark)
{
    int free = 0;
    QVector<QPushButton*> winningButtons;
    for (int i = 0; i < board->getSize(); i++)
    {
        for (int j = 0; j < board->getSize(); j++)
        {
            //vertical
            if (i <= board->getSize() - toWin) {
                bool equal = true;
                for (int k=i + 1; k<i + toWin; k++) {
                    if (fields[k][j] != fields[i][j]) {
                        equal = false;
                        break;
                    }
                }
                if (equal) {
                    if (mark && fields[i][j] != Field::EMPTY) {
                        for (int k=i; k<i + toWin; k++) {
                            winningButtons.push_back(board->getButtons()[k][j]);
                            markWin(winningButtons);
                        }
                    }
                    if (fields[i][j] == Field::COMPUTER) {
                        return State::COMPUTER_WON;
                    } else if (fields[i][j] == Field::PLAYER) {
                        return State::PLAYER_WON;
                    }
                }
            }
            //horizontal
            if (j <= board->getSize() - toWin) {
                bool equal = true;
                for (int k=j + 1; k<j + toWin; k++) {
                    if (fields[i][k] != fields[i][j]) {
                        equal = false;
                        break;
                    }
                }
                if (equal) {
                    if (mark && fields[i][j] != Field::EMPTY) {
                        for (int k=j; k<j + toWin; k++) {
                            winningButtons.push_back(board->getButtons()[i][k]);
                            markWin(winningButtons);
                        }
                    }
                    if (fields[i][j] == Field::COMPUTER) {
                        return State::COMPUTER_WON;
                    } else if (fields[i][j] == Field::PLAYER) {
                        return State::PLAYER_WON;
                    }
                }
            }
            //vertical I
            if (j <= board->getSize() - toWin && i <= board->getSize() - toWin) {
                bool equal = true;
                for (int k=i + 1, l = j + 1; k<i + toWin; k++, l++) {
                    if (fields[k][l] != fields[i][j]) {
                        equal = false;
                        break;
                    }
                }
                if (equal) {
                    if (mark && fields[i][j] != Field::EMPTY) {
                        for (int k=i, l = j; k<i + toWin; k++, l++) {
                            winningButtons.push_back(board->getButtons()[k][l]);
                            markWin(winningButtons);
                        }
                    }
                    if (fields[i][j] == Field::COMPUTER) {
                        return State::COMPUTER_WON;
                    } else if (fields[i][j] == Field::PLAYER) {
                        return State::PLAYER_WON;
                    }
                }
            }
            //vertical II
            if (j >= toWin - 1 && i <= board->getSize() - toWin) {
                bool equal = true;
                for (int k=i + 1, l = j - 1; k<i + toWin; k++, l--) {
                    if (fields[k][l] != fields[i][j]) {
                        equal = false;
                        break;
                    }
                }
                if (equal) {
                    if (mark && fields[i][j] != Field::EMPTY) {
                        for (int k=i, l = j; k<i + toWin; k++, l--) {
                            winningButtons.push_back(board->getButtons()[k][l]);
                            markWin(winningButtons);
                        }
                    }
                    if (fields[i][j] == Field::COMPUTER) {
                        return State::COMPUTER_WON;
                    } else if (fields[i][j] == Field::PLAYER) {
                        return State::PLAYER_WON;
                    }
                }
            }
            if (fields[i][j] == Field::EMPTY)
            {
                free++;
            }
        }
    }
    if (free == 0)
    {
        return State::TIE;
    }
    else
    {
        return State::NONE;
    }
}

void Game::markWin(QVector<QPushButton *> buttons) {
    for (auto &button : buttons) {
        button->setStyleSheet("background-color:grey; color:white");
    }
}
