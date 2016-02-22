#include "surveytype.h"

SurveyType::SurveyType(int object_id,QString objectname, vector <int> qtypes) : id(object_id), name(objectname), q_types(qtypes)
{
}

vector <int> SurveyType::get_q_types(){
    return q_types;
}

