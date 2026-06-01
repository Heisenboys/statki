//
// Created by Karol on 28.05.2026.
//

#include "GameWindow.h"

#include <QGridLayout>
#include <QPushButton>

#include "Engine.h"

GameWindow::GameWindow() {
    QVBoxLayout * main_layout = new QVBoxLayout();

    QWidget * top_grid = new QWidget();
    QGridLayout * top_layout = new QGridLayout();
    top_layout->setSpacing(0);
    top_layout->setContentsMargins(0,0,0,0 );
    int rows = 10;
    int cols = 10;
    for (int r = 0; r<rows; r++) {
        for (int c = 0; c<cols; c++) {
            QPushButton* button = new QPushButton();
            button->setProperty("row", r);
            button->setProperty("col", c);
            button->setFixedSize(40, 40);
            button->setEnabled(false);
            top_layout->addWidget(button, r, c);
        }
    }
    top_grid->setLayout(top_layout);
    QWidget * bottom_grid = new QWidget();
    QGridLayout* bottom_layout = new QGridLayout();
    bottom_layout->setSpacing(0);
    bottom_layout->setContentsMargins(0,0,0,0 );
    for (int r = 0; r<rows; r++) {
        for (int c = 0; c<cols; c++) {
            QPushButton* button = new QPushButton();
            button->setProperty("row", r);
            button->setProperty("col", c);
            button->setFixedSize(40, 40);

            connect(button, &QPushButton::clicked, this, &GameWindow::on_button_clicked);

            bottom_layout->addWidget(button, r, c);
        }
    }
    bottom_grid->setLayout(bottom_layout);
    main_layout->addWidget(top_grid);
    main_layout->addWidget(bottom_grid);

    this->setLayout(main_layout);
}

void GameWindow::on_button_clicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (clickedButton) {
        int row = clickedButton->property("row").toInt();
        int col = clickedButton->property("col").toInt();

        if (Engine::instance().fire(row, col)) {
            clickedButton->setText("T");
        }
    }


}

