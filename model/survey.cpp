#include "survey.h"

Survey::Survey(){

}

Survey::Survey(int databaseId, int sTypeId, int sLocation, int sDate) : dbId(databaseId), surveyTypeName(sTypeId), location(sLocation), date(sDate)
{

}



QString Survey::getLocation() const
{
    return location;
}

void Survey::setLocation(const QString &value)
{
    location = value;
}

QString Survey::getDate() const
{
    return date;
}

void Survey::setDate(const QString &value)
{
    date = value;
}

int Survey::getDbId() const
{
    return dbId;
}

void Survey::setDbId(int value)
{
    dbId = value;
}

QString Survey::getSurveyTypeName() const
{
    return surveyTypeName;
}

void Survey::setSurveyTypeName(const QString &value)
{
    surveyTypeName = value;
}

int Survey::getSurveyTypeId() const
{
    return surveyTypeId;
}

void Survey::setSurveyTypeId(int value)
{
    surveyTypeId = value;
}

bool Survey::getIsFilled() const
{
    return isFilled;
}

void Survey::setIsFilled(bool value)
{
    isFilled = value;
}

int Survey::getQuestionDataSize() const
{
    return questionDataSize;
}

void Survey::setQuestionDataSize(int value)
{
    questionDataSize = value;
}

vector<Question> Survey::getQuestions() const
{
    return questions;
}


void Survey::pushBackQuestions(const Question &value)
{
    questions.push_back(value);
    isFilled=true;
}

