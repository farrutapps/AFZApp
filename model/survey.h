#ifndef SURVEY_H
#define SURVEY_H

#include <iostream>
#include <vector>

#include "model/questions/question.h"

using namespace std;

class Survey
{
public:
    Survey();
    Survey(int databaseId, int sTypeId, int sLocation, int sDate);


    void pushBackQuestions(const Question &value);

    QString getLocation() const;
    void setLocation(const QString &value);

    QString getDate() const;
    void setDate(const QString &value);

    int getDbId() const;
    void setDbId(int value);

    QString getSurveyTypeName() const;
    void setSurveyTypeName(const QString &value);

    int getSurveyTypeId() const;
    void setSurveyTypeId(int value);
    
    bool getIsFilled() const;
    void setIsFilled(bool value);



    int getQuestionDataSize() const;
    void setQuestionDataSize(int value);

    vector<Question> getQuestions() const;

private:
    bool isFilled;

    int dbId;
    int surveyTypeId;
    QString surveyTypeName;

    QString location;
    QString date;

    vector <Question> questions;
    int questionDataSize;

signals:

public slots:
};

#endif // SURVEY_H
