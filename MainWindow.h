//
// Created by Karol on 28.05.2026.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QWidget>


class MainWindow: public QWidget{
    Q_OBJECT
    public:
    MainWindow();

    private:
    QPushButton *start_button;

    private slots:
    void on_button_clicked();
};



#endif //MAINWINDOW_H
