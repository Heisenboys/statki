//
// Created by Karol on 28.05.2026.
//

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>


class GameWindow : public QWidget{
    Q_OBJECT
    public:
    GameWindow();
private slots:
    void on_button_clicked();
};



#endif //GAMEWINDOW_H
