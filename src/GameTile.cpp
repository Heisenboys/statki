#include "GameTile.h"

#include <QPainter>
#include <QMouseEvent>

#include "Engine.h"


GameTile::GameTile(int row, int col, BoardOwner owner, QWidget* parent): Tile(row, col, owner, parent) {
}

void GameTile::drawContent(QPainter& painter) {
    const bool isComputerHit = (owner == BoardOwner::Computer) && Engine::instance().isTileHit(owner, row, col);
    const bool isPlayer = (owner == BoardOwner::Player);
    const bool isSunken = (Engine::instance().isShipSunken(owner, row, col));

    if (isComputerHit || isPlayer) {
        if (Engine::instance().hasShipAt(owner, row, col)) {
            painter.setBrush(QBrush(Qt::lightGray));
            painter.setPen(QPen(Qt::NoPen));
            painter.drawRect(0, 0, width(), height());
        }
    }
    if (Engine::instance().isTileHit(owner, row, col)) {
        if (Engine::instance().hasShipAt(owner, row, col)) {
            if (isSunken){ painter.setBrush(QBrush(Qt::black)); }
            else{painter.setBrush(QBrush(Qt::red));}
        }else {
            painter.setBrush(QBrush(Qt::white));
        }
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(rect().center(), this->width()/4, this->height()/4);
    }
}

void GameTile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (owner == BoardOwner::Computer && !Engine::instance().isTileHit(owner, row, col)) {
            emit tileClicked(row, col);
        }
    }
}
