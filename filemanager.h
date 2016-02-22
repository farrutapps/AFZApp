#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "questiondata.h"
#include "surveytype.h"

#include <QWidget>
#include <iostream>
#include <vector>
#include "dbmanager.h"

#include <fstream>
#include <cassert>
#include <vector>



using namespace std;

class FileManager
{
public:
    FileManager(QString path, int surveytype_id);

    void ReadCsv();
    void ReadDataToQuestions();
    void ReadSurveytypes();

    void WriteSurveyToDb();


    


private:
    QString file_path;
    int surveytype_id;
    DbManager db_man;
    vector <vector <QString> > question_types;


    vector <vector <string> > datamatrix;
    vector <questiondata> questions;


signals:

public slots:
};

#endif // FILEMANAGER_H
