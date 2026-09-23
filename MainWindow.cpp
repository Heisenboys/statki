#include "MainWindow.h"
#include "SetupWindow.h"

#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow() {
    QVBoxLayout *layout = new QVBoxLayout();
    start_button = new QPushButton();
    start_button->setText("Zacznij gre");
    connect(start_button, &QPushButton::clicked, this, &MainWindow::on_button_clicked);
    layout->addWidget(start_button);
    this->setLayout(layout);
}

void MainWindow::on_button_clicked() {
    start_button->setEnabled(false);
    SetupWindow* setupWindow = new SetupWindow();
    setupWindow->show();
    this->close();
}
