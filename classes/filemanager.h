#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "classes/question.h"
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
    FileManager(QString path, int stype_id, DbManager *database_man);
    FileManager(int survey_id, int stype_id, DbManager *database_man);

    bool csvToDatamatrix();
    bool datamatrixToQuestions();
    void getSurveytypes(bool cutUseless=false);



    void questionsToDb(QString location, QString date);

    void questionsToTextFile(QString filePath, QString text);
    void dbToQuestions(int surveyId);

    vector <Question> getQuestions();
    vector <QString> getSurveyFacts();

    bool getIsReady();

private:
    QString filePath;
    int surveyTypeId;
    DbManager *dbMan;
    vector <vector <QString> > questionTypes;

    vector <QString> surveyFacts;
    vector <vector <string> > dataMatrix;
    vector <Question> questions;
    bool isReady;

signals:

public slots:
};

#endif // FILEMANAGER_H
