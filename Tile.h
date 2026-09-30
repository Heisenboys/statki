#ifndef UNTITLED2_TILE_H
#define UNTITLED2_TILE_H
#include <QWidget>

#include "Engine.h"


class Tile :public QWidget{
    Q_OBJECT
public:
    explicit Tile(int row, int col, BoardOwner owner, QWidget *parent = nullptr);
    virtual ~Tile() = default;

    int getRow() const {return row;}
    int getCol() const {return col;}
    BoardOwner getOwner() const {return owner;}
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    const int row;
    const int col;
    const BoardOwner owner;
};


#endif
