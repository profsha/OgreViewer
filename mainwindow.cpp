#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    cWidget=new Widget;
    this->setCentralWidget(cWidget);
}

MainWindow::~MainWindow()
{
    delete cWidget;
}
