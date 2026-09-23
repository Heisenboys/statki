#include "BotPlayer.h"
#include "Engine.h"
#include <QRandomGenerator>
#include <algorithm>

BotPlayer::BotPlayer() {
    randomizeShips();
};

void BotPlayer::randomizeShips() {
    while (true) {
        std::vector<int> lengths = {2,3,3,4,5};
        int tries = 0;
        while (!lengths.empty() && tries<500) {
            tries++;
            int startRow = QRandomGenerator::global()->bounded(0, 10);
            int startCol = QRandomGenerator::global()->bounded(0, 10);
            int length = lengths.back();
            Orientation orientation = (QRandomGenerator::global()->bounded(0, 2)==0)?Orientation::Vertical:Orientation::Horizontal;
            if (Engine::instance().can_add_ship(startRow, startCol, length, orientation)) {
                lengths.pop_back();
                Engine::instance().add_ship(BoardOwner::Computer, startRow, startCol, length, orientation);
            }
        }
        if (tries>=500) {
            Engine::instance().clear_computer_board();
        }
        else {
            break;
        }
    }
}

std::pair<int,int> BotPlayer::calculateNextMove() {
    if (!targetKnown) {
        int row,col;
        do {
            row = QRandomGenerator::global()->bounded(0, 10);
            col = (row % 2 == 0)?QRandomGenerator::global()->bounded(0, 5)*2:QRandomGenerator::global()->bounded(0, 5)*2+1;
        }while (isShotFired(row, col));
        return {row, col};
    }
    else {
        if (target.size()>1) {
            Orientation orientation = (target.front().first == target.back().first)?Orientation::Horizontal:Orientation::Vertical;
            if (orientation == Orientation::Horizontal) {
                std::sort(target.begin(), target.end(), [](const auto& a, const auto& b) {return a.second < b.second;});
                std::pair left = {target.front().first, target.front().second-1};
                std::pair right = {target.back().first, target.back().second+1};
                return isShotFired(left.first, left.second) ? right : left;
            }
            else {
                std::sort(target.begin(), target.end());
                std::pair top = {target.front().first-1, target.front().second};
                std::pair bottom = {target.back().first+1, target.back().second};
                return isShotFired(top.first, top.second) ? bottom : top;
            }
        }
        else {
            QVector incrX = {-1, 1, 0, 0};
            QVector incrY = {0, 0, -1, 1};
            for (int i=0;i<4;i++) {
                if (!isShotFired(target.back().first+incrX[i], target.back().second+incrY[i])) {return {target.back().first+incrX[i], target.back().second+incrY[i]};}
            }
        }
    }
    targetKnown = false;
    target.clear();
    return calculateNextMove();
}

ShotResult BotPlayer::makeMove(int row, int col) {
    ShotResult result = Engine::instance().fire(BoardOwner::Player, row, col);
    shotsFired.push_back({row, col});
    if (result==ShotResult::Hit) {
        targetKnown = true;
        target.push_back({row, col});
        return result;
    }
    if (result==ShotResult::Sunk) {
        target.push_back({row, col});
        targetKnown = false;
        wreckage(target);
        target.clear();
    }
    return result;
}

bool BotPlayer::isShotFired(int row, int col) {
    return shotsFired.contains({row, col});
}

void BotPlayer::wreckage(QVector<std::pair<int,int>> target) {
    for (auto hit : target) {
        for (int i=-1;i<=1;i++) {
            for (int j=-1;j<=1;j++) {
                if (shotsFired.contains({hit.first+i,hit.second+j})) {continue;}
                shotsFired.push_back({hit.first+i, hit.second+j});
            }
        }
    }
}
