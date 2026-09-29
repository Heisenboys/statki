#ifndef SETUPTILE_H
#define SETUPTILE_H
#include <QWidget>

#include "Engine.h"


class SetupTile: public QWidget {
    Q_OBJECT
public:
    SetupTile(int row, int col, QWidget *parent);

    void setGlowing(bool value);
    int getRow();
    int getCol();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

    signals:
    void tileClicked(int row, int col, Qt::MouseButton button);
    void tileHovered(SetupTile *widget);
    void tileMouseMoved(int row, int col, QPointF pos);


private:
    int row;
    int col;

    bool isTileHovered = false;

    static constexpr auto OWNER = BoardOwner::Player;


};



#endif //SETUPTILE_H
