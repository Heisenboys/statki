#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H
#include <QLabel>
#include <QWidget>

#include "SetupTile.h"

class SetupWindow: public QWidget{
public:
    SetupWindow();

    private slots:
    void on_button_clicked();
    void on_tileClicked(int row, int col, Qt::MouseButton button);
    void on_mouse_move(int row, int col, QPointF pos);

    private:
    static constexpr auto OWNER = BoardOwner::Player;

    bool isHolding = false;
    ShipData heldShip;
    int id=-1;
    int mastIdx = -1;
    Orientation originalOrientation;

    QLabel* previewLabel = nullptr;

    void updatePreview(QPoint pos);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif //SETUPWINDOW_H
