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
    FileManager(int survey_id, DbManager *database_man);

    bool CsvToDatamatrix();
    bool DatamatrixToQuestions();
    void ReadSurveytypes();


    void QuestionsToDb(QString Location , QString Date);

    void QuestionsToTextFile(QString filepath, QString text);
    void DbToQuestions(int survey_id);

    vector <questiondata> get_questions();
    vector <QString> ReadSurveyFacts();
    bool IsReady();

private:
    QString file_path;
    int surveytype_id;
    DbManager *db_man;
    vector <vector <QString> > question_types;

    vector <QString> survey_facts;
    vector <vector <string> > datamatrix;
    vector <questiondata> questions;
    bool is_ready=false;

signals:

public slots:
};

#endif // FILEMANAGER_H
