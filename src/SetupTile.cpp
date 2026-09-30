#include "SetupTile.h"
#include <QMimeData>
#include <qguiapplication.h>
#include <QMouseEvent>
#include <QPainter>

#include "Engine.h"
#include "SetupWindow.h"

SetupTile::SetupTile(int row, int col, QWidget* parent): Tile(row, col, BoardOwner::Player, parent) {
    setMouseTracking(true);
}

void SetupTile::drawContent(QPainter &painter) {
    if (Engine::instance().hasShipAt(owner, row, col)) {
        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(QBrush(QColor(Qt::lightGray)));
        painter.drawRect(0,0,width(),height());
    }
    if (isTileHovered) {
        painter.setPen(QPen(Qt::white, 2));
        painter.setBrush(QBrush(Qt::NoBrush));
        painter.drawRect(0,0,width(),height());
    }
}

void SetupTile::mousePressEvent(QMouseEvent *event) {
    emit tileClicked(row, col, event->button());
    QWidget::mousePressEvent(event);
}

void SetupTile::mouseMoveEvent(QMouseEvent *event) {
    emit tileMouseMoved(row, col, event->globalPosition());
    QWidget::mouseMoveEvent(event);
}

void SetupTile::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event);
    isTileHovered = true;
    update();
    emit tileHovered(row, col);
}

void SetupTile::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    isTileHovered = false;
    update();
}