#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QLabel>
#include <QWidget>

#include "BotPlayer.h"


class GameWindow : public QWidget{
    Q_OBJECT
    BotPlayer botPlayer;
    bool is_player_turn = true;

    QLabel* label;
    public:
    GameWindow();
    public slots:
    void playerMoved(int row, int col);
    void botMove();
    void delay(int milliseconds);
    void gameEnd(Winner winner);
};



#endif //GAMEWINDOW_H
