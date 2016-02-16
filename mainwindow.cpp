#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flexiblesurvey.h"
#include "customsurvey.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

QWidget *CentralWidget = new QWidget(this);
this->resize(900,600);

QTabWidget *Tabs = new QTabWidget(CentralWidget);

QGridLayout *mainLayout = new QGridLayout(CentralWidget);
mainLayout->addWidget(Tabs);

QWidget *CustomTab = new CustomSurvey();
QWidget *FlexibleTab = new flexiblesurvey();

Tabs->addTab(CustomTab, "Customized");
Tabs->addTab(FlexibleTab, "Flexibel");


this->setCentralWidget(CentralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
