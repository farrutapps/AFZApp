#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flexiblesurvey.h"
#include "customsurvey.h"
#include "dbwindow.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

#include <dbmanager.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

QWidget *CentralWidget = new QWidget(this);
this->resize(900,600);

QTabWidget *Tabs = new QTabWidget(CentralWidget);

QGridLayout *mainLayout = new QGridLayout(CentralWidget);
mainLayout->addWidget(Tabs);

//connect to database
DbManager* db_man= new DbManager("/Users/Sebastian/Documents/CPP/AFZ/Feedbacker/database/fb_database.db");

QWidget *CustomTab = new CustomSurvey(this,db_man);
QWidget *DbWindowTab= new DbWindow(this,db_man);
//QWidget *FlexibleTab = new flexiblesurvey();

Tabs->addTab(CustomTab, "Customized");
Tabs->addTab(DbWindowTab, "Database Management");
//Tabs->addTab(FlexibleTab, "Flexibel");


this->setCentralWidget(CentralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
