#include "computer.h"
#include "tictactoeboard.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Computer::Computer(Game* game, int depth)
{
    this->game = game;
    this->depth = depth;
}
Computer::~Computer(){
    if(game != nullptr) {
        delete game;
    }
}

QPair<int, int> Computer::move(QVector<QVector<Field>>& fields)
{
    QVector<QPair<int, int>> bests;
    int bestScore = INT32_MIN;
    for (int i = 0; i < fields.size(); i++)
    {
        for (int j = 0; j < fields[0].size(); j++)
        {
            if (fields[i][j] == Field::EMPTY)
            {
                fields[i][j] = Field::COMPUTER;
                int score = minmax(fields, depth, INT32_MIN, INT32_MAX, false);
                fields[i][j] = Field::EMPTY;
                if (score > bestScore)
                {
                    bestScore = score;
                    bests.clear();
                    bests.push_back(QPair<int, int>(i, j));
                } else if (score == bestScore) {
                    bests.push_back(QPair<int, int>(i, j));
                }
            }
        }
    }
    int random = rand() % bests.size();
    fields[bests[random].first][bests[random].second] = Field::COMPUTER;
    return bests[random];
}

int Computer::minmax(QVector<QVector<Field>> &fields, int depth, int alpha, int beta, bool isMaximazing)
{

    State result = game->checkWinner(false);
    if (result == State::COMPUTER_WON)
    {
        return 10;
    }
    else if (result == State::PLAYER_WON)
    {
        return -10;
    }
    else if (result == State::TIE)
    {
        return 5;
    }
    else if (depth == 0) {
        return 0;
    }

    if (isMaximazing)
    {
        int bestScore = INT32_MIN;
        for (int i = 0; i < fields.size(); i++)
        {
            for (int j = 0; j < fields[0].size(); j++)
            {
                if (fields[i][j] == Field::EMPTY)
                {
                    fields[i][j] = Field::COMPUTER;
                    int score = minmax(fields, depth - 1, alpha, beta, false);
                    fields[i][j] = Field::EMPTY;
                    bestScore = std::max(score, bestScore);
                    alpha = std::max(alpha, score);
                    if (beta <= alpha) {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = INT32_MAX;
        for (int i = 0; i < fields.size(); i++)
        {
            for (int j = 0; j < fields[0].size(); j++)
            {
                if (fields[i][j] == Field::EMPTY)
                {
                    fields[i][j] = Field::PLAYER;
                    int score = minmax(fields, depth - 1, alpha, beta, true);
                    fields[i][j] = Field::EMPTY;
                    bestScore = std::min(score, bestScore);
                    beta = std::min(beta, score);
                    if (beta <= alpha) {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
}
