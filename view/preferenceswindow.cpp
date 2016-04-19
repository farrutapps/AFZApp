#include "preferenceswindow.h"
#include "ui_preferenceswindow.h"

PreferencesWindow::PreferencesWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreferencesWindow)
{
    ui->setupUi(this);
}

PreferencesWindow::~PreferencesWindow()
{
    delete ui;
}
