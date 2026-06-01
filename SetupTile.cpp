//
// Created by Karol on 29.05.2026.
//

#include "SetupTile.h"
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>


#include "Engine.h"

SetupTile::SetupTile(int _row, int _col): row(_row), col(_col), isShip(false) {

    setAcceptDrops(true);

    setFixedSize(40, 40);

}

SetupTile::SetupTile() {
    setAcceptDrops(true);

    setFixedSize(40, 40);
}


void SetupTile::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasText() && !isShip) {
        event->acceptProposedAction();
    }
}

void SetupTile::dropEvent(QDropEvent *event) {

    shipLength = event->mimeData()->text().toInt();

    Engine::instance().add_ship(row, col, shipLength);

    isShip = true;
    this->update_tile_appearance();
    event->acceptProposedAction();

}

void SetupTile::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isShip) {
        QMimeData *mimeData =  new QMimeData();
        mimeData->setText(QString::number(shipLength));

        QDrag *drag = new QDrag(this);
        drag->setPixmap(this->grab());
        drag->setMimeData(mimeData);

        isShip = false;
        Engine::instance().remove_ship(row, col, shipLength);
        this->update_tile_appearance();


        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
        if (dropAction == Qt::IgnoreAction) {
            isShip = true;
            Engine::instance().add_ship(row, col, shipLength);
            this->update_tile_appearance();
        }

    }
}

void SetupTile::update_tile_appearance() {
    if (this->isShip){this->setText("S");}
    else{this->setText(" ");}
}

void SetupTile::make_ship() {
    this->isShip = true;
}

