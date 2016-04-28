#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "model/question.h"
#include "model/dbmanager.h"
#include "model/survey.h"

#include <QWidget>
#include <iostream>
#include <vector>

#include "model/survey.h"
#include "model/import.h"
#include <fstream>
#include <cassert>
#include <view/datainputpopup.h>




using namespace std;

class FileManager
{
public:
    FileManager();
    




    static void questionsToTextFile(QString filePath, QString text);
    static void fillSurveyFromDb(Survey &survey);

    static void getQuestionTypesFromDb(vector<QString> &questionTypes,  int surveyTypeId, bool cutUseless);

    static vector <Question> getQuestions();

    static vector<QString> getSurveyFacts(vector <QString> &surveyFacts, int surveyId );



    static bool surveysFromDbToModel(int &numberOfSurveys);

    static bool newCalculation(int surveyId);

    static void getSurveyTypes(vector <QString> &surveyTypes);

    static Survey *getCurrentSurvey();
    static void ImportFile(bool pathIsSet=true);

private:
    static DataInputPopup *newPopup;
    
    static DbManager *dbMan;
    static QString filePath;

    static vector <Survey> surveys;
    static Survey *currentSurvey;


signals:

public slots:
    static void importButtonClicked(bool path_is_set = 0);
    static void newImport();

};

#endif // FILEMANAGER_H
