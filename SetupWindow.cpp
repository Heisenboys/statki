//
// Created by Karol on 29.05.2026.
//

#include "SetupWindow.h"

#include <QPushButton>
#include <QVBoxLayout>

#include "Engine.h"
#include "GameWindow.h"
#include "SetupTile.h"

SetupWindow::SetupWindow() {
    QVBoxLayout *layout = new QVBoxLayout();
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0,0,0,0);
    for (int r = 0; r<10; r++) {
        for (int c = 0; c<10; c++) {
            SetupTile *tile = new SetupTile(r, c);
            tile->setStyleSheet("border: 2px solid black;");
            tiles.push_back(tile);
            gridLayout->addWidget(tile, r, c);
        }
    }
    SetupTile *ship = new SetupTile(-1, -1);
    ship->make_ship();
    tiles.push_back(ship);



    layout->addLayout(gridLayout);
    layout->addWidget(ship);
    QPushButton *button = new QPushButton();
    button->setText("Zatwierdź");
    connect(button, &QPushButton::clicked, this, &SetupWindow::on_button_clicked);
    layout->addWidget(button);
    this->setLayout(layout);
    this->update_board();
}

void SetupWindow::on_button_clicked() {
    if (!Engine::instance().ship_setup_correct()){return;}
    GameWindow* g = new GameWindow();
    g->show();
    this->close();
}

void SetupWindow::update_board() {
    for (auto x: tiles) {
        x->update_tile_appearance();
    }
}

