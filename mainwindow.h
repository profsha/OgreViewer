#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    Widget *cWidget;
    ~MainWindow();
    
signals:
    
public slots:
    
};

#endif // MAINWINDOW_H
