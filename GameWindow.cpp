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
    QVBoxLayout * main_layout = new QVBoxLayout(this);

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
            GameTile* tile = new GameTile(row, col, BoardOwner::Computer);
            top_layout->addWidget(tile, row,col );
            connect(tile, &GameTile::tileClicked, this, &GameWindow::playerMoved);
            bottom_layout->addWidget(new GameTile(row, col, BoardOwner::Player),row,col );
        }
    }


    bottom_grid->setLayout(bottom_layout);
    top_grid->setLayout(top_layout);
    main_layout->addWidget(top_grid);
    label = new QLabel(this);
    main_layout->addWidget(label);
    main_layout->addWidget(bottom_grid);

    this->setLayout(main_layout);
}

void GameWindow::playerMoved(int row, int col) {
    if (!is_player_turn) {return;}
    is_player_turn = false;
    ShotResult result = Engine::instance().fire(BoardOwner::Computer, row, col);
    if (result == ShotResult::Miss) {
        delay(1000);
        return botMove();
    }
    Winner winner = Engine::instance().is_game_ended();
    if (winner != Winner::Unresolved) {
        return gameEnd(winner);
    }
    if (result == ShotResult::Sunk) {
        label->setText("Zatopiony");
        delay(2000);
        label->clear();
    }
    is_player_turn = true;
    return;
}

void GameWindow::botMove() {
    std::pair<int,int> move= botPlayer.calculateNextMove();
    ShotResult result = botPlayer.makeMove(move.first, move.second);
    if (result == ShotResult::Miss) {
        is_player_turn = true;
        return;
    }
    if (result == ShotResult::Hit || result == ShotResult::Sunk) {
        Winner winner = Engine::instance().is_game_ended();
        if (winner != Winner::Unresolved) {return gameEnd(winner);}
        delay(1000);
        return botMove();
    }
    if (result == ShotResult::Invalid) {
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

    endScreen->exec();
}

