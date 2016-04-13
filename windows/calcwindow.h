#ifndef CalcWindow_H
#define CalcWindow_H
using namespace std;
#include <iostream>
#include <QWidget>
#include <QUrl>
#include <fstream>
#include <cassert>

#include "classes/questiondata.h"
#include "classes/filemanager.h"
# include "classes/dbmanager.h"

namespace Ui {
class CalcWindow;
}

class CalcWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWindow(QWidget *parent = 0, DbManager *db_manager=0, FileManager *f_man=0);
    ~CalcWindow();



    void ReadDataToSamples();
    void DisplayStatistics();
    void closeEvent (QCloseEvent *event);
public slots:
    void on_WriteFile_Button_clicked();


private:
    Ui::CalcWindow *ui;

    QUrl file;
    vector <questiondata> questions;

    DbManager *db_man;
    FileManager *f_man;

};

#endif // CalcWindow_H
