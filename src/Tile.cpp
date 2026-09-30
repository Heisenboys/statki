#include "Tile.h"

#include <QPainter>

Tile::Tile(int _row, int _col, BoardOwner _owner, QWidget *parent):QWidget(parent), row(_row), col(_col), owner(_owner) {
    setFixedSize(40,40);
    connect(&Engine::instance(), &Engine::boardUpdate, this, [this](){update();});
};

void Tile::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::black)));
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(0,0,width(),height());
    drawContent(painter);
}
