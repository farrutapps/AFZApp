#include "dbwindow.h"
#include "ui_dbwindow.h"

DbWindow::DbWindow(QWidget *parent, DbManager *db_manager) :
    QWidget(parent),
    ui(new Ui::DbWindow), db_man(db_manager)
{
    ui->setupUi(this);
    SetupTable();
    ReadDb();
}

DbWindow::~DbWindow()
{
    delete ui;
}

void DbWindow::SetupTable(){
    ui->DbTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->DbTable->setRowCount(1);
    ui->DbTable->setColumnCount(4);

    ui->DbTable->setDragEnabled(false);
    ui->DbTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

 //   QTableWidgetItem *newItem = new QTableWidgetItem("hellooo");
   //   ui->DbTable->setItem(0, 0, newItem);
}

void DbWindow::ReadDb(){
    //setheaders
    QStringList TableHeaders;
    TableHeaders.append("Seminar");
    TableHeaders.append("Ort");
    TableHeaders.append("Datum");
    TableHeaders.append("Feedbacks");

    ui->DbTable->setHorizontalHeaderLabels(TableHeaders);
    ui->DbTable->horizontalHeader()->setStretchLastSection(true);

    vector <vector <QString> > content;
    vector <QString> query_columns;
    query_columns.push_back("");


}
