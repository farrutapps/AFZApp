#ifndef MAINWINDOW_H
#define MAINWINDOW_H

using namespace std;
#include <iostream>
#include <QMainWindow>
#include "windows/calcwindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
