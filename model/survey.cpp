#include "survey.h"

Survey::Survey(int databaseId, int sTypeId, int sLocation, int sDate) : dbId(databaseId), surveyTypeId(sTypeId), location(sLocation), date(sDate)
{

}

int Survey::getQuestionsSize() const
{
    return questions.size();
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

int Survey::getSurveyTypeId() const
{
    return surveyTypeId;
}

void Survey::setSurveyTypeId(int value)
{
    surveyTypeId = value;
}

