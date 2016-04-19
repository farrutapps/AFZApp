#ifndef CalcWindow_H
#define CalcWindow_H
using namespace std;
#include <iostream>
#include <QWidget>
#include <QUrl>
#include <fstream>
#include <cassert>

#include "model/question.h"
#include "model/filemanager.h"
# include "model/dbmanager.h"

namespace Ui {
class CalcWindow;
}

class CalcWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWindow(QWidget *parent = 0, DbManager *db_manager=0, FileManager *fMan=0);
    ~CalcWindow();




    void displayStatistics();
    void closeEvent (QCloseEvent *event);
public slots:
    void on_WriteFile_Button_clicked();


private:
    Ui::CalcWindow *ui;

    QUrl file;
    vector <Question> questions;

    DbManager *dbMan;
    FileManager *fMan;

};

#endif // CalcWindow_H
