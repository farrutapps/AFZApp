#ifndef SURVEYTYPE_H
#define SURVEYTYPE_H

#include <vector>
#include <QWidget>

#include <vector>

using namespace std;
class SurveyType
{
public:
    SurveyType(int object_id,QString objectname, vector <int> qtypes);

    vector <int> get_q_types();

private:
    int id;
    QString name;
    vector <int> q_types;


};

#endif // SURVEYTYPE_H
