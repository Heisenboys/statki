#ifndef UNTITLED2_BOTPLAYER_H
#define UNTITLED2_BOTPLAYER_H
#include <utility>

#include "Engine.h"

class BotPlayer {

    bool targetKnown = false;
    QVector<std::pair<int, int>> target;
    QVector<std::pair<int, int>> shotsFired;

    void wreckage(QVector<std::pair<int,int>> target);

    bool isShotFired(int row, int col);

    public:
    BotPlayer();

    std::pair<int,int> calculateNextMove();

    void randomizeShips();

    ShotResult makeMove(int row, int col);

};

#endif //UNTITLED2_BOTPLAYER_H
