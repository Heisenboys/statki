#ifndef UNTITLED2_GAMETILE_H
#define UNTITLED2_GAMETILE_H

#include "Engine.h"
#include "Tile.h"

class GameTile: public Tile{
    Q_OBJECT
public:
    GameTile(int row, int column, BoardOwner owner, QWidget* parent = nullptr);
    ~GameTile() override = default;
signals:
    void tileClicked(int row, int col);

protected:
    void drawContent(QPainter& painter) override;

    void mousePressEvent(QMouseEvent *event) override;
};


#endif
