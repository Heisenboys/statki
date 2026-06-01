#include <QApplication>

#include "GameWindow.h"
#include "MainWindow.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // GameWindow w;
    MainWindow w;
    w.show();

    return QApplication::exec();
}