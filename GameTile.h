#ifndef UNTITLED2_GAMETILE_H
#define UNTITLED2_GAMETILE_H

#include <QWidget>
#include "Engine.h"

class GameTile: public QWidget{
    Q_OBJECT

    int row, col;
    BoardOwner owner;
public:
    GameTile(int row, int column, BoardOwner owner);
signals:
    void tileClicked(int row, int col);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;



};


#endif //UNTITLED2_GAMETILE_H
