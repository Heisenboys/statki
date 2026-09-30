#include "GameWindow.h"

#include <qeventloop.h>
#include <QGridLayout>
#include <QWidget>
#include <QTimer>
#include <QDialog>
#include <QLabel>

#include "GameTile.h"
#include "Engine.h"

GameWindow::GameWindow() {
    setWindowTitle("Faza bitwy");
    QVBoxLayout * main_layout = new QVBoxLayout(this);

    auto description1 = new QLabel(this);
    auto description2 = new QLabel(this);
    description1->setText("Plansza przeciwnika:");
    description2->setText("Plansza gracza:");

    QWidget* top_grid = new QWidget(this);
    QGridLayout * top_layout = new QGridLayout();
    top_layout->setSpacing(0);
    top_layout->setContentsMargins(0,0,0,0 );

    QWidget* bottom_grid = new QWidget(this);
    QGridLayout* bottom_layout = new QGridLayout();
    bottom_layout->setSpacing(0);
    bottom_layout->setContentsMargins(0,0,0,0 );

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            GameTile* tile = new GameTile(row, col, BoardOwner::Computer, this);
            top_layout->addWidget(tile, row,col );
            connect(tile, &GameTile::tileClicked, this, &GameWindow::playerMoved);
            bottom_layout->addWidget(new GameTile(row, col, BoardOwner::Player, this),row,col );
        }
    }


    bottom_grid->setLayout(bottom_layout);
    top_grid->setLayout(top_layout);
    main_layout->addWidget(description1);
    main_layout->addWidget(top_grid);
    main_layout->addWidget(description2);
    main_layout->addWidget(bottom_grid);

    this->setLayout(main_layout);
}

void GameWindow::playerMoved(int row, int col) {
    if (!isPlayerTurn) {return;}
    isPlayerTurn = false;
    ShotResult result = Engine::instance().fire(BoardOwner::Computer, row, col);
    if (result == ShotResult::Miss) {
        delay(1000);
        return botMove();
    }

    if (result == ShotResult::Sunk) {
        Winner winner = Engine::instance().isGameEnded();
        if (winner != Winner::Unresolved) {
            return gameEnd(winner);
        }
    }
    isPlayerTurn = true;
    return;
}

void GameWindow::botMove() {
    std::pair<int,int> move= botPlayer.calculateNextMove();
    ShotResult result = botPlayer.makeMove(move.first, move.second);
    if (result == ShotResult::Miss) {
        isPlayerTurn = true;
        return;
    }
    if (result == ShotResult::Hit || result == ShotResult::Sunk || result == ShotResult::Invalid) {
        if (result == ShotResult::Sunk){
            Winner winner = Engine::instance().isGameEnded();
            if (winner != Winner::Unresolved) {return gameEnd(winner);}
        }
        if (result == ShotResult::Hit || result == ShotResult::Sunk) {delay(1000);}
        return botMove();
    }
}

void GameWindow::delay(int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}

void GameWindow::gameEnd(Winner winner) {
    QDialog* endScreen = new QDialog(this);
    endScreen->setWindowTitle("Koniec Gry");


    QLabel* resultLabel = new QLabel(endScreen);
    resultLabel->setAlignment(Qt::AlignCenter);

    if (winner == Winner::Player) {
        resultLabel->setText("Zwycięstwo!\nZatopiłeś wszystkie statki wroga!");
    }
    else {
        resultLabel->setText("Porażka\nKomputer zniszczył twoją flotę.");
    }
    this->close();
    endScreen->adjustSize();
    endScreen->exec();
}

