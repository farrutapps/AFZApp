#ifndef CUSTOMSURVEY_H
#define CUSTOMSURVEY_H
using namespace std;
#include <iostream>
#include <QWidget>
#include <QUrl>
#include <fstream>
#include <cassert>
#include <questiondata.h>
#include "filemanager.h"
# include "dbmanager.h"

namespace Ui {
class CustomSurvey;
}

class CustomSurvey : public QWidget
{
    Q_OBJECT

public:
    explicit CustomSurvey(QWidget *parent = 0, DbManager *db_manager=0);
    ~CustomSurvey();


    void BuildCombo();
    void ReadDataToSamples();
    void DisplayStatistics();

public slots:
    void on_DirectoryButton_clicked();
    void on_GoButton_clicked();
    void on_ClearButton_clicked();
    void on_WriteFile_Button_clicked();
    void on_ToDbButton_clicked();

private:
    Ui::CustomSurvey *ui;

    QUrl file;
    vector <questiondata> questions;

    DbManager *db_man;
    FileManager *f_man;

};

#endif // CUSTOMSURVEY_H
