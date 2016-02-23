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
    explicit CustomSurvey(QWidget *parent = 0);
    ~CustomSurvey();

    void ReadCsv(string);
    void ExtractHeaders();
    void ExtractNumbers();
    void BuildCombo();
    void ReadDataToSamples();
    void SortSamples();
    void MergeSamples();
    void DisplayStatistics();



public slots:
void on_DirectoryButton_clicked();
void on_GoButton_clicked();
 void on_ClearButton_clicked();
  void on_WriteFile_Button_clicked();

private:
    Ui::CustomSurvey *ui;
    QUrl file;
    vector <vector <string> > datamatrix;
    vector <vector <double> > fb_values;
    vector <string> fb_headers;
    vector <questiondata> questions;



    vector <int> questiontypes_DA_TS;
    vector <int> questiontypes_DA_FBS;
    vector <int> questiontypes_BAN_TS;
    vector <int> questiontypes_BAN_FBS;

    DbManager *db_man;
    FileManager *f_man;

};

#endif // CUSTOMSURVEY_H
