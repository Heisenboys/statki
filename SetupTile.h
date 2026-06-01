//
// Created by Karol on 29.05.2026.
//

#ifndef SETUPTILE_H
#define SETUPTILE_H
#include <QLabel>


class SetupTile: public QLabel {
    Q_OBJECT
public:
    SetupTile();
    SetupTile(int row, int col);

    void update_tile_appearance();

    void make_ship();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;


private:
    int row;
    int col;
    bool isShip;
    int shipLength;



};



#endif //SETUPTILE_H
