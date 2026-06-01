//
// Created by Karol on 29.05.2026.
//

#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H
#include <QWidget>
#include <vector>

#include "SetupTile.h"


class SetupWindow: public QWidget{
public:
    SetupWindow();

    void update_board();

    private slots:
    void on_button_clicked();

    private:
    std::pmr::vector<SetupTile*> tiles;
};



#endif //SETUPWINDOW_H
