#include "SetupTile.h"
#include <QMimeData>
#include <qguiapplication.h>
#include <QMouseEvent>
#include <QPainter>

#include "Engine.h"

SetupTile::SetupTile(int _row, int _col, QWidget* parent): row(_row), col(_col), QWidget(parent) {
    setAcceptDrops(true);
    setMouseTracking(true);

    setFixedSize(40, 40);
    setStyleSheet("border: 2px solid black;");

    connect(&Engine::instance(), &Engine::boardUpdate, this, [this](){update();});
}

void SetupTile::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setPen(QPen(QColor(Qt::black), 2));

    if (Engine::instance().has_ship_at(OWNER, this->row, this->col)) {
        painter.setBrush(QBrush(QColor(Qt::lightGray)));
        if (Engine::instance().get_ship_at(OWNER,row, col).orientation == Orientation::Horizontal) {
            painter.drawRoundedRect(0, 0, this->width()*Engine::instance().get_ship_at(OWNER,row, col).length, this->height(), 4, 4);
        }
        else {
            painter.drawRoundedRect(0, 0, this->width(), this->height()*Engine::instance().get_ship_at(OWNER,row, col).length, 4, 4);
        }
    }
    else {
        painter.setBrush(QBrush(QColor(Qt::blue)));
        painter.drawRoundedRect(0, 0, this->width(), this->height(), 4, 4);
    }
    painter.end();
}

void SetupTile::mousePressEvent(QMouseEvent *event) {
    emit tileClicked(row, col, event->button());
}

void SetupTile::mouseMoveEvent(QMouseEvent *event) {
    emit tileHovered(row, col, event->globalPosition());
    QWidget::mouseMoveEvent(event);
}

