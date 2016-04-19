#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "model/question.h"
#include "model/dbmanager.h"
#include "model/survey.h"

#include <QWidget>
#include <iostream>
#include <vector>


#include <fstream>
#include <cassert>




using namespace std;

class FileManager
{
public:
    FileManager();
    FileManager(QString path, int stypeId, DbManager *databaseMan);
    FileManager(int surveyId, int stypeId, DbManager *databaseMan);

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
