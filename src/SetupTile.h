#ifndef SETUPTILE_H
#define SETUPTILE_H

#include "Tile.h"

class SetupTile: public Tile {
    Q_OBJECT
public:
    explicit SetupTile(int row, int col, QWidget *parent=nullptr);
    ~SetupTile() override = default;
    signals:
    void tileClicked(int row, int col, Qt::MouseButton button);
    void tileHovered(int row, int col);
    void tileMouseMoved(int row, int col, QPointF pos);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void drawContent(QPainter &painter) override;
private:
    bool isTileHovered = false;
};
#endif
