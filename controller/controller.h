#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "model/question.h"
#include "model/dbmanager.h"
#include "model/survey.h"
#include "model/import.h"

#include <QWidget>

#include <iostream>

#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

class Controller
{
public:
    Controller();

    static void questionsToTextFile(QString filePath, QString text);
    static void fillSurveyFromDb(Survey &survey);

    static void getQuestionTypesFromDb(vector<QString> &questionTypes,  int surveyTypeId, bool cutUseless);

    static vector <Question> getQuestions();

    static void getSurveyFacts(vector <QString> &surveyFacts, int surveyId );
    static void getSurveyFacts(vector<vector<QString> > &surveyFacts);

    static bool surveysFromDbToModel(int &numberOfSurveys);

    static bool newCalculation(int surveyId);

    static void getSurveyTypes(vector <QString> &surveyTypes);

    static Survey *getCurrentSurvey();

    static bool ImportFile(QString location, QString date, int surveyTypeId, QString filePath);

    static void deleteSurveyFromDb(QString surveyId);
private:

    
    static DbManager *dbMan;


    static vector <Survey> surveys;
    static Survey *currentSurvey;


signals:

public slots:



};

#endif // FILEMANAGER_H
