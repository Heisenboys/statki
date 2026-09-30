#include "MainWindow.h"
#include <QApplication>
#include "SetupWindow.h"

#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow() {
    QVBoxLayout *layout = new QVBoxLayout();
    start_button = new QPushButton();
    start_button->setText("Zacznij gre");
    connect(start_button, &QPushButton::clicked, this, &MainWindow::on_startButtonClicked);
    layout->addWidget(start_button);
    this->setLayout(layout);
    setWindowTitle(QApplication::translate("MainWindow", "Menu", 0));
}

void MainWindow::on_startButtonClicked() {
    start_button->setEnabled(false);
    SetupWindow* setupWindow = new SetupWindow();
    setupWindow->show();
    this->close();
}
