#ifndef SURVEY_H
#define SURVEY_H

#include <iostream>
#include <vector>

#include "question.h"

using namespace std;

class Survey
{
public:
    Survey(int databaseId, int sTypeId, int sLocation, int sDate);



    int getQuestionsSize() const;

    QString getLocation() const;
    void setLocation(const QString &value);

    QString getDate() const;
    void setDate(const QString &value);

    int getDbId() const;
    void setDbId(int value);

    int getSurveyTypeId() const;
    void setSurveyTypeId(int value);

private:
    int dbId;
    int surveyTypeId;

    QString location;
    QString date;

    vector <Question> questions;


signals:

public slots:
};

#endif // SURVEY_H
