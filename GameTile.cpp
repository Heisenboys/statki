#include "GameTile.h"

#include <QPainter>
#include <QMouseEvent>

#include "Engine.h"


GameTile::GameTile(int _row, int _col, BoardOwner _owner): row(_row), col(_col), owner(_owner) {
    setFixedSize(40,40);

    connect(&Engine::instance(),&Engine::boardUpdate, this, [this](){update();});

}

void GameTile::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(0, 0, this->width(), this->height());

    if (owner == BoardOwner::Computer && Engine::instance().is_tile_hit(owner, row, col) || owner == BoardOwner::Player) {
        if (Engine::instance().has_ship_at(owner, row, col)) {
            painter.setBrush(QBrush(Qt::lightGray));
            painter.drawRoundedRect(0, 0, this->width(), this->height(), 4, 4);
        }
    }

    if (Engine::instance().is_tile_hit(owner, row, col)) {
        if (Engine::instance().has_ship_at(owner, row, col)) {
            painter.setBrush(QBrush(Qt::red));
        }
        else {
            painter.setBrush(QBrush(Qt::white));
        }
        painter.drawEllipse(rect().center(), this->width()/4, this->height()/4);
    }
}

void GameTile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (owner == BoardOwner::Computer && !Engine::instance().is_tile_hit(owner, row, col)) {
            emit tileClicked(row, col);
        }
    }
}
