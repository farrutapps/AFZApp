#ifndef IMPORT_H
#define IMPORT_H

#include <iostream>
#include <QUrl>
#include <vector>
#include <model/question.h>
#include <fstream>
#include <model/dbmanager.h>

using namespace std;

class Import
{
public:
    Import(DbManager *databaseMan, QString location, QString date, int surveyTypeId, vector<QString> &questionTypes, QString filePath);

    bool csvToDatamatrix(QString filePath);
    bool datamatrixToQuestions();
    void importData(QString location, QString Date, int surveyTypeId);
    bool questionsToDb(QString location, QString date, int surveyTypeId);

    bool getSuccess() const;

private:
    vector <Question> questions;
    vector < vector <string> > dataMatrix;
    vector <QString> questionTypes;
    bool success;

    DbManager *dbMan;

signals:

public slots:
};

#endif // IMPORT_H
