#include "SetupWindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>

#include "Engine.h"
#include "GameWindow.h"
#include "SetupTile.h"

SetupWindow::SetupWindow() {
    previewLabel = new QLabel(this);
    previewLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    previewLabel->raise();
    previewLabel->hide();

    QVBoxLayout *layout = new QVBoxLayout();
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    for (int r = 0; r<10; r++) {
        for (int c = 0; c<10; c++) {
            SetupTile *tile = new SetupTile(r, c, this);
            connect(tile, &SetupTile::tileClicked, this, &SetupWindow::on_tileClicked);
            connect(tile, &SetupTile::tileHovered, this, &SetupWindow::on_mouse_move);
            gridLayout->addWidget(tile, r, c);
        }
    }
    layout->addLayout(gridLayout);
    QPushButton *button = new QPushButton();
    button->setText("Zatwierdź");
    connect(button, &QPushButton::clicked, this, &SetupWindow::on_button_clicked);
    layout->addWidget(button);

    Engine::instance().setup_ships();

    this->setLayout(layout);
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #0a192f, stop:1 #020c1b); color: #ccd6f6; font-family: \"Segoe UI\", sans-serif;font-size: 14px;");
}

void SetupWindow::on_button_clicked() {
    if (!Engine::instance().ship_setup_correct()) {

        return;
    }
    GameWindow* g = new GameWindow();
    g->show();
    this->close();
}

void SetupWindow::on_tileClicked(int row, int col, Qt::MouseButton button) {
    if (isHolding) {
        if (button == Qt::LeftButton) {
            int startRow = (heldShip.orientation == Orientation::Horizontal) ? row : row-mastIdx;
            int startCol = (heldShip.orientation == Orientation::Horizontal) ? col-mastIdx : col;
            if (Engine::instance().placeShip(startRow, startCol, heldShip.length, heldShip.orientation, id)) {
                isHolding = false;
                previewLabel->hide();
                return;
            }
            else {
                //jakis komunikat
            }
        }
        if (button == Qt::RightButton) {
            heldShip.orientation = (heldShip.orientation == Orientation::Horizontal) ? Orientation::Vertical : Orientation::Horizontal;
            updatePreview(mapFromGlobal(QCursor::pos()));
            return;
        }
    }
    else {
        if (button == Qt::LeftButton) {
            if (Engine::instance().has_ship_at(OWNER, row, col)) {
                isHolding = true;
                heldShip = Engine::instance().get_ship_at(OWNER, row, col);
                TileData tile = Engine::instance().get_tile_at(OWNER, row, col);
                id = tile.id;
                mastIdx = tile.mastIndex;
                originalOrientation = heldShip.orientation;
                Engine::instance().pickup_ship(row, col);
                updatePreview(mapFromGlobal(QCursor::pos()));
                previewLabel->show();
                previewLabel->raise();
            }
        }
    }
}

void SetupWindow::on_mouse_move(int row, int col, QPointF pos) {
    if (isHolding) {
        int hotX = (heldShip.orientation == Orientation::Horizontal) ? mastIdx*40+40/2 : 40/2;
        int hotY = (heldShip.orientation == Orientation::Horizontal) ? 40/2 : mastIdx*40+40/2;
        QPointF windowPos = mapFromGlobal(pos);
        previewLabel->move(windowPos.x() - hotX, windowPos.y() - hotY);
    }
}

void SetupWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape && isHolding) {
        heldShip.orientation = originalOrientation;
        Engine::instance().cancel_pickup(heldShip, id);
        isHolding = false;
        previewLabel->hide();
        return;
    }
}

void SetupWindow::updatePreview(QPoint pos) {
    int width = (heldShip.orientation == Orientation::Horizontal) ? heldShip.length*40 : 40;
    int height = (heldShip.orientation == Orientation::Horizontal) ? 40 : heldShip.length*40;

    previewLabel->setFixedSize(width, height);

    QPixmap pixmap(width, height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    painter.setBrush(QColor(Qt::lightGray));
    painter.setPen(QPen(QColor(Qt::black)));
    painter.drawRoundedRect(1, 1, width, height, 4, 4);

    painter.end();
    previewLabel->setPixmap(pixmap);

    int hotX = (heldShip.orientation == Orientation::Horizontal) ? mastIdx*40+40/2 : 40/2;
    int hotY = (heldShip.orientation == Orientation::Horizontal) ? 40/2 : mastIdx*40+40/2;

    previewLabel->move(pos.x() - hotX, pos.y() - hotY);


}

