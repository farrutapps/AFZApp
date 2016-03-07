#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "classes/questiondata.h"
#include "classes/dbmanager.h"

#include <QWidget>
#include <iostream>
#include <vector>


#include <fstream>
#include <cassert>
#include <vector>



using namespace std;

class FileManager
{
public:
    FileManager();
    FileManager(QString path, int surveytype_id, DbManager *database_man);

    bool ReadCsv();
    void ReadDataToQuestions();
    void ReadSurveytypes();

    void WriteSurveyToDb(QString );

    void saveToTextFile(QString, QString );

    vector <questiondata> get_questions();


private:
    QString file_path;
    int surveytype_id;
    DbManager *db_man;
    vector <vector <QString> > question_types;


    vector <vector <string> > datamatrix;
    vector <questiondata> questions;


signals:

public slots:
};

#endif // FILEMANAGER_H