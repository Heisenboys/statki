#ifndef SETUPTILE_H
#define SETUPTILE_H
#include <QWidget>

#include "Engine.h"


class SetupTile: public QWidget {
    Q_OBJECT
public:
    SetupTile(int row, int col, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    signals:
    void tileClicked(int row, int col, Qt::MouseButton button);
    void tileHovered(int row, int col, QPointF pos);

private:
    int row;
    int col;

    static constexpr auto OWNER = BoardOwner::Player;
};



#endif //SETUPTILE_H
